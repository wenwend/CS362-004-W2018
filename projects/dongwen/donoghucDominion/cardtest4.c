/*
 * cardtest4.c
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
	int c1=0,c2=0,c3=0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};

    //test playVillage() function
    printf("Test against playVillage():\n");

    initializeGame(numPlayer, k, seed, g); // now each player have 5 hands by hands.
    printf("Starting with handCount=%d, deckCount=%d, discardCount=%d, "
            		"number of Action =%d\n",g->handCount[0],g->deckCount[0],
            		g->discardCount[0],g->numActions);

    printf("\n1: Number of handCount should stay the same!\n");
    memcpy(gCopy,g,sizeof(struct gameState));
    cardEffect(village,c1,c2,c3,gCopy,handPos,bonus);
    if(gCopy->handCount[thisPlayer] !=g->handCount[thisPlayer]){
        	printf("Fail:the handCount%d doesn't match %d",gCopy->handCount[thisPlayer],g->handCount[thisPlayer]);
        	bug++;
        }
    if(my_assert(bug,0))
    	printf("Test 1 Passed!\n");
    else
        printf("Test 1 Failed!\n");


    printf("2: Number of deck should be at decremented by 1!\n");
    memcpy(gCopy,g,sizeof(struct gameState));
    bug=0;
    //playVillage(gCopy,handPos);
	cardEffect(village,c1,c2,c3,gCopy,handPos,bonus);

    if(gCopy->deckCount[thisPlayer]+gCopy->discardCount[thisPlayer]!=g->deckCount[thisPlayer]+g->discardCount[thisPlayer] -1 )
        {
        	bug++;
        	printf("Fail: deckCount =% doesn't decrement",g->deckCount);
        }
    if(my_assert(bug,0))
    	printf("Test 2 Passed!\n");
    else
        printf("Test 2 Failed!\n");

    printf("3: Number of actions should be at most +2 more!\n");
    memcpy(gCopy,g,sizeof(struct gameState));
    bug=0;
   cardEffect(village,c1,c2,c3,gCopy,handPos,bonus);

    if(gCopy->numActions != g->numActions+2){
        	bug++;
        	printf("Failed: Actions does not increment by 2:%d-%d",gCopy->numActions,g->numActions);
        }
    if(my_assert(bug,0))
    	printf("Test 3 Passed!\n");
    else
        printf("Test 3 Failed!\n");


    printf("4: Number of supply should be +1 !\n");
    memcpy(gCopy,g,sizeof(struct gameState));
    bug=0;
    cardEffect(village,c1,c2,c3,gCopy,handPos,bonus);

    for(p=0;p<25;p++){
        	if(gCopy->supplyCount[p]!=g->supplyCount[p]){
        		bug++;
        		printf("Fail! supply count checked after Villiage Card used!\n");
        	}
        }
    if(my_assert(bug,0))
    	printf("Test 4 Passed!\n");
    else
        printf("Test 4 Failed!\n");


    printf("5: The rest of the player should not be effected!\n");
    memcpy(gCopy,g,sizeof(struct gameState));
    bug=0;
   cardEffect(village,c1,c2,c3,gCopy,handPos,bonus);

    for(p=1;p<numPlayer;p++){
    	endTurn(gCopy);
    	if(gCopy->numActions==1 && gCopy->deckCount[p]==5&&gCopy->handCount[p]==5)
    		printf("Player %d Passed!\n",p);
    	else{
    		bug++;
    		printf("Player %d Failed! action =%d,handcount=%d deckcount=%d\n",p,gCopy->numActions,gCopy->handCount[p],gCopy->deckCount[p]);
    	}

    }
    if(my_assert(bug,0))
    	printf("Test 5 Passed!\n");
    else
        printf("Test 5 Failed!\n");




	printf("All tests passed!\n");
	return 0;
}






