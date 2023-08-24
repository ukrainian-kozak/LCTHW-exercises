CC = gcc
CFLAGS=-Wall -g -DNDEBUG


OBJS = ex22.o ex22_main.o

TARGET = a.out

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

ex22.o: ex22.c ex22.h
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

ex22_main.o: ex22_main.c ex22.h
	$(CC) $(CFLAGS) -c ex22_main.c -o ex22_main.o

clean:
	rm -rf $(OBJS) $(TARGET)

