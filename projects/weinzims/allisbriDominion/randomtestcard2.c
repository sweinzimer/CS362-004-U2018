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
   
    
        int disSize = rand() % MAX_DECK;
        G-> discardCount[i]=disSize;
    
   
        int handSize = rand() % MAX_HAND;
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

    int i, n, r, p, deckCount, discardCount, handCount;
    int currPlayers = 4;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    struct gameState G, testG;
        int failCount=0;
        int succCount = 0;
    printf("Testing sea hag.\n");
    for(int testCount  = 0; testCount < 100; testCount++)
    {

    radomizeState(&G);
   for(int player = 0; player < G.numPlayers; player++)
   {


    //end turn
    testG.hand[player][testG.handCount[player] - 1] = sea_hag; //set a card to test card

    memcpy(&testG, &G, sizeof(struct gameState));

    
    int suc = 0;
    
    
    cardEffect(sea_hag, 0, 0, 0, &testG, testG.handCount[player] - 1, 0);
    
    for (int i = 0; i < testG.numPlayers; i++)
    {
        if(i==player)
            continue;

           // printf("testing for player %d\n", i );
        int origDicard = G.discardCount[i];
        int nowDiscard = testG.discardCount[i];
        int check1 = IsEqual(origDicard + 1, nowDiscard);
        if (check1 == 0)
        {
            printf("Failed to discard 1 card \n");
            suc = 1;
        }
        else
        {
           
            int topcard = G.deck[i][G.deckCount[i]--];
            int discard = testG.discard[i][testG.discardCount[i]--];
            int check2 = IsEqual(topcard, discard);
            if (check2 == 0)
            {
                printf("Failed to discard the top card. car expected is  %d: car found %d \n", topcard, discard);
               // for(int j = 0; j < testG.discardCount[i]; j++)
                //{
                 //    printf("%d:%d\n", j, testG.discard[i][j]);
                //}
                suc = 1;
            }
            int nowTopDeck = testG.deck[i][testG.deckCount[i]--];
            int check3 = IsEqual(nowTopDeck, curse);
            if (check3 == 0)
            {
                   printf("Failed to place curse on top of deck. card found is %d\n", nowTopDeck);
              //     for(int j = 0; j < testG.deckCount[i]; j++)
                //   {
                  //      printf("%d:%d\n", j, testG.deck[i][j]);
                   //}
                  
                suc = 1;
            }
        }
    }

    if (suc == 1)
    {
        printf("sea hag Failed @ Test %d:%d, \n ", testCount, player );
        failCount++;
    }
    else{
        succCount++;
    }
       

       suc=0;

    //assert(suc != 1);
    endTurn(&G);
   // G.whoseTurn = player + 1;
   }
    }
    printf("Adventuere card failed %d and succeded in %d tests", failCount, succCount);
    return 0;
}
