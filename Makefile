CFLAGS = -Wall -Werror -Wextra
CC = gcc
TARGET = bin/game_of_life

all:$(TARGET)

$(TARGET): obj/game_of_life.o
	$(CC) $(CFLAGS) obj/game_of_life.o -o $@

obj/game_of_life.o:src/game_of_life.c
	$(CC) $(CFLAGS) -c src/game_of_life.c -o $@

run:
	./$(TARGET)

clean:
	find . -name "*.d" -exec rm {} \;
	find . -name "*.o" -exec rm {} \;
	find . -name "*.a" -exec rm {} \;
	rm $(TARGET)

rebuild: clean all

.PHONY: clean run rebuild all