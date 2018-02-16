CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testBuyCard.c dominion.o rngs.o
	gcc -o testBuyCard -g  testBuyCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

randomtestadventurer.out: randomtestadventurer.c dominion.o rngs.o
	echo "Result for running the Random test:" >randomtestadventurer.out
	
	echo "Randomtestadventurer.c" >>randomtestadventurer.out
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	./randomtestadventurer >>randomtestadventurer.out
	gcov -f -b dominion.c >>randomtestadventurer.out
randomtestcard1.out: randomtestcard1.c dominion.o rngs.o
	echo "Result for running the Random test:" >randomtestcard1.out
	
	echo "Randomtestcard1.c" >>randomtestcard1.out
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard1 >>randomtestcard1.out
	gcov -f -b dominion.c >>randomtestcard1.out

randomtestcard2.out: randomtestcard2.c dominion.o rngs.o
	echo "Result for running the Random test:" >randomtestcard2.out
	
	echo "Randomtestcard2.c" >>randomtestcard2.out
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard2 >>randomtestcard2.out
	gcov -f -b dominion.c >>randomtestcard2.out

all: playdom player testDrawCard testBuyCard badTestDrawCard randomtestadventurer.out randomtestcard1.out randomtestcard2.out

clean:
	rm -f *.o playdom.exe playdom player player.exe *.gcov *.gcda *.gcno *.so testDrawCard testDrawCard.exe testBuyCard badTestDrawCard randomtestcard1 randomtestcard2 randomtestadventurer