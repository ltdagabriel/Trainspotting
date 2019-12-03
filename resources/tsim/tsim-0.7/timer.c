#include <math.h>
#include <stdio.h>
#include <X11/Xlib.h>			/* for Xlib definitions */
#include <X11/StringDefs.h>		/* for useful atom names */
#include <X11/Intrinsic.h>

#include "train.h"
#include "trainP.h"
#include "resources.h"

/* prototype for gcc */
void AddTimeOut(tTrainLine train_line);
void SendTrainEvent(tTrainLine train_line, tTrainNo tno, tEvent event);

int fsign(f)
     float f;
{
  if(f > 0.0)
    return(1);
  else if(f < 0.0)
    return(-1);
  else
    return(0);
}

void MoveTrains(train_line, dummy)
     tTrainLine train_line;
{
  tTrain *train;
  float speed_diff = timeout_interval() * acceleration();
  tEvent event;

  for(train = train_line->trains; train; train = train->next) {
    if(train->speed != train->wanted_speed) {
      train->speed += (fsign(train->wanted_speed - train->speed) * speed_diff);
      if(fabs(train->speed - train->wanted_speed) < speed_diff)
	train->speed = train->wanted_speed;
    }
    train->offset_frac += timeout_interval() * fabs(train->speed);
    if(train->offset_frac >= 1.0) {
      int int_offset = train->offset_frac;
      train->offset_frac -= int_offset;
      if((event = 
	 MoveTrain(train_line, train->no, fsign(train->speed) * int_offset))) {
	/* Collision, stop train! */
	train->speed = 0.0;
	train->wanted_speed = 0.0;
	SendTrainEvent(train_line, train->no, event);
      }
    }
  }
  AddTimeOut(train_line);
}
      
void AddTimeOut(train_line)
     tTrainLine train_line;
{
  XtAppAddTimeOut(XtWidgetToApplicationContext(train_line->top), 
		  (long)(timeout_interval() * 1000.0),
		  MoveTrains, (XtPointer)train_line);
}
