CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -pedantic
LDFLAGS = -lm
OBJS    = main.o artemis.o validaciones.o
TARGET  = artemis

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

main.o: main.c artemis.h validaciones.h
artemis.o: artemis.c artemis.h validaciones.h
validaciones.o: validaciones.c validaciones.h

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
