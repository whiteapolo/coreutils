CC = cc
RELEASE_CFLAGS = -Wall -Wextra -O3
DEV_CFLAGS = -Wall -Wextra -O0 -g
TARGET = exe

all: release

release:
	$(CC) $(RELEASE_CFLAGS) -o $(TARGET) main.c

dev:
	$(CC) $(DEV_CFLAGS) -o $(TARGET) main.c

clean:
	rm -f $(TARGET)

.PHONY: all clean release dev
