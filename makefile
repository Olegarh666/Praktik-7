# Makefile для игры "Угадай число"

CC = gcc
CFLAGS = -Wall -Wextra
TARGET = guess_game
SRC = guess_game.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
