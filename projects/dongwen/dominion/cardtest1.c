/*
 * cardtest1.c
 *
 *  Created on: Feb 3, 2018
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

int main(){
	int p;
	struct gameState *g = newGame(), *gCopy=newGame();
    int seed = 1000;
    int numPlayer = MAX_PLAYERS;
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

    playSmithy(gCopy,handPos);
    printf("\n1: Test if Smithy get your hand with +3 cards!\n");


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
    if(my_assert(bug,0))
    	printf("Test 1 Passed!\n");
    else
    	printf("Test 1 Failed!\n");


    //Test if the Card still in player's hand after used.
    printf("\n2: We can also test if the Smithy card effect the player's deck\n");
    handPos=0;bug=0;thisPlayer=0;
    memcpy(gCopy,g,sizeof(struct gameState));
    playSmithy(gCopy,handPos);
    for(p=0;p<gCopy->handCount[thisPlayer];p++){
    	if(gCopy->hand[thisPlayer][p]==smithy)
    	{
    		bug++;
    		printf("Fail! Smithy is not discard after use!\n");
    	}
    }
    if(my_assert(bug,0))
    	printf("Test 2 Passed!\n");
    else
    	printf("Test 2 Failed!\n");


    printf("\n3: We can also test if the Smithy card effect the supply deck\n");
    handPos=0;bug=0;
    memcpy(gCopy,g,sizeof(struct gameState));
    playSmithy(gCopy,handPos);
    for(p=0;p<25;p++){
    	if(gCopy->supplyCount[p]!=g->supplyCount[p]){
    		bug++;
    		printf("Fail! supply count checked after smithy Card effect!\n");
    	}
    }
    if(my_assert(bug,0))
    	printf("Test 3 Passed!\n");
    else
    	printf("Test 3 Failed!\n");


	printf("\nAll tests passed!\n");
	return 0;


}




