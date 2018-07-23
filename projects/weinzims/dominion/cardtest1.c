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

//smithy card test
int main()
{

    int i, n, r, p, deckCount, discardCount, handCount;
    int currPlayers = 4;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    struct gameState G, testG;

    printf("Testing smithy.\n");

    r = initializeGame(currPlayers, k, 6, &G);

    printf("initializeGame(4, k, 1, &G) = %d\n", r);
    assert(r == 0);
    //end turn

    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(smithy, 0, 0, 0, &testG, testG.handCount[0], 0);
    int suc = 0;
    //check 3 cards drawn and 1 discarded

    int check1 = IsEqual(G.handCount[0] + 2, testG.handCount[0]);
    //  printf("Inital Cards: %d/ Now Cards: %d\n", G.handCount[0], testG.handCount[0]);
    if (check1 == 0)
    {
        printf("Failed to draw\n");
        suc = 1;
    }
    int check2 = testG.discardCount[0] > G.discardCount[0];
    printf("Number discarded %d\n", testG.discardCount[0]);
    if (check2 == 0)
    {
        printf("Failed to discard\n");
        suc = 1;
    }
    if (suc != 1)
        printf("Smithy Success\n");
    else
        printf("Smithy Failed\n");
    assert(suc != 1);

    return 0;
}
