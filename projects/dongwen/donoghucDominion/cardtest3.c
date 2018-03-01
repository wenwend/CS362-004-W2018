/*
 * cardtest3.c
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
    int c1=0,c2=0,c3=0,handPos =0, bonus=0;
    int newCard,bug=0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};

    //test great_hall card,
    printf("Test against great_hall card:\n");

    initializeGame(numPlayer, k, seed, g); // now each player have 5 hands by hands.
    printf("Starting with handCount=%d, deckCount=%d, discardCount=%d, "
        		"number of Action =%d, score =%d\n",g->handCount[0],g->deckCount[0],
        		g->discardCount[0],g->numActions,scoreFor(0,g));

    printf("\n1: Number of handCount should stay the same!\n");
    memcpy(gCopy,g,sizeof(struct gameState));
    cardEffect(great_hall,c1,c2,c3,gCopy,handPos,bonus);
    if(gCopy->handCount[thisPlayer] !=g->handCount[thisPlayer]){
    	printf("Fail:the handCount%d doesn't match %d",gCopy->handCount[thisPlayer],g->handCount[thisPlayer]);
    	bug++;
    }
    if(my_assert(bug,0))
    	printf("Test 1 Passed!\n");
    else
    	printf("Test 1 Failed!\n");




    printf("2: Number of deckCount and discarded card should be decremented by 1 !\n");
    memcpy(gCopy,g,sizeof(struct gameState));
    bug=0;
    cardEffect(great_hall,c1,c2,c3,gCopy,handPos,bonus);
    if(gCopy->deckCount[thisPlayer]+gCopy->discardCount[thisPlayer]!=g->deckCount[thisPlayer]+g->discardCount[thisPlayer] -1 )
    {
    	bug++;
    	printf("Fail: deckCount =% doesn't decrement",g->deckCount);
    }
    if(my_assert(bug,0))
        	printf("Test 2 Passed!\n");
        else
        	printf("Test 2 Failed!\n");

    printf("3: Number of actions should be at most +1 more!\n");
    memcpy(gCopy,g,sizeof(struct gameState));
    bug=0;
    cardEffect(great_hall,c1,c2,c3,gCopy,handPos,bonus);
    if(gCopy->numActions != g->numActions+1){
    	bug++;
    	printf("Failed: Actions =%d does not increment",g->numActions);
    }
    if(my_assert(bug,0))
        	printf("Test 3 Passed!\n");
        else
        	printf("Test 3 Failed!\n");

    printf("4: Number of score should be +1 !\n");
    memcpy(gCopy,g,sizeof(struct gameState));
    cardEffect(great_hall,c1,c2,c3,gCopy,handPos,bonus);
    bug=0;
    if(scoreFor(thisPlayer,gCopy) != scoreFor(thisPlayer,g)+1)
    {
    	bug++;
    	printf("Failed: Score = %d didn't incremental by 1",scoreFor(thisPlayer,g));
    }
    if(my_assert(bug,0))
        	printf("Test 4 Passed!\n");
        else
        	printf("Test 4 Failed!\n");

    printf("5: The rest of the player should not be effected!\n");
    memcpy(gCopy,g,sizeof(struct gameState));
	gCopy->whoseTurn=0;
    bug=0;
    cardEffect(great_hall,c1,c2,c3,gCopy,handPos,bonus);

    for(p=1;p<numPlayer;p++){
    	endTurn(gCopy);
    	if(gCopy->numActions == 1 && gCopy->handCount[p] == 5)
    	{
    		printf("Player %d Passed!\n",p);
    	}
    	else{
    		printf("Player %d Failed!action=%d,handCount=%d\n rest:%d,%d:%d,%d,%d\n",p,gCopy->numActions,gCopy->handCount[p],gCopy->deckCount[p],gCopy->discardCount[p],g->deckCount[p],g->discardCount[p]);
    		bug++;
    	}

    }
    if(my_assert(bug,0))
    	printf("Test 5 Passed!\n");
    else
        printf("Test 5 Failed!\n");

    printf("All tests passed!\n");
	return 0;
}






