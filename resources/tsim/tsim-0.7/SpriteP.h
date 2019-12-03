/*
 * $XConsortium: MailboxP.h,v 1.16 89/05/11 01:05:56 kit Exp $
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

#ifndef _SpriteP_h
#define _SpriteP_h

#include "Sprite.h"

typedef struct {			/* new fields for sprite widget */
    /* resources */
    Pixel foreground_pixel;		/* color index of normal state fg */
    Boolean reverseVideo;		/* do reverse video? */
    GC gc;				/* normal GC to use */
    struct _mbimage {
	Pixmap bitmap, mask;		/* depth 1, describing shape */
	Pixmap pixmap;			/* full depth pixmap */
	int width, height;		/* geometry of pixmaps */
    } content;
    Boolean shape_it;
    Pixmap shape_cache;
} SpritePart;

typedef struct _SpriteRec {		/* full instance record */
    CorePart core;
    SpritePart sprite;
} SpriteRec;


typedef struct {			/* new fields for mailbox class */
    int dummy;				/* stupid C compiler */
} SpriteClassPart;

typedef struct _SpriteClassRec {	/* full class record declaration */
    CoreClassPart core_class;
    SpriteClassPart mailbox_class;
} SpriteClassRec;

extern SpriteClassRec spriteClassRec;	 /* class pointer */

#endif /* _SpriteP_h */
