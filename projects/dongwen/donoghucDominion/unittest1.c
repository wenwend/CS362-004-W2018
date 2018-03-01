/*
 * unittest1.c
 *
 *  Created on: Feb 1, 2018
 *      Author: Wenwen DONG
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
	int p,q;
	struct gameState *g = newGame();
    int seed = 1000;
    int numPlayer = 2;
    int maxHandCount =5;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};

    //test numHandCards() function
    printf("Test against numHandCards function():\n");

    initializeGame(numPlayer, k, seed, g); // now each player have 5 hands by hands.
    for(p=0;p<numPlayer;p++){
    	for(q=0;q<maxHandCount;q++){
		drawCard(p,g);  // now let them to draw one more cards.
#if (NOISY_TEST == 1)
     		printf("Test player %d with %d handcard(s).\n", p, numHandCards(g));
#endif
		my_assert(numHandCards(g),6+q); //check if the number of cards are correct.


    	}
    endTurn(g);
    }
	printf("All tests passed!\n");
	return 0;
}
