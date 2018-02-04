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

unittestresults.out: unittest1.c unittest2.c unittest3.c cardtest1.c unittest4.c dominion.o rngs.o
	echo "Result for running the unit test:" > unittestresults.out
	
	echo "Unittest1.c" >>unittestresults.out
	gcc -o utest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	./utest1 >> unittestresults.out
	gcov -f -b unittest1.c >> unittestresults.out

	echo "Unittest2.c" >>unittestresults.out
	gcc -o utest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	./utest2 >> unittestresults.out
	gcov -f -b unittest2.c >> unittestresults.out

	echo "Unittest3.c" >>unittestresults.out
	gcc -o utest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
	./utest3 >> unittestresults.out
	gcov -f -b unittest3.c >> unittestresults.out

	echo "Unittest4.c" >>unittestresults.out
	gcc -o utest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
	./utest4 >> unittestresults.out
	gcov -f -b unittest4.c >> unittestresults.out

	echo "cardtest1.c" >>unittestresults.out
	gcc -o ctest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	./ctest1 >> unittestresults.out	
	gcov -f -b cardtest1.c >> unittestresults.out

	echo "cardtest2.c" >>unittestresults.out
	gcc -o ctest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
	./ctest2  >> unittestresults.out
	gcov -f -b cardtest2.c >> unittestresults.out

	echo "cardtest3.c" >>unittestresults.out
	gcc -o ctest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
	./ctest3  >> unittestresults.out
	gcov -f -b cardtest3.c >> unittestresults.out

	echo "cardtest4.c" >>unittestresults.out
	gcc -o ctest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
	./ctest4  >> unittestresults.out
	gcov -f -b cardtest4.c >> unittestresults.out

	echo "dominion coverage" >>unittestresults.out
	gcov -f -b dominion.c >>unittestresults.out
	

all: playdom player testDrawCard testBuyCard badTestDrawCard unittestresults.out

clean:
	rm -f *.o playdom.exe playdom player player.exe *.gcov *.gcda *.gcno *.so testDrawCard testDrawCard.exe testBuyCard badTestDrawCard utest1 utest2 utest3 utest4 ctest1 ctest2 ctest3 ctest4 
