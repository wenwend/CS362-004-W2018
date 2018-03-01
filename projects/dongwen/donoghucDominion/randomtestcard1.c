/*
 * randomtestcard1.c
 *
 *  Created on: Feb 15, 2018
 *      Author: wenwen
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "my_assert.c"

#define NOISY_TEST 1
//global random checker
int cardEffectFails=0;
int playerEffectedFails=0;
int supplyCountFails=0;

void checkplaySmithy(int numPlayer){
	int p;
	struct gameState *g = newGame(), *gCopy=newGame();
    int seed = 1000;

    int thisPlayer=0;
    int handPos =0, bonus=0;
    int newCard,bug=0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};

    //test playSmithy() function if draw three cards
    printf("Test against playSmithy():\n");

    initializeGame(numPlayer, k, seed, g);
    memcpy(gCopy,g,sizeof(struct gameState));
    newCard =3;

    smithy_function(thisPlayer,gCopy,handPos);
    printf("\nTest if Smithy get your hand with +3 cards!\n");


    for(p=0;p<numPlayer;p++){
#if(NOISY_TEST)

    	printf("Start: Player %d hand count = %d, deck count =%d,discard count =%d\n",p,g->handCount[p],g->deckCount[p],g->deckCount[p]);
#endif
    	if(p==thisPlayer){
    		if(gCopy->handCount[p] == g->handCount[p] + newCard)  //draw +3 cards
    		{
    			printf("Pass: handCount increased properly.\n ");
    		}
    		else{
    			printf("Fail on hand count!%d != %d.\n ",gCopy->handCount[p],g->handCount[p]+newCard);
    			bug++;
    		}
    		if(gCopy->deckCount[p] == g->deckCount[p]-newCard)
    		{
    			printf("Pass: deck count decreased properly.\n ");
    		}
    		else{
    			printf("Fail on deck count!%d != %d.\n ",gCopy->deckCount[p],g->deckCount[p]);
    			bug++;
    		}

    		if(gCopy->discardCount[p] == g->discardCount[p])
    		{
       			printf("Pass: deck count decreased properly.\n ");
    		}
    		else{
    		    printf("Fail on discard count!%d != %d.\n ",gCopy->discardCount[p],g->discardCount[p]);
    		    bug++;
    		}
    	}
    	else{
    		if(gCopy->handCount[p]==g->handCount[p] && gCopy->deckCount[p]== g->deckCount[p] && gCopy->discardCount[p]==g->discardCount[p])
    		{
    			printf("Pass: deck count decreased properly for none-current player %d.\n ",p);
    		}
    		else{
    			printf("Fail on none player's count!\n");
    			bug++;
    		}
    	}

    }
	my_assert(bug,0);
	if(bug!=0) cardEffectFails++;
#if(NOISY_TEST)
    	printf("Passing the test of +3 cards by Smithy.\n");
#endif


    //Test if the Card still in player's hand after used.
    printf("\nWe can also test if the Smithy card effect the player's deck\n");
    handPos=0;bug=0;thisPlayer=0;
    memcpy(gCopy,g,sizeof(struct gameState));
    smithy_function(thisPlayer,gCopy,handPos);
    for(p=0;p<gCopy->handCount[thisPlayer];p++){
    	if(gCopy->hand[thisPlayer][p]==smithy)
    	{
    		bug++;
    		printf("Fail! Smithy is not discard after use!\n");
    	}
    }
	my_assert(bug,0);
	if(bug!=0) playerEffectedFails++;
#if(NOISY_TEST)
	printf("Pass: discarding smithy card after using it.\n");
#endif


    printf("\n We can also test if the Smithy card effect the supply deck\n");
    handPos=0;bug=0;
    memcpy(gCopy,g,sizeof(struct gameState));
    smithy_function(thisPlayer,gCopy,handPos);
    for(p=0;p<25;p++){
    	if(gCopy->supplyCount[p]!=g->supplyCount[p]){
    		bug++;
    		printf("Fail! supply count checked after smithy Card effect!\n");
    	}
    }
	my_assert(bug,0);
	if(bug!=0) supplyCountFails++;
#if(NOISY_TEST)
	printf("Pass: unchanged supply count after using Smithy.\n");
#endif

}
int main(){
	srand(time(NULL));
	printf("FILE: randomtestcard1.c \n");
	int iter = 100,i=0;
	for(;i<iter;i++){
		int player = rand()%(MAX_PLAYERS-1) +2;
		checkplaySmithy(player);
	}
	int total =cardEffectFails+playerEffectedFails+supplyCountFails;
	if(total ==0)
			printf("Passing Random Test!\n");
		else {
			printf("Random Test Report:\n");
			printf("Card Effects of adding 3 cards Fails: %d times.\n",cardEffectFails);
			printf("Card in Supply Counting Fails: %d times.\n",supplyCountFails);
			printf("Other player effected Fails: %d times.\n",playerEffectedFails);
		}
	printf("All tests passed!\n");
	return 0;
}

