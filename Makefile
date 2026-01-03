CC = gcc
TARGET = scaffold

all: build win32 win64

build:
	mkdir -p build
	$(CC) $(TARGET).c -o ./build/$(TARGET)

win32:
	mkdir -p build
	$(CC) $(TARGET).c -o ./build/$(TARGET)_win32.exe -m32

win64:
	mkdir -p build
	$(CC) $(TARGET).c -o ./build/$(TARGET)_win64.exe -m64

clean:
	rm -rf build

.PHONY: all build win32 win64 clean
