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
		int p,i,j;
		struct gameState *g = newGame(), *gCopy=newGame();
	    int seed = 1000;
	    int numPlayer = MAX_PLAYERS;
	    int temphand[MAX_HAND];// moved above the if statement
	    int thisPlayer=0;
	    int bug=0;
	    int k[10] = {adventurer, council_room, feast, gardens, mine
	               , remodel, smithy, village, baron, great_hall};

    //test playAdventurer() function
    printf("Test against playAdventurer():\n");

    initializeGame(numPlayer, k, seed, g);

    printf("\n The deck should be decremented by one. \n");
    memcpy(gCopy,g,sizeof(struct gameState));
    adventurer_function(0,gCopy,thisPlayer,temphand);
    if(gCopy->deckCount[thisPlayer] != g->deckCount[thisPlayer] -1){
        	printf("Fail! deckCount old = %d new= %d /n",g->deckCount[0],gCopy->deckCount[0]);
        	bug++;
    }
    my_assert(bug,0);
#if(NOISY_TEST)
    printf("Pass: New Deck Count is one cards less now!\n");
#endif


    printf("\n The player should have two more treasure cards. \n");
    memcpy(gCopy,g,sizeof(struct gameState));
    bug=0;
    adventurer_function(0,gCopy,thisPlayer,temphand);
    i=gCopy->hand[thisPlayer][gCopy->handCount[thisPlayer]-1];	//top hands card
    j=gCopy->hand[thisPlayer][gCopy->handCount[thisPlayer]-2];	//second top hands card
    if(i>=4&&i<=6&&j>=4&&j<=6){
    	printf("Two treasure cards are %d, %d\n",i, j);
    }
    else{
    	bug++;
    }
    my_assert(bug,0);
#if(NOISY_TEST)
    printf("Pass: Two Treasure Cards in hand!\n");
#endif

    printf("\n The revealed card should have a difference of two. \n");
    memcpy(gCopy,g,sizeof(struct gameState));
    bug=0;
    adventurer_function(0,gCopy,thisPlayer,temphand);
    if(gCopy->handCount[thisPlayer]+ gCopy->discardCount[thisPlayer]!= g->handCount[thisPlayer] + g->discardCount[thisPlayer] + 2){
      		printf("Fail! discard old = %d new= %d ",g->discardCount[0],gCopy->discardCount[0]);
    		printf("Fail! handCount old = %d new= %d /n",g->handCount[0],gCopy->handCount[0]);
          	bug++;
      }
      my_assert(bug,0);
      my_assert(gCopy->handCount[thisPlayer]+ gCopy->discardCount[thisPlayer], g->handCount[thisPlayer] + g->discardCount[thisPlayer] + 2);
  #if(NOISY_TEST)
      printf("Pass: Revealed card have a two cards difference!\n");
  #endif

      printf("\n Other player should not be effected! \n");
      memcpy(gCopy,g,sizeof(struct gameState));
      bug=0;
      adventurer_function(0,gCopy,thisPlayer,temphand);
      for(p=1;p<numPlayer;p++){
    	  printf("Player %d HandCount =%d, DeckCount =%d, DiscardCount =%d\n",p,gCopy->handCount[p],gCopy->deckCount[p],gCopy->discardCount[p]);
    	  if(gCopy->handCount[p]==g->handCount[p] && gCopy->deckCount[p]==g->deckCount[p] && gCopy->discardCount[p]==g->discardCount[p])
    	  {
    		  printf("Pass: player %d is not effected!\n",p);
    	  }
    	  else{
    		  bug++;
    		  printf("Fail! Player%d is effected!\n");
    	  }
      }
      my_assert(bug,0);
      #if(NOISY_TEST)
          printf("Pass: None player is effected!\n\n");
      #endif

	printf("All tests passed!\n");
	return 0;
}




