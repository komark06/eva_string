NORMAL = \033[m
CYAN = \033[0;36m
CC = gcc
DFLAG = -fno-omit-frame-pointer -O2 -Wextra -Wall -Winline -pedantic -std=c99
test = TEST

all: compiler.h simpletest.h eva_alloc.h eva_string.c
	$(CC) -o $(test) eva_string.c $(DFLAG) -DEVA_TEST
	@echo "Enter $(CYAN)./$(test)$(NORMAL) to test."

debug: compiler.h simpletest.h eva_alloc.h eva_string.c test.c
	$(CC) -o $(test) eva_string.c test.c $(DFLAG)

.PHONY:clean
clean:
	rm -f $(test) *.o a.out
