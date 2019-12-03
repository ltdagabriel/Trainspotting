INSTDIR = .
# FreeBSD
#CFLAGS = -g -I/usr/X11R6/include -I/usr/compat/linux -DLINUX
# Linux and Cygwin
CFLAGS  = -g -Wall -DLINUX
# Solaris
#CFLAGS = -g -Wall -DSOLARIS
# Irix
#CFLAGS = -g -Wall -DLINUX
CC      = gcc

OBJ = tsim.o train.o bitmap.o Sprite.o Graph.o file.o AddToggleWidget.o DrawingPalette.o DialogPopup.o timer.o sound.o pipe.o resources.o strdupl.o BitmapDirectory.o errcheck.o

SRC = AddToggleWidget.c BitmapDirectory.c DialogPopup.c DrawingPalette.c Graph.c Sprite.c bitmap.c errcheck.c file.c pipe.c resources.c sound.c strchr.c strdupl.c strpbrk.c strtok.c timer.c train.c tsim.c

# OBJ = $(SRC:.c:.o)

tsim: $P $(OBJ)
	$(CC) -o tsim $(OBJ) -L/usr/X11R6/lib  -lXaw -lXt -lXmu -lX11 -lXext 
# -lm -lresolve

Sprite.o: Sprite.h SpriteP.h
Graph.o: Graph.h GraphP.h
train.o: train.h trainP.h bitmap.h
test.o: train.h file.h
file.o: train.h trainP.h file.h
DrawingPalette.o: train.h trainP.h file.h
timer.o: train.h trainP.h resources.h
pipe.o: train.h trainP.h
resources.o: resources.h
BitmapDirectory.o: BitmapDirectory.h
bitmap.o: BitmapDirectory.h resources.h
tsim.o: Sprite.h train.h file.h resources.h
sound.o: train.h trainP.h resources.h
trainP.h: BitmapDirectory.h
	touch trainP.h

clean:
	rm -f $(OBJ)
