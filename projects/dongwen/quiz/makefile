CFLAGS = -Wall -fpic -coverage -lm -std=c99

default: test

test: testme.c
	#echo "Result for running testme:" > test.out
	#echo "RandomTest for testme.c:">>test.out
	gcc -o test testme.c $(CFLAGS)
	./test
	#gcov testme.c >>test.out


clean:
	rm  test *.gcda *.gcno *.gcov
