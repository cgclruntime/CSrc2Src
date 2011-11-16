TARGET = SSCA2
CC = g++
LIBS = -lm
FLAGS = -O3
# -xtarget=ultraT1 -xarch=v9b -xO3

OBJS = SSCA2.o init.o utils.o genScalData.o \
    computeGraph.o getStartLists.o findSubGraphs.o \
    betweennessCentrality.o

all: $(OBJS) defs.h Makefile
	$(CC) $(FLAGS) -o $(TARGET) $(OBJS) $(LIBS)

.c.o: defs.h Makefile
	$(CC) $(FLAGS) -c $<

clean:
	rm -f *.o *~ $(TARGET) core*
