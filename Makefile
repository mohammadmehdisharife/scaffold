CC = gcc
TARGET = scaffold

MINGW32 = i686-w64-mingw32-gcc
MINGW64 = x86_64-w64-mingw32-gcc

all: build win32 win64

build:
	mkdir -p build
	$(CC) $(TARGET).c -o ./build/$(TARGET)

win32:
	mkdir -p build
	$(MINGW32) $(TARGET).c -o ./build/$(TARGET)_win32.exe

win64:
	mkdir -p build
	$(MINGW64) $(TARGET).c -o ./build/$(TARGET)_win64.exe

clean:
	rm -rf build

.PHONY: all build win32 win64 clean
