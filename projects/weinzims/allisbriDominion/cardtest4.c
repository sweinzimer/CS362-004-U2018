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

//village card test
int main()
{

    int i, n, r, p, deckCount, discardCount, handCount;
    int currPlayers = 4;
    int k[11] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall, sea_hag};

    struct gameState G, testG;

    printf("Testing village.\n");

    r = initializeGame(currPlayers, k, 6, &G);

    printf("initializeGame(4, k, 1, &G) = %d\n", r);
    assert(r == 0);
    //end turn
    testG.hand[0][testG.handCount[0] - 1] = village; //set a card to test card

    memcpy(&testG, &G, sizeof(struct gameState));

    cardEffect(village, 0, 0, 0, &testG, testG.handCount[0] - 1, 0);
    int suc = 0;
    int initHand = G.handCount[0];
    int nowHand = testG.handCount[0];

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

    int check4 = IsEqual(G.deckCount[0], testG.deckCount[0] + 1);
    if (check4 == 0)
    {
        printf("Failed to draw 1 card \n");
        suc = 1;
    }

    if (suc != 1)
        printf("Village Success\n");
    else
        printf("Village Failed\n");

    assert(suc != 1);

    return 0;
}
