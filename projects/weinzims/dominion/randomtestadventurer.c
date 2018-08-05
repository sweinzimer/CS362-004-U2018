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
#define CARD_COUNT 26

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
void radomizeState(struct gameState *G)
{
    // randomeize initaliztion parameters
    //2-4 players
    int currPlayers = rand() % 2 + 2;

    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    //int seed = rand() %100;
    int r = initializeGame(currPlayers, k, 10, G);

    //for each player randomize hand, discard , and deck states

    for (int i = 0; i < currPlayers; i++)
    {

        for (int i = 0; i < currPlayers; i++)
        {

            int deckSize = rand() % MAX_DECK;
            if (deckSize == 0)
                deckSize++;
            G->deckCount[i] = deckSize;
            //    printf("Deck size is %d", deckSize);

            int disSize = rand() % (MAX_DECK - deckSize);
            G->discardCount[i] = disSize;

            int remCards = MAX_HAND - (deckSize + disSize);
            if (remCards < 0)
                remCards = 7;
            int handSize = rand() % remCards;
            if (handSize == 0)
                handSize++;
            G->handCount[i] = handSize - G->deckCount[i] - G->discardCount[i];

            for (int j = 0; j < G->deckCount[i] - 3; j++)
            {

                G->deck[i][j] = rand() % CARD_COUNT;
            }
            for (int j = G->deckCount[i] - 3; j < G->deckCount[i]; j++)
            {
                int roll = rand() % 3;
                if (roll == 0)
                    G->deck[i][j] = copper;
                if (roll == 1)
                    G->deck[i][j] = silver;
                if (roll == 2)
                    G->deck[i][j] = gold;
            }

            for (int j = 0; j < G->handCount[i]; j++)
            {

                G->hand[i][j] = rand() % CARD_COUNT;
            }
            for (int j = 0; j < G->discardCount[i]; j++)
            {

                G->discard[i][j] = rand() % CARD_COUNT;
            }
        }
    }
}
    //adventurer card test
    int main()
    {
        srand(time(NULL));
        clock_t start  = clock();
        int i, n, r, p, deckCount, discardCount, handCount;
        int currPlayers = 4;
        int k[10] = {adventurer, council_room, feast, gardens, mine,
                     remodel, smithy, village, baron, great_hall};

        struct gameState G, testG;
        int failCount = 0;
        int succCount = 0;
        printf("Testing adventurer.\n");
       
        for (int testCount = 0; testCount < 100; testCount++)
        {

            radomizeState(&G);
            for (int player = 0; player < G.numPlayers; player++)
            {

                //end turn
                testG.hand[player][testG.handCount[player] - 1] = adventurer; //set a card to test card

                memcpy(&testG, &G, sizeof(struct gameState));

                // int suc = 0;
                // //check 3 treasures drawn
                // int initalCount = 0;
                // int intalTotalTreasurers = 0;
                // int nowCount = 0;
                // for (int i = 0; i < G.handCount[player]; i++)
                // {
                //     int card = G.hand[player][i];
                //     //  printf("Card%d: %d\n", i, card );
                //     if (card == copper || card == silver || card == gold)
                //     {
                //         initalCount++;
                //     }
                // }
                // for (int i = 0; i < G.deckCount[player]; i++)
                // {
                //     int card = G.deck[player][i];
                //     // printf("Card%d: %d\n", i, card );
                //     if (card == copper || card == silver || card == gold)
                //     {
                //         intalTotalTreasurers++;
                //     }
                // }
                // for (int i = 0; i < G.discardCount[player]; i++)
                // {
                //     int card = G.discard[player][i];
                //     //  printf("Card%d: %d\n", i, card );
                //     if (card == copper || card == silver || card == gold)
                //     {
                //         intalTotalTreasurers++;
                //     }
                // }
                // if (intalTotalTreasurers < 3)
                // {
                //     printf("There are only %d treas to draw skipping test %d:%d\n", intalTotalTreasurers, testCount, player);
                //     continue;
                // }
                cardEffect(adventurer, 0, 0, 0, &testG, testG.handCount[player] - 1, 0);
                // for (int i = 0; i < testG.handCount[player]; i++)
                // {
                //     int card = testG.hand[player][i];
                //     //printf("Card%d: %d\n",i, card );
                //     if (card == copper || card == silver || card == gold)
                //     {
                //         nowCount++;
                //     }
                // }

                // int check1 = IsEqual(initalCount + 2, nowCount);
                // //  printf("Inital count: %d/ Now Cards: %d\n", initalCount, nowCount);
                // if (check1 == 0)
                // {
                //     printf("Failed to draw 2 treasures %d:%d \n", initalCount, nowCount);

                //     suc = 1;
                // }
                // int check2 = testG.discardCount[player] > G.discardCount[player];
                // // printf("Number discarded %d\n",  testG.discardCount[player]);
                // //printf("Number discarded %d\n",  G.discardCount[player]);

                // if (check2 == 0)
                // {
                //     printf("Failed to discard\n");
                //     suc = 1;
                // }

                // if (suc == 1)
                // {
                //     printf("Adventurer Failed @ Test %d:%d, \n ", testCount, player);
                //     failCount++;
                // }
                // else
                // {
                //     succCount++;
                // }

                // suc = 0;

                //assert(suc != 1);
                endTurn(&G);
                // G.whoseTurn = player + 1;
            }
        }
        printf("Completed in %d", ((clock()-start)/(double)CLOCKS_PER_SEC));
        printf("Adventuere card failed %d and succeded in %d tests", failCount, succCount);
        return 0;
    }
