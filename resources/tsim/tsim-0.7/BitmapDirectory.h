#ifndef _BitmapDirectory_h
#define _BitmapDirectory_h

typedef struct {
  Pixmap bitmap;
  String name;
  unsigned int width, height;
} tBitmapEntry;

typedef struct _tBitmapDirectory *tBitmapDirectory;


tBitmapDirectory BDAddDirectory();
void BDFindBitmap();
void BDBitmaps();
#endif
/* No stuff here, please */
