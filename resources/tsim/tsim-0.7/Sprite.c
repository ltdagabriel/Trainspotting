/*
 *
 * Copyright 1988 Massachusetts Institute of Technology
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of M.I.T. not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  M.I.T. makes no representations about the
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 * Author:  Jim Fulton, MIT X Consortium
 *
 */

/* Sprite Widget by Magnus Carlsson */

#include <stdio.h>			/* for printing error messages */
#include <pwd.h>			/* for getting username */

#include <X11/cursorfont.h>		/* for cursor constants */
#include <X11/StringDefs.h>		/* for useful atom names */
#include <X11/IntrinsicP.h>		/* for toolkit stuff */
#include <sys/stat.h>			/* for stat() ** needs types.h ***/

#include <X11/Xaw/XawInit.h>
#include "SpriteP.h"		/* for implementation sprite stuff */

#include <X11/Xmu/Converters.h>		/* for XmuCvtStringToBitmap */
#include <X11/Xmu/Drawing.h>		/* for XmuCreatePixmapFromBitmap */

#include <X11/extensions/shape.h>

/* Initialization of defaults */

#define offset(field) XtOffset(SpriteWidget,sprite.field)
#define goffset(field) XtOffset(Widget,core.field)

static Dimension defDim = 48;
static Pixmap nopix = None;

static XtResource resources[] = {
    { XtNwidth, XtCWidth, XtRDimension, sizeof (Dimension), 
	goffset (width), XtRDimension, (caddr_t)&defDim },
    { XtNheight, XtCHeight, XtRDimension, sizeof (Dimension),
	goffset (height), XtRDimension, (caddr_t)&defDim },

    { XtNforeground, XtCForeground, XtRPixel, sizeof (Pixel),
	offset (foreground_pixel), XtRString, "black" },
    { XtNbackground, XtCBackground, XtRPixel, sizeof (Pixel),
	goffset (background_pixel), XtRString, "white" },
    { XtNreverseVideo, XtCReverseVideo, XtRBoolean, sizeof (Boolean),
	offset (reverseVideo), XtRString, "FALSE" },

    { XtNwindowPixmapMask, XtCPixmapMask, XtRBitmap, sizeof(Pixmap),
	offset (content.mask), XtRBitmap, (caddr_t) &nopix },
    { XtNcontentPixmap, XtCPixmap, XtRBitmap, sizeof(Pixmap),
	offset (content.bitmap), XtRBitmap, (caddr_t) &nopix },
};

#undef offset
#undef goffset

static void ClassInitialize(), Initialize(), Realize(), Destroy(),
  Handle_expose();
static Boolean SetValues();

SpriteClassRec spriteClassRec = {
    { /* core fields */
    /* superclass		*/	&widgetClassRec,
    /* class_name		*/	"Sprite",
    /* widget_size		*/	sizeof(SpriteRec),
    /* class_initialize		*/	ClassInitialize,
    /* class_part_initialize	*/	NULL,
    /* class_inited		*/	FALSE,
    /* initialize		*/	Initialize,
    /* initialize_hook		*/	NULL,
    /* realize			*/	Realize,
    /* actions			*/	NULL,
    /* num_actions		*/	0,
    /* resources		*/	resources,
    /* resource_count		*/	XtNumber(resources),
    /* xrm_class		*/	0, //NULL,
    /* compress_motion		*/	TRUE,
    /* compress_exposure	*/	TRUE,
    /* compress_enterleave	*/	TRUE,
    /* visible_interest		*/	FALSE,
    /* destroy			*/	Destroy,
    /* resize			*/	NULL,
    /* expose			*/	Handle_expose,
    /* set_values		*/	SetValues,
    /* set_values_hook		*/	NULL,
    /* set_values_almost	*/	XtInheritSetValuesAlmost,
    /* get_values_hook		*/	NULL,
    /* accept_focus		*/	NULL,
    /* version			*/	XtVersion,
    /* callback_private		*/	NULL,
    /* tm_table			*/	NULL,
    /* query_geometry		*/	XtInheritQueryGeometry,
    /* display_accelerator	*/	XtInheritDisplayAccelerator,
    /* extension		*/	NULL
    }
};

WidgetClass spriteWidgetClass = (WidgetClass) &spriteClassRec;


/*
 * widget initialization
 */

static void ClassInitialize ()
{
    static XtConvertArgRec screenConvertArg[] = {
    { XtWidgetBaseOffset, (caddr_t) XtOffset(Widget, core.screen), sizeof(Screen *) }
    };

    XawInitializeWidgetSet();
    XtAddConverter (XtRString, XtRBitmap, XmuCvtStringToBitmap,
		    screenConvertArg, XtNumber(screenConvertArg));
    return;
}

static GC get_sprite_gc (w)
    SpriteWidget w;
{
    XtGCMask valuemask;
    XGCValues xgcv;

    valuemask = GCForeground | GCBackground | GCFunction;
    xgcv.foreground = w->sprite.foreground_pixel;
    xgcv.background = w->core.background_pixel;
    xgcv.function = GXcopy;
    return (XtGetGC ((Widget) w, valuemask, &xgcv));
}

