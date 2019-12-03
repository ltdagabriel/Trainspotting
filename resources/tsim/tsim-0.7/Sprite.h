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
 */

#ifndef _Sprite_h
#define _Sprite_h

/*
 * Sprite widget; window shape from one bitmap, content from another.
 */

/* resource names used by sprite widget that aren't defined in StringDefs.h */

/* Pixmap defining window's shape */
#define XtNwindowPixmapMask "windowPixmapMask"
#define XtNcontentPixmap "contentPixmap"

#define XtCPixmapMask "PixmapMask"

/* structures */

typedef struct _SpriteRec *SpriteWidget;  /* see SpriteP.h */
typedef struct _SpriteClassRec *SpriteWidgetClass;  /* see SpriteP.h */


extern WidgetClass spriteWidgetClass;

#endif /* _Sprite_h */
/* DON'T ADD STUFF AFTER THIS #endif */
