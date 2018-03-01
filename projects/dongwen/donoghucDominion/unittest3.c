/*
 * unittest3.c
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
#include "my_assert.c"

#define NOISY_TEST 1

int main(){
    srand(time(NULL));
    
    int numPlayer = 2;
    int maxBuy = 3;
    int p, r;
    int bonus;
    struct gameState *g=newGame();
    int maxCoin = 100;


    //test buyCard()
    printf("Testing buyCard():\n");
    for(p=0;p<numPlayer;p++){
    	g->whoseTurn=p;
    	g->discardCount[p]=0;
    	g->supplyCount[silver]=0; //set card i as non-existed card
    	g->supplyCount[province]=3;
    	g->numBuys=maxBuy;
    	g->coins=maxCoin;
    	printf("Player %d start with total %d coins for %d buy in total.\n",p,maxCoin,maxBuy);

    	//test some preconditions such as card not available, no buy or no coins.
    	my_assert(buyCard(silver,g) , -1);
#if (NOISY_TEST == 1)
		printf("Pass: the card is not available for now.\n");
#endif
		g->numBuys=0;
		my_assert(buyCard(province,g) ,-1);
		printf("Pass: do not have buy for this player %d.\n",p);
		g->numBuys=maxBuy;

		g->coins=0;
		my_assert(buyCard(province,g), -1);
		printf("Pass: not enough coins for now.\n");
		g->coins=maxCoin;

		for(r=0;r<maxBuy;r++){
		
#if (NOISY_TEST == 1)
		printf("Player %d spend %d for the %d buy. Now he has %d buy left. \n",p,getCost(province),r+1,g->numBuys);
#endif
		my_assert(buyCard(province,g) , 0); //buy province
		my_assert(g->coins,maxCoin-8);//province cost 8
		my_assert(g->numBuys,maxBuy-1);
		my_assert(g->discardCount[p],r+1);
		my_assert(g->discard[p][0],province);
		my_assert(g->supplyCount[province],2-r);
		
		maxCoin=maxCoin-8; 
		maxBuy=maxBuy-1;
		}

    }

    printf("All tests passed!\n");
	return 0;
}


