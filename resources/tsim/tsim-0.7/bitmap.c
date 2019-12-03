#include <X11/Xlib.h>
#include <stdio.h>
#include <X11/Intrinsic.h>
#ifndef SOLARIS
#include <X11/Xlibint.h>
#endif
#include "resources.h"
#include "BitmapDirectory.h"

static tBitmapDirectory gBitmapDirectory;

static void GetBitmapPath(name, full_name)
     String name, full_name;
{
  sprintf(full_name, "%s/%s", bitmap_dir(), name);
}

#define BUFSIZE 2048
void ReadCustomBitmaps(w)
     Widget w;
{
  char custom_directory[BUFSIZE];

  sprintf(custom_directory, "%s/customBitmaps", bitmap_dir());
  gBitmapDirectory = BDAddDirectory(w, custom_directory, NULL);
}

void FindCustomBitmap(name, bitmap_entry)
     String name;
     tBitmapEntry **bitmap_entry;
{
  BDFindBitmap(name, bitmap_entry, gBitmapDirectory);
}

void CustomBitmaps(entry, bitmap_entry)
     void **entry;
     tBitmapEntry **bitmap_entry;
{
  BDBitmaps(entry, bitmap_entry, gBitmapDirectory);
}

void ReadBitmap(w, name, dest, width_return, hot_y_return)
     Widget w;
     String name;
     Pixmap *dest;
     unsigned int *width_return;
     int *hot_y_return;
{
  char file_name[BUFSIZE];
  unsigned int width,height;
  int hot_x,hot_y;
  Window win = XRootWindowOfScreen(XtScreen(w));

  GetBitmapPath(name, file_name);
  if(XReadBitmapFile(XtDisplay(w), win, file_name, &width, &height, dest,
		     &hot_x, &hot_y) !=BitmapSuccess) {
    fprintf(stderr, "Error reading bitmap file %s\n", file_name);
    exit(1);
  }
  *hot_y_return = hot_y;
  *width_return = width;
}

void WriteBitmap(w, name, bitmap)
     Widget w;
     String name;
     Pixmap bitmap;
{
  char file_name[200];
  Window dummywin;
  int dummyint;
  unsigned int width, height, dummy;
  
  if(!XGetGeometry(XtDisplay(w), bitmap, &dummywin, &dummyint, 
		   &dummyint, &width, &height, &dummy, &dummy)) {
    fprintf(stderr,"XGetGeometry failed in SaveBitmap\n");
    exit(1);
  }

  GetBitmapPath(name, file_name);
  
  if(XWriteBitmapFile(XtDisplay(w), file_name, bitmap, width, height, -1, -1))
    {
      fprintf(stderr, "Error writing bitmap file %s\n", file_name);
      exit(1);
    }
}
