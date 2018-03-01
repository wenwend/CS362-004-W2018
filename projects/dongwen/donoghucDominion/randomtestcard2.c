/*
 * randomtestcard2.c
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
#include <time.h>
#include <math.h>
#include "my_assert.c"

#define NOISY_TEST 1
//global fails counter
int handCountFails=0;
int decknDiscardCountFails=0;
int actionCountFails=0;
int scoreCountFails=0;
int playerEffectedFails=0;

void checkGreatHall(int numPlayer){
	int p;
		struct gameState *g = newGame(), *gCopy=newGame();
	    int seed = 1000;

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
	    if(bug!=0) handCountFails++;




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
	    if(bug!=0) decknDiscardCountFails++;

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
	    if(bug!=0) actionCountFails++;

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
	    if(bug!=0) scoreCountFails++;

	    printf("5: The rest of the player should not be effected!\n");
	    memcpy(gCopy,g,sizeof(struct gameState));
		gCopy->whoseTurn=0;
	    bug=0;
	    cardEffect(great_hall,c1,c2,c3,gCopy,handPos,bonus);

	    for(p=1;p<numPlayer;p++){
	    	endTurn(gCopy);
	    	if(gCopy->numActions == 1 && gCopy->deckCount[p]+gCopy->discardCount[p]==g->deckCount[p]+g->discardCount[p] && gCopy->handCount[p] == 5)
	    	{
	    		printf("Player %d Passed!\n",p);
	    	}
	    	else{
	    		printf("Player %d Failed!action=%d,handCount=%d\n rest:%d,%d:%d,%d\n",p,gCopy->numActions,gCopy->handCount[p],gCopy->deckCount[p],gCopy->discardCount[p],g->deckCount[p],g->discardCount[p]);
	    		bug++;
	    	}

	    }
	    if(my_assert(bug,0))
	    	printf("Test 5 Passed!\n");
	    else
	        printf("Test 5 Failed!\n");
	    if(bug!=0) playerEffectedFails++;
}
int main(){
	srand(time(NULL));
	printf("FILE: randomtestcard2.c \n");
	int iter = 100,i=0;
	for(;i<iter;i++){
		int player = rand()%(MAX_PLAYERS-1) +2;
		checkGreatHall(player);
	}
	int total = handCountFails+decknDiscardCountFails+actionCountFails+scoreCountFails+playerEffectedFails;

	if(total ==0)
			printf("Passing Random Test!");
		else {
			printf("Random Test Report:\n");
			printf("Card in Hand Counting Fails: %d times.\n",handCountFails);
			printf("Card in deck and Discard Pile Counting Fails: %d times.\n",decknDiscardCountFails);
			printf("Action +1 or more Counting Fails: %d times.\n",actionCountFails);
			printf("Score Counting +1 Fails: %d times.\n",scoreCountFails);
			printf("Other player effected Fails: %d times.\n",playerEffectedFails);
		}
		printf("All tests passed!\n");
	return 0;
}


