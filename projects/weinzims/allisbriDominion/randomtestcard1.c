#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define DEBUG 0
#define NOISY_TEST 1
#define CARD_COUNT  26

int IsEqual(int a, int b)
{
    if (a == b)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void radomizeState(struct gameState* G)
{
// randomeize initaliztion parameters
//2-4 players
int currPlayers = rand() % 2+2;

int k[10]= {adventurer, council_room, feast, gardens, mine,
    remodel, smithy, village, baron, great_hall};
//int seed = rand() %100;
   int r = initializeGame(currPlayers, k, 10, G);
   
   //for each player randomize hand, discard , and deck states

  
   for(int i = 0; i < currPlayers; i++)
   {
       
        int deckSize = rand() % MAX_DECK;
        if(deckSize==0)
            deckSize++;
        G-> deckCount[i]=deckSize;
   //    printf("Deck size is %d", deckSize);
   
    
        int disSize = rand() % (MAX_DECK - deckSize);
        G-> discardCount[i]=disSize;
    
    int remCards = MAX_HAND - (deckSize + disSize);
    if(remCards < 0)
        remCards = 7;
        int handSize = rand() % remCards;
        if(handSize==0)
            handSize++;
        G-> handCount[i]=handSize - G->deckCount[i] - G->discardCount[i];
    
    for(int j = 0; j < G->deckCount[i]; j++)
    {
        
        G->deck[i][j]= rand() % CARD_COUNT; 
    }
    

    for(int j = 0; j < G->handCount[i]; j++)
    {

        G->hand[i][j]= rand() % CARD_COUNT; 
    }
    for(int j = 0; j < G->discardCount[i]; j++)
    {

        G->discard[i][j]= rand() % CARD_COUNT; 
    }

    

   }

}

//adventurer card test
int main()
{
    srand(time(NULL));
    printf(time(NULL));
    int i, n, r, p, deckCount, discardCount, handCount;
    int currPlayers = 4;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    struct gameState G, testG;
        int failCount=0;
        int succCount = 0;
    printf("Testing village.\n");
    for(int testCount  = 0; testCount < 100; testCount++)
    {

    radomizeState(&G);
   for(int player = 0; player < G.numPlayers; player++)
   {


    //end turn
    testG.hand[player][testG.handCount[player] - 1] = village; //set a card to test card

    memcpy(&testG, &G, sizeof(struct gameState));

    
   
    
    
    cardEffect(village, 0, 0, 0, &testG, testG.handCount[player] - 1, 0);
    int suc = 0;
    int initHand = G.handCount[player];
    int nowHand = testG.handCount[player];

    int check1 = IsEqual(initHand, nowHand);
    if (check1 == 0)
    {
        printf("Failed to draw 1 card \n");
        suc = 1;
    }

    int check2 = IsEqual(G.numActions + 2, testG.numActions);
    if (check2 == 0)
    {
        printf("Failed to add 2 actions \n");
        suc = 1;
    }

    int check4 = IsEqual(G.deckCount[player], testG.deckCount[player] + 1);
    if (check4 == 0)
    {
        printf("Failed to draw 1 card \n");
        suc = 1;
    }
    if (suc == 1)
    {
        printf("village Failed @ Test %d:%d, \n ", testCount, player );
        failCount++;
    }
    else{
        succCount++;
       // printf("village passed @ Test %d:%d, \n ", testCount, player );
    }
       

       suc=0;

    //assert(suc != 1);
    endTurn(&G);
   // G.whoseTurn = player + 1;
   }
    }
    printf("village card failed %d and succeded in %d tests", failCount, succCount);
    return 0;
}
