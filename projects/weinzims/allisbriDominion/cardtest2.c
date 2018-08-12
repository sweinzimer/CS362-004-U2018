#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

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

//adventurer card test
int main()
{

    int i, n, r, p, deckCount, discardCount, handCount;
    int currPlayers = 4;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    struct gameState G, testG;

    printf("Testing adventurer.\n");

    r = initializeGame(currPlayers, k, 6, &G);

    printf("initializeGame(4, k, 1, &G) = %d\n", r);
    assert(r == 0);
    //end turn
    testG.hand[0][testG.handCount[0] - 1] = adventurer; //set a card to test card

    memcpy(&testG, &G, sizeof(struct gameState));

    cardEffect(adventurer, 0, 0, 0, &testG, testG.handCount[0] - 1, 0);
    int suc = 0;
    //check 3 treasures drawn
    int initalCount, nowCount;
    for (int i = 0; i < G.handCount[0]; i++)
    {
        int card = G.hand[0][i];
        //  printf("Card%d: %d\n", i, card );
        if (card == copper || card == silver || card == gold)
        {
            initalCount++;
        }
    }

    for (int i = 0; i < testG.handCount[0]; i++)
    {
        int card = testG.hand[0][i];
        //   printf("Card%d: %d\n",i, card );
        if (card == copper || card == silver || card == gold)
        {
            nowCount++;
        }
    }

    int check1 = IsEqual(initalCount + 2, nowCount);
    //  printf("Inital count: %d/ Now Cards: %d\n", initalCount, nowCount);
    if (check1 == 0)
    {
        printf("Failed to draw 2 treasures \n");
        suc = 1;
    }
    int check2 = testG.discardCount[0] > G.discardCount[0];
    //printf("Number discarded %d\n",  testG.discardCount[0]);
    if (check2 == 0)
    {
        printf("Failed to discard\n");
        suc = 1;
    }

    if (suc != 1)
        printf("Adventurer Success\n");
    else
        printf("Adventurer Failed\n");

    assert(suc != 1);

    return 0;
}
