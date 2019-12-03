#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#ifdef SOLARIS
#include <string.h>
#else
#include <strings.h>
#endif
#include <sys/wait.h>
#include "train.h"
#include "trainP.h"
#include "resources.h"
#include <stdlib.h>

/* LINUX defines random in <stdlib.h> as: long int random(void); */
#ifdef SOLARIS
extern long random();
#endif

#ifdef LINUX
#include <unistd.h>                            /* for fork */ 
#endif

typedef struct { char *fname; double p; } SoundTable;

static SoundTable startsound[] = { {"train.wav", 1.0} };
static SoundTable faststartsound[] = { {"ftrain.wav", 1.0} };

static SoundTable traincrashsound[] = { 
  {"crash1.wav", 0.5},
  {"crash2.wav", 0.5}};

static SoundTable derailcrashsound[] = { 
  {"derail.wav", 1.0}};


static SoundTable stopcrashsound[] = { 
  {"stcrash.wav", 1.0}};


static void play(sound, host)
     char *sound, *host;
{
#define SIZE 200
  char command[SIZE];
  char playc[SIZE];
  char path[SIZE];

#ifndef SOLARIS
  /* Give peace to defunct processes */

  while(wait3(NULL, WNOHANG, NULL) > 0)
    ;
#endif

  if(!fork()) {
    sprintf(path,"%s/%s",sound_dir(),sound);
    sprintf(playc,play_cmd(),path);
#ifdef __CYGWIN__
    strcpy(command,playc);
#else
    /* Find out if we are running on host */
    if(host && strlen(host) && strcmp(getenv("HOST"), host))
      sprintf(command,"rsh %s -n '(%s)' >&- 2>&-",host,playc);
    else
      sprintf(command,"tcsh -c '(%s)' >&- 2>&-",playc);
#endif

    system(command);
    exit(0);
  }
}

static void Sound(train_line, sound)
     tTrainLine train_line;
     char *sound;
{
  char host[100], *display_name;
  display_name = DisplayString(XtDisplay(train_line->top));
  strcpy(host, display_name);
  {
    char *cl = strstr(host,":");
    if(cl) *cl = '\0';
  }
  play(sound, host);
}

static void Sounds(train_line,table,n)
     tTrainLine train_line;
     SoundTable table[];
     int n;
{
  int i;

#define DIGS 0xffffff
#ifdef SOLARIS
  double s = rand() % DIGS * 1.0 /DIGS;
#else
  double s = random() % DIGS * 1.0 / DIGS;
#endif

  for(i=0;i<n;i++) {
    if(s < table[i].p) {
      Sound(train_line,table[i].fname);
      return;
    }
    s -= table[i].p;
  }
}
    
#define SOUNDS(n,t) void n(train_line) \
   tTrainLine train_line; \
{ \
  Sounds(train_line,(t),XtNumber(t)); \
}

SOUNDS(SoundTrain,startsound)
SOUNDS(SoundFastTrain,faststartsound)
SOUNDS(SoundTrainCrash,traincrashsound)
SOUNDS(SoundDerailCrash,derailcrashsound)
SOUNDS(SoundStopCrash,stopcrashsound)
