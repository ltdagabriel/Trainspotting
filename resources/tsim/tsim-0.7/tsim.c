/* tsim magnus@cs.chalmers.se 1990 */
/* tsim for Linux, algo@chl.chalmers.se 2000 */

#include <stdio.h>
#include <X11/Xatom.h>
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/Shell.h>
#include <X11/Xaw/Cardinals.h>

#include "Sprite.h"
#include "train.h"
#include "file.h"
#include "resources.h"

#ifdef SOLARIS
#include <stdlib.h>
#endif

#ifdef LINUX
#include <stdlib.h>
#include <time.h>
#endif

/* prototypes for gcc */
extern void AddPipe (XtAppContext apc, tTrainLine train_line);
extern Widget CreateDrawingPalette (String name, Widget parent, 
				    tTrainLine train_line);

static String fallback_resources[] = {
  "tsim*illegalNumber.dialog.label: Illegal number or direction missing!",
  "tsim*cannotCreateTrain.dialog.label: Cannot create train!",
  "tsim*noOfCarsAndDirection.dialog.label: Enter number of cars and direction",
  "tsim*noOfCarsAndDirection.dialog.value: 1 Left",
  "tsim*cannotSave.dialog.label: Cannot save train line!",
  "tsim*save.dialog.label: Save train line in:",
  "tsim*save.dialog.value: ",
  "tsim*speed.dialog.label: Enter speed",
  "tsim*speed.dialog.value: 20",
  "tsim*illegalSpeed.dialog.label: Illegal speed!",
  "tsim*bulldozerButton.label: Delete",
  "tsim*speedButton.label: Speed",
  "tsim*switchButton.label: Switch",
  "tsim*quit.label: Quit",
  "tsim*save.label: Save",
  "tsim*tools.geometry: 467x57",
  "tsim*coordinates.label: v0.7-HUT", /* version */
  NULL
  };

int main(argc, argv)
    int argc;
    char **argv;
{
    Widget toplevel, dp;
    XtAppContext apc;
    tTrainLine tl;

#ifdef SOLARIS
    srand((int) time ((time_t *) 0));
#else
    /* srand is available in Linux, but srandom is better */
    srandom ((int) time (NULL));
#endif

    toplevel = XtAppInitialize(&apc, "Tsim", NULL, 0, &argc, argv,
			       fallback_resources, NULL, 0);
#if 0
    (void)XSynchronize(XtDisplay(toplevel),1);
#endif

    GetResources(toplevel);
    if (argc == 2) {
      if(!(tl = LoadTrainLine(argv[1], toplevel)))
	exit(1);
    } else {
      int x, y;
      if(argc == 3 || argc == 1) {
	if(argc == 1 || !sscanf(argv[1], "%d", &x) ||
	   !sscanf(argv[2], "%d", &y)) {
	  x = 20;
	  y = 20;
	}
	tl = CreateTrainLine(toplevel, Pos(x,y));
      }
    }

    AddPipe(apc, tl);

    dp = (Widget)CreateDrawingPalette("tools", toplevel, tl);

    XtRealizeWidget (toplevel);

    XtAppMainLoop (apc);

    return 0;
}