/* ARGSUSED */
static void Initialize (request, new)
    Widget request, new;
{
    SpriteWidget w = (SpriteWidget) new;
    int shape_event_base, shape_error_base;


    if (w->core.width <= 0) w->core.width = 1;
    if (w->core.height <= 0) w->core.height = 1;

    if (w->sprite.reverseVideo) {
	Pixel tmp;

	tmp = w->sprite.foreground_pixel;
	w->sprite.foreground_pixel = w->core.background_pixel;
	w->core.background_pixel = tmp;
    }


    w->sprite.shape_it = XShapeQueryExtension (XtDisplay (w),
					       &shape_event_base,
					       &shape_error_base);
    w->sprite.gc = get_sprite_gc(w);

    return;
}


/*
 * action procedures
 */

static Pixmap make_pixmap (dpy, w, bitmap, depth, widthp, heightp)
    Display *dpy;
    SpriteWidget w;
    Pixmap bitmap;
    int depth;
    int *widthp, *heightp;
{
    Window root;
    int x, y;
    unsigned int width, height, bw, dep;
    unsigned long fore, back;

    if (!XGetGeometry (dpy, bitmap, &root, &x, &y, &width, &height, &bw, &dep))
      return None;
    
    *widthp = (int) width;
    *heightp = (int) height;
    XtResizeWidget((Widget)w, width, height, 0);
    fore = w->sprite.foreground_pixel;
    back = w->core.background_pixel;
    return XmuCreatePixmapFromBitmap (dpy, w->core.window, bitmap, 
				      width, height, depth, fore, back);
}

static void Realize (gw, valuemaskp, attr)
    Widget gw;
    XtValueMask *valuemaskp;
    XSetWindowAttributes *attr;
{
    SpriteWidget w = (SpriteWidget) gw;
    //    register Display *dpy = XtDisplay (w);
    //    int depth = w->core.depth;

    *valuemaskp |= (CWBitGravity);
    attr->bit_gravity = ForgetGravity;

    XtCreateWindow (gw, InputOutput, (Visual *) CopyFromParent,
		    *valuemaskp, attr);

    w->sprite.content.pixmap = 
	make_pixmap(XtDisplay(gw), gw, w->sprite.content.bitmap,
		    w->core.depth, &w->sprite.content.width, 
		    &w->sprite.content.height);
    w->sprite.shape_cache = None;

    return;
}


static void Destroy (gw)
    Widget gw;
{
    SpriteWidget w = (SpriteWidget) gw;
    Display *dpy = XtDisplay (gw);

    XtDestroyGC (w->sprite.gc);
#define freepix(p) if (p) XFreePixmap (dpy, p)
    freepix (w->sprite.content.pixmap);		/* until cvter does ref cnt */
    return;
}

/* ARGSUSED */
static Boolean SetValues (gcurrent, grequest, gnew)
    Widget gcurrent, grequest, gnew;
{
    SpriteWidget current = (SpriteWidget) gcurrent;
    SpriteWidget new = (SpriteWidget) gnew;
    Boolean redisplay = FALSE;
    Display *dpy = XtDisplay (gcurrent);

    XRaiseWindow(dpy, XtWindow(new));
    if(current->sprite.content.bitmap != new->sprite.content.bitmap) {
      freepix(current->sprite.content.pixmap);
#undef freepix
      new->sprite.content.pixmap = 
	make_pixmap(XtDisplay(gnew), gnew, new->sprite.content.bitmap,
		    new->core.depth, &new->sprite.content.width, 
		    &new->sprite.content.height);
      redisplay = TRUE;
    }

    if (current->sprite.foreground_pixel != new->sprite.foreground_pixel ||
	current->core.background_pixel != new->core.background_pixel) {
	XtDestroyGC (current->sprite.gc);
	new->sprite.gc = get_sprite_gc (new);
	redisplay = TRUE;
    }
    return (redisplay);
}


/*
 * drawing code
 */

static void Handle_expose(w, event, region)
     SpriteWidget w;
     XEvent *event;
     Region region;
{
  register Display *dpy = XtDisplay (w);
  register Window win = XtWindow (w);
  int x, y, width, height;

  switch(event->type) {
    case Expose: 
      x = event->xexpose.x;
      y = event->xexpose.y;
      width = event->xexpose.width;
      height = event->xexpose.height;
      break;
    case GraphicsExpose:
      x = event->xgraphicsexpose.x;
      y = event->xgraphicsexpose.y;
      width = event->xgraphicsexpose.width;
      height = event->xgraphicsexpose.height;
      break;
    default:
      return;
  }
      
  XCopyArea (dpy, w->sprite.content.pixmap, win, w->sprite.gc, x, y,
	     width, height, x, y);
  
  if (w->sprite.shape_it && w->sprite.content.mask != w->sprite.shape_cache) {
    XShapeCombineMask (dpy, win, ShapeBounding, 0, 0,
		       w->sprite.content.mask, ShapeSet);
    w->sprite.shape_cache = w->sprite.content.mask;
  }
}
