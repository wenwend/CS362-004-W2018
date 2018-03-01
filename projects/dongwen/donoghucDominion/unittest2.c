/*
 * unittest2.c
 *
 *  Created on: Feb 1, 2018
 *      Author: wenwen
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include<time.h>
#include"my_assert.c"

#define NOISY_TEST 1
#define ZERO 0
int main(){
	srand(time(NULL));
	int i,p=100,q=100,maxTest=20;  // p,q is just some edge number that card enum won't reach
	int count=0;
	
	struct gameState *g = newGame();
	int randomCard;
	
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};


	printf("Test against isGameOver():\n");
	
	for(i=0;i<maxTest;i++){
	
		randomCard = rand()%26;
		if(randomCard == 3){
			g->supplyCount[randomCard] = 0;
#if (NOISY_TEST == 1)
			printf("The supply ends with %d province card!  GAME is over!\n",  ZERO );
#endif
			my_assert(isGameOver(g),1);
			g->supplyCount[randomCard] = 1; //reset so that it can loop again
		}
		else if(p!=randomCard &&q!=randomCard)
		{
			count++;
			g->supplyCount[randomCard] = 0;
			if(count==3){
#if (NOISY_TEST == 1)
			printf("The deck has %d empty supply card!  GAME is over!\n",  3 );
#endif
			my_assert(isGameOver(g),1);
			g->supplyCount[randomCard] = 1; //reset
			}
		}
	}
	printf("All tests passed!\n");
    return 0;
}




