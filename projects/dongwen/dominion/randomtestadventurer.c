/*
 * randomtestcard3.c
 *
 *  Created on: Feb 15, 2018
 *      Author: wenwen
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <math.h>
#include "my_assert.c"


#define NOISY_TEST 1

//global fail counter
int deckCardCountFails=0;
int treasureCountFails=0;
int revealCountFails=0;
int playerEffectedFails=0;

void checkAdventurer(int numPlayer){
	int p,i,j,t=1;
			struct gameState *g = newGame(), *gCopy=newGame();
		    int seed = 1000;
		    
		    int thisPlayer=0;
		    int bug=0;
		    int k[10] = {adventurer, council_room, feast, gardens, mine
		               , remodel, smithy, village, baron, great_hall};

	    //test playAdventurer() function
	    printf("Test against playAdventurer():\n");

	    initializeGame(numPlayer, k, seed, g);

	    printf("\n The deck should be decremented by one. \n");
	    memcpy(gCopy,g,sizeof(struct gameState));
	    for(;t<5;t++){
	    gCopy->deckCount[thisPlayer]=t;
		g->deckCount[thisPlayer] =t;
	    playAdventurer(gCopy);
	    if(gCopy->deckCount[thisPlayer] != g->deckCount[thisPlayer] -1){
	        	printf("Fail! deckCount old = %d new= %d \n",g->deckCount[0],gCopy->deckCount[0]);
	        	bug++;
	    }
	    my_assert(bug,0);
	    if(bug!=0) deckCardCountFails++;}
	#if(NOISY_TEST)
	    printf("Pass: New Deck Count is one cards less now!\n");
	#endif


	    printf("\n The player should have two more treasure cards. \n");
	    memcpy(gCopy,g,sizeof(struct gameState));
	    bug=0;
	    playAdventurer(gCopy);
	    i=gCopy->hand[thisPlayer][gCopy->handCount[thisPlayer]-1];	//top hands card
	    j=gCopy->hand[thisPlayer][gCopy->handCount[thisPlayer]-2];	//second top hands card
	    if(i>=4&&i<=6&&j>=4&&j<=6){
	    	printf("Two treasure cards are %d, %d\n",i, j);
	    }
	    else{
	    	bug++;
	    }
	    my_assert(bug,0);
	    if(bug!=0) treasureCountFails++;
	#if(NOISY_TEST)
	    printf("Pass: Two Treasure Cards in hand!\n");
	#endif

	    printf("\n The revealed card should have a difference of two. \n");
	    memcpy(gCopy,g,sizeof(struct gameState));
	    bug=0;
	    playAdventurer(gCopy);
	    if(gCopy->handCount[thisPlayer]+ gCopy->discardCount[thisPlayer]!= g->handCount[thisPlayer] + g->discardCount[thisPlayer] + 2){
	      		printf("Fail! discard old = %d new= %d ",g->discardCount[0],gCopy->discardCount[0]);
	    		printf("Fail! handCount old = %d new= %d /n",g->handCount[0],gCopy->handCount[0]);
	          	bug++;
	      }
	      my_assert(bug,0);
	      if(bug!=0) revealCountFails++;
	      my_assert(gCopy->handCount[thisPlayer]+ gCopy->discardCount[thisPlayer], g->handCount[thisPlayer] + g->discardCount[thisPlayer] + 2);
	  #if(NOISY_TEST)
	      printf("Pass: Revealed card have a two cards difference!\n");
	  #endif

	      printf("\n Other player should not be effected! \n");
	      memcpy(gCopy,g,sizeof(struct gameState));
	      bug=0;
	      playAdventurer(gCopy);
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
	      if(bug!=0) playerEffectedFails++;
	      #if(NOISY_TEST)
	          printf("Pass: None player is effected!\n\n");
	      #endif
}
int main(){
	srand(time(NULL));
	printf("FILE: randomtestadventurer.c \n");
	int iter = 100,i=0;
	for(;i<iter;i++){
		int player = rand()%(MAX_PLAYERS-1) +2;
		checkAdventurer(player);
	}
	int total=deckCardCountFails+treasureCountFails+revealCountFails+playerEffectedFails;
		
	
	if(total ==0)
		printf("Passing Random Test!\n");
	else {
		printf("Random Test Report:\n");
		printf("Card in Deck Counting Fails: %d times.\n",deckCardCountFails);
		printf("Card in Treasure Counting Fails: %d times.\n",treasureCountFails);
		printf("Card in Revealing Counting Fails: %d times.\n",revealCountFails);
		printf("Other player effected Fails: %d times.\n",playerEffectedFails);
		
	}
	printf("All tests passed!\n");
	return 0;
}

