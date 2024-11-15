# Makefile для игры "Угадай число"

CC = gcc
CFLAGS = -Wall -Wextra
TARGET = ex1
SRC = Ex1.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
