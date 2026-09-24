CC = cc
BASE_FLAGS = -Wall -Wextra -I../zlib/include
RELEASE_CFLAGS = $(BASE_FLAGS) -O3
DEV_CFLAGS = $(BASE_FLAGS) -O0 -g
TARGET = tr

all: release

release:
	make -C ../zlib
	$(CC) $(RELEASE_CFLAGS) -o $(TARGET) main.c ../zlib/libzatar.a

dev:
	make dev -C ../zlib
	$(CC) $(DEV_CFLAGS) -o $(TARGET) main.c ../zlib/libzatar.a

clean:
	rm -f $(TARGET)

.PHONY: all clean release dev
