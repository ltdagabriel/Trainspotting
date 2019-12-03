#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <X11/Intrinsic.h>
#include <X11/Xlibint.h>
#include "BitmapDirectory.h"

/* prototypes for gcc */
extern int errcheck(int i, int ec, char *s);

typedef struct _tBitmapDirectory {
  tBitmapEntry bitmap_entry;
  tBitmapDirectory next;
} sBitmapDirectory;

#define NEW(o) ((o*)(malloc(sizeof(o))))
char *strdupl();

static tBitmapDirectory FindBitmap(name, bd)
     String name;
     tBitmapDirectory bd;
{
  tBitmapDirectory entry;
  for(entry = bd; entry; entry = entry->next)
    if(!strcmp(name, entry->bitmap_entry.name))
      return(entry);
  return(NULL);
}

static tBitmapDirectory AddFile(w, file, name, bd)
     Widget w;
     String file, name;
     tBitmapDirectory bd;
{
  int dummy;
  tBitmapEntry bitmap_entry;
  tBitmapDirectory entry;
  Window win = XRootWindowOfScreen(XtScreen(w));

  if(XReadBitmapFile(XtDisplay(w), win, file,
		     &bitmap_entry.width, &bitmap_entry.height,
		     &bitmap_entry.bitmap,
		     &dummy, &dummy) !=BitmapSuccess) 
    return bd; /* Ignore invalid bitmap files */
  if(!(entry = FindBitmap(name, bd))) {
    /* create new entry */
    entry = NEW(sBitmapDirectory);
    entry->next = bd;
    bd = entry;
  } /* else replace existent entry! */
  entry->bitmap_entry = bitmap_entry;
  entry->bitmap_entry.name = strdupl(name);
  return bd;
}

tBitmapDirectory BDAddDirectory(w, directory, bd)
     Widget w;
     String directory;
     tBitmapDirectory bd;
{
  DIR *dir;
  struct dirent *dp;
  struct stat statbuf;
  char fullfilename[BUFSIZE];

  dir = (DIR *)errcheck((int)opendir(directory), (int)NULL, directory);
  for(dp = readdir(dir); dp; dp = readdir(dir))
    if(dp->d_name[0] != '.') { /* Ignore files starting with '.' */
      sprintf(fullfilename, "%s/%s", directory, dp->d_name);
      stat(fullfilename, &statbuf);
      if(statbuf.st_mode & S_IFDIR)
	/* Subdirectory, so add it... */
	bd = BDAddDirectory(w, fullfilename, bd);
      else
	bd = AddFile(w, fullfilename, dp->d_name, bd);
    }
  (void)errcheck((int)closedir(dir), -1, directory);
  return(bd);
}

void BDFindBitmap(name, bitmap_entry, bd)
     String name;
     tBitmapEntry **bitmap_entry;
     tBitmapDirectory bd;
{
  tBitmapDirectory entry;
  if((entry = FindBitmap(name, bd))) {
    *bitmap_entry = &(entry->bitmap_entry);
  } else
    *bitmap_entry = NULL;
}

void BDBitmaps(entry, bitmap_entry, bd)
     tBitmapDirectory *entry;
     tBitmapEntry **bitmap_entry;
     tBitmapDirectory bd;
{
  if(*entry)
    *entry = (*entry)->next;
  else
    *entry = bd;
  if(*entry) {
    *bitmap_entry = &((*entry)->bitmap_entry);
  } else
    *bitmap_entry = NULL;
}
