CFLAGS = -Wall -Werror -Wextra
CC = gcc

all:bin/game_of_life

bin/game_of_life: obj/game_of_life.o
	$(CC) $(CFLAGS) obj/game_of_life.o -o $@

obj/game_of_life.o:src/game_of_life.c
	$(CC) $(CFLAGS) -c src/game_of_life.c -o $@

run:
	./bin/game_of_life

clean:
	find . -name "*.d" -exec rm {} \;
	find . -name "*.o" -exec rm {} \;
	find . -name "*.a" -exec rm {} \;
	rm bin/game_of_life

rebuild: clean all

.PHONY: clean run rebuild all