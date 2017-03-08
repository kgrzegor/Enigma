CC = gcc
CFLAGS  = -g -Wall
TARGET = main
all: $(TARGET)

#cos

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c
clean:
	$(RM) $(TARGET)
