CC=gcc
CFLAGS= -Wall -g -fprofile-arcs -ftest-coverage

all: tests
tests.o: tests.c
	${CC} -c tests.c -o tests.o ${CFLAGS}
hashtables.o: hashtables.c
	${CC} -c hashtables.c -o hashtables.o ${CFLAGS}
tests: tests.o hashtables.o
	${CC} hashtables.o tests.o -o tests ${CFLAGS}
clean:
	@rm -rf *.o *.gcno *.gcda *.gcov tests 2&>/dev/null
tar:
	tar czvf ../hashtables.tgz ../hashtables
