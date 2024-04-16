MODE = l
CFLAGS = -0 -m$(MODE) -wx

EXEFILE = ezft.exe

all: $(EXEFILE)

$(EXEFILE): ezft.c vga.c
	wcl $(CFLAGS) -bt=dos $<

clean: .symbolic
	del *.obj
	del *.err
	del *.exe
