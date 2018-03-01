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

BugsInTeammateCode.txt: unittest1.c unittest2.c unittest3.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c unittest4.c randomtestadventurer.c randomtestcard1.c randomtestcard2.c dominion.o rngs.o
	echo "Result for running the unit test:" > BugsInTeammateCode.txt
	
	echo "Unittest1.c" >>BugsInTeammateCode.txt
	gcc -o utest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	./utest1 >> BugsInTeammateCode.txt
	#gcov -f -b dominion.c >> BugsInTeammateCode.txt

	echo "Unittest2.c" >>BugsInTeammateCode.txt
	gcc -o utest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	./utest2 >> BugsInTeammateCode.txt
	#gcov -f -b dominion.c >> BugsInTeammateCode.txt

	echo "Unittest3.c" >>BugsInTeammateCode.txt
	gcc -o utest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
	./utest3 >> BugsInTeammateCode.txt
	#gcov -f -b dominion.c >> BugsInTeammateCode.txt

	echo "Unittest4.c" >>BugsInTeammateCode.txt
	gcc -o utest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
	./utest4 >> BugsInTeammateCode.txt
	#gcov -f -b dominion.c >> BugsInTeammateCode.txt

	echo "cardtest1.c" >>BugsInTeammateCode.txt
	gcc -o ctest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	./ctest1 >> BugsInTeammateCode.txt
	gcov -f -b dominion.c >> BugsInTeammateCode.txt

	echo "cardtest2.c" >>BugsInTeammateCode.txt
	gcc -o ctest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
	./ctest2  >> BugsInTeammateCode.txt
	gcov -f -b dominion.c >> BugsInTeammateCode.txt

	echo "cardtest3.c" >>BugsInTeammateCode.txt
	gcc -o ctest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
	./ctest3  >> BugsInTeammateCode.txt
	gcov -f -b dominion.c >> BugsInTeammateCode.txt

	echo "cardtest4.c" >>BugsInTeammateCode.txt
	gcc -o ctest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
	./ctest4  >> BugsInTeammateCode.txt
	gcov -f -b dominion.c >> BugsInTeammateCode.txt

	echo "Result for running the Random test1:" >>BugsInTeammateCode.txt
	
	echo "Randomtestadventurer.c" >>BugsInTeammateCode.txt
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	./randomtestadventurer >>BugsInTeammateCode.txt
	gcov -f -b dominion.c >>BugsInTeammateCode.txt

	echo "Result for running the Random test2:" >>BugsInTeammateCode.txt
	
	echo "Randomtestcard1.c" >>BugsInTeammateCode.txt
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard1 >>BugsInTeammateCode.txt
	gcov -f -b dominion.c >>BugsInTeammateCode.txt

	echo "Result for running the Random test3:" >>BugsInTeammateCode.txt
	
	echo "Randomtestcard2.c" >>BugsInTeammateCode.txt
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard2 >>BugsInTeammateCode.txt
	gcov -f -b dominion.c >>BugsInTeammateCode.txt

all: playdom player testDrawCard testBuyCard badTestDrawCard BugsInTeammateCode.txt

clean:
	rm -f *.o playdom.exe playdom player player.exe *.gcov *.gcda *.gcno *.so testDrawCard testDrawCard.exe testBuyCard badTestDrawCard utest1 utest2 utest3 utest4 ctest1 ctest2 ctest3 ctest4 randomtestcard1 randomtestcard2 randomtestadventurer