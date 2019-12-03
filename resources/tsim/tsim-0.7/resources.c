#include <X11/Xlib.h>
#include <X11/StringDefs.h>
#include <X11/Intrinsic.h>

typedef struct {
  String bitmap_dir;
  String sound_dir;
  float timeout_interval;
  float acceleration;
  String play_cmd;
} tData, *tData_ptr;

#define XtNbitmapDir "bitmapDir"
#define XtCBitmapDir "BitmapDir"
#define XtNsoundDir "soundDir"
#define XtCSoundDir "SoundDir"
#define XtNtimeoutInterval "timeoutInterval"
#define XtCTimeoutInterval "TimeoutInterval"
#define XtNacceleration "acceleration"
#define XtCAcceleration "Acceleration"
#define XtNplayCmd "playCmd"
#define XtCPlayCmd "PlayCmd"

/* Change these to point to your local bitmap and sound directories */
#define BITMAPDIR "./bitmaps"
#define SOUNDDIR  "./sounds"

#define offset(field) XtOffset(tData_ptr, field)

static XtResource resources[] = {
  { XtNbitmapDir, XtCBitmapDir, XtRString, sizeof(String), 
      offset(bitmap_dir), XtRString, BITMAPDIR },
  { XtNsoundDir, XtCSoundDir, XtRString, sizeof(String), 
      offset(sound_dir), XtRString, SOUNDDIR },
  { XtNtimeoutInterval, XtCTimeoutInterval, XtRFloat, sizeof(float),
      offset(timeout_interval), XtRString, "0.1" }, /* seconds */
  { XtNacceleration, XtCAcceleration, XtRFloat, sizeof(float),
      offset(acceleration), XtRString, "5.0", }, /* pixels / second**2 */
#ifdef __CYGWIN__
  { XtNplayCmd, XtCPlayCmd, XtRString, sizeof(String),
      offset(play_cmd), XtRString, "sndrec32 /play /close /embedding \"%s\"" } 
#else
  { XtNplayCmd, XtCPlayCmd, XtRString, sizeof(String),
      offset(play_cmd), XtRString, "mpg123 \"%s\"" } 
#endif
};

static tData data;

void GetResources(toplevel)
     Widget toplevel;
{
  XtGetApplicationResources(toplevel, &data, resources, XtNumber(resources),
			    NULL, 0);
}

String bitmap_dir()
{
  return data.bitmap_dir;
}

String sound_dir()
{
  return data.sound_dir;
}

float timeout_interval()
{
  return data.timeout_interval;
}

float acceleration()
{
  return data.acceleration;
}

String play_cmd()
{
  return data.play_cmd;
}
