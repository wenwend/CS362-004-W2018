/*
 * unittest4.c
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
#include "my_assert.c"

#define NOISY_TEST 1

int main(){
	srand(time(NULL));
    int i,p,r;
    int randomCard;
    int numPlayer = 2;
    int randomBonus;
    int randomHandCount;

    struct gameState *g= newGame();

    //test updateCoins()
    printf("Test against function updateCoins(): \n");

    for(i=0;i<numPlayer;i++){
    	randomBonus = rand()%10+1;//bonus can be up to 10
    	randomHandCount=rand()%5+1; //set up handCount
    	g->handCount[i]=randomHandCount;
    	r=randomBonus;
    	for(p=0;p<randomHandCount;p++){
    		randomCard=rand()%3+4; //can either be cooper silver or gold
    		g->hand[i][p]=randomCard;
    		r+=randomCard-3;
#if (NOISY_TEST == 1)
		printf("Player %d has %d new cards in hand, worthy %d coins. \n",i,p+1,randomCard-3);
#endif
    	}
	printf("Player %d has %d bonus besides the card(s). \n",i,randomBonus);
#if (NOISY_TEST == 1)
		printf("Player %d has %d cards worthy %d in hand \n",i,g->handCount[i],r);
#endif
		my_assert(updateCoins(i,g,randomBonus),0);
		my_assert(g->coins,r);
    	}
    printf("All tests passed!\n");
    return 0;
}





