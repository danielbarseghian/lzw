CC = cc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

TARGET = lzw
SRC = include/main.c
HEADER = include/main.h

$(TARGETe): $(SRC) $(HEADER)
					$(CC) ($CFLAGS) $(SRC) -o $(TARGET)

clean: 
				rm -f $(TARGET)

.PHONY: clean
