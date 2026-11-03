CC = x86_64-w64-mingw32-gcc 
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

TARGET = lzw.exe
SRC = src/main.c
HEADER = include/main.h

$(TARGET): $(SRC) $(HEADER)
					$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean: 
				rm -f $(TARGET)

.PHONY: clean
