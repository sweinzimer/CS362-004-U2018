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

//sea hag card test
int main()
{

    int i, n, r, p, deckCount, discardCount, handCount;
    int currPlayers = 4;
    int k[11] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall, sea_hag};

    struct gameState G, testG;

    printf("Testing adventurer.\n");

    r = initializeGame(currPlayers, k, 6, &G);

    printf("initializeGame(4, k, 1, &G) = %d\n", r);
    assert(r == 0);
    //end turn
    testG.hand[0][testG.handCount[0] - 1] = sea_hag; //set a card to test card

    memcpy(&testG, &G, sizeof(struct gameState));

    cardEffect(sea_hag, 0, 0, 0, &testG, testG.handCount[0] - 1, 0);
    int suc = 0;
    for (int i = 1; i < currPlayers; i++)
    {
        int origDicard = G.discardCount[i];
        int nowDiscard = testG.discardCount[i];
        int check1 = IsEqual(origDicard + 1, nowDiscard);
        if (check1 == 0)
        {
            printf("Failed to dicard 1 card \n");
            suc = 1;
        }
        else
        {
           
            int topcard = G.deck[i][G.deckCount[i]--];
            int discard = testG.discard[i][testG.discardCount[i]--];
            int check2 = IsEqual(topcard, discard);
            if (check2 == 0)
            {
                printf("Failed to dicard the top card \n");
                suc = 1;
            }
            int nowTopDeck = testG.deck[i][testG.deckCount[i]--];
            int check3 = IsEqual(nowTopDeck, curse);
            if (check3 == 0)
            {
                   printf("Failed to place curse on top of deck \n");
                suc = 1;
            }
        }
    }
    if (suc != 1)
        printf("Sea Hag Succes\n");
    else
        printf("Sea Hag Failed\n");

    assert(suc != 1);

    return 0;
}
