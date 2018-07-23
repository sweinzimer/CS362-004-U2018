#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

int main()
{

    int i, n, r, p, deckCount, discardCount, handCount;
    int currPlayers = 4;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    struct gameState G;

    printf("Testing isGameOver.\n");

    r = initializeGame(currPlayers, k, 1, &G);

    printf("initializeGame(4, k, 1, &G) = %d\n", r);
    assert(r == 0);
    //check game is not overn
    int go1 = isGameOver(&G);
    assert(go1 != 1);

    G.supplyCount[province] = 0;

    int go2 = isGameOver(&G);
    assert(go2 == 1);

    //re initalize
    r = initializeGame(currPlayers, k, 1, &G);
    for (int j = 0; j < 25; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            if (i + j >= 25)
            {
                G.supplyCount[(i)] = 0;
            }
            else
            {
                G.supplyCount[i + j] = 0;
            }
        }

        int go3 = isGameOver(&G);
        // printf("checking cards %d, %d, %d: %d", j, j+1, j+2, go3);

        assert(go3 == 1);
        r = initializeGame(currPlayers, k, 1, &G);
    }

    printf("isGameOver passed\n");

    return 0;
}
