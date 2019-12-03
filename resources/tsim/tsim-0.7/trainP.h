
#include <stdio.h>
#include "BitmapDirectory.h"
#ifndef _trainP_h
#define _trainP_h

typedef enum {
  NoCar,
  Car,
  Engine
  } tCarType;

#define MAXRAILS 200
#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define NEW(o) ((o*)(malloc(sizeof(o))))

typedef struct {
  tRailType type[RightSwitch+1];
  tSensorState sensor;
  tSwitchState sw;
  tSemaphoreState semaphore;
  Boolean custom;
  tBitmapEntry *bitmap_entry;
  tRailPos bitmap_pos;
} tRail;

typedef struct _tTrainPart {
  Widget sprite;
  tRailPos pos;
  tPos widget_pos;
  tDirection direction;
  tCarType type;
  struct _tTrainPart *next;
} tTrainPart;

typedef int tRailOffset;
typedef float tSpeed;

typedef struct _tTrain {
  tTrainNo no;
  tRailOffset offset;
  tSpeed speed, wanted_speed;
  float offset_frac;
  tTrainPart *parts;
  struct _tTrain *next;
} tTrain;

typedef enum {
  ForegroundBitmap,
  MaskBitmap } tBitmapType;

typedef tRail tRailArray[MAXRAILS][MAXRAILS];

typedef struct _tTrainLine {
  Widget top;
  tRailPos space;
  Widget back_widget;
  tRailArray rails;
  tTrain *trains;
  tTrainNo free_no;
  String file_name;
  Boolean use_pipes;
  FILE *out_pipe;
} sTrainLine;

extern unsigned int RailWidth;
extern int WheelOffset;
extern Pixmap 
  CarBitmap[Engine+1][Left+1][MaskBitmap+1],
  RailBitmap[LeftStopRail+1],
  SwitchBitmap[Left+1][RightSwitch+1],
  SensorBitmap[LeftStopRail+1];

#endif
/* No stuff here, please */
