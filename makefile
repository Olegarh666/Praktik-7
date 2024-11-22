# Makefile для игры "Угадай число"

CC = gcc
CFLAGS = -Wall -Wextra
TARGET = ex1
TARGET2 = ex2
SRC = Ex1.c
SRC2 = Ex2.c

all: $(TARGET) $(TARGET2)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET2): $(SRC2)
	$(CC) $(CFLAGS) -o $@ $^
run_ex1: $(TARGET)
	@echo "Запуск программы с сигналами:"
	./$(TARGET) 100

run_ex2: $(TARGET2)
	@echo "Запуск программы с очередями сообщений:"
	./$(TARGET2) 100

clean:
	rm -f $(TARGET) $(TARGET2)
.PHONY: all run_ex1 run_ex2 clean
