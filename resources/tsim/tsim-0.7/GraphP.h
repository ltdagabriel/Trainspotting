#include "Graph.h"
#include <X11/Intrinsic.h>
#include <X11/CoreP.h>

typedef struct {
  int maxvalues;
  Pixel foreground;
  int	backing_store;
  int first, last, jump;
  int *values;
  Boolean xauto;
  int xmin, xmax;
  int ymin, ymax;
  XFontStruct *font;
  char *label;
  GC gc;
  GC cgc;
  Pixmap pixcach;
} GraphPart;

typedef struct _GraphRec {
  CorePart core;
  GraphPart graph;
} GraphRec;

typedef struct {
  int dummy;
} GraphClassPart;

typedef struct _GraphClassRec {
  CoreClassPart core_class;
  GraphClassPart graph_class;
} GraphClassRec;

extern GraphClassRec graphClassRec;
