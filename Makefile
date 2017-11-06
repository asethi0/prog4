CC = gcc

CFlags = -Wall -g

LD = gcc

LDFlags = 

mytar: mytar.o
	$(LD) -o mytar mytar.o

mytar.o: driver.c
	$(LD) -c driver.c tar_funcs.c Mytar.c tar.h

clean:
	echo Cleaning up!
	$(RM) *.o *~ $(mytar)	
