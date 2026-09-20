CC = cc
RELEASE_CFLAGS = -Wall -Wextra -O3 -I../zlib/include
DEV_CFLAGS = -Wall -Wextra -O0 -g -I../zlib/include
TARGET = pgrep

all: release

release:
	make -C ../zlib
	$(CC) $(RELEASE_CFLAGS) -o $(TARGET) main.c ../zlib/libzatar.a

dev:
	make dev -C ../zlib
	$(CC) $(DEV_CFLAGS) -o $(TARGET) main.c ../zlib/libzatar.a

clean:
	rm -f $(TARGET)

.PHONY: all clean
