GCC = gcc
RM = rm
TARGET = synch
CPPFLAGS = -Wall -Wextra -lpthread
OBJECTS = synch.o Queue.o process.o

all: $(OBJECTS)
	$(GCC) $(OBJECTS) -o $(TARGET) $(CPPFLAGS)

Queue.o: Queue.c
	$(GCC) $(CPPFLAGS) -c Queue.c -o Queue.o

process.o: process.c
	$(GCC) $(CPPFLAGS) -c process.c -o process.o

synch.o: synch.c
	$(GCC) $(CPPFLAGS) -c synch.c -o synch.o

clean:
	$(RM) $(OBJECTS) $(TARGET)