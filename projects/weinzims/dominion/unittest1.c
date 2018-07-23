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

  int k[10] = {adventurer, council_room, feast, gardens, mine,
               remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf("Testing fullDeckCount.\n");

  r = initializeGame(4, k, 1, &G);

  printf("initializeGame(4, k, 1, &G) = %d\n", r);
  assert(r == 0);

  int barons[MAX_HAND];
  int singlecopper[1] = {copper};
  for (int i = 0; i < MAX_HAND; i++)
  {
    barons[i] = baron;
  }
  for (int j = 0; j < 4; j++)
  {
    G.handCount[j] = MAX_HAND;
    G.discardCount[j] = MAX_HAND;
    G.deckCount[j] = MAX_DECK;
    //check adding cards
    r = fullDeckCount(j, baron, &G);
    //printf("%d\n", r);
    assert(r == 0);
    memcpy(G.hand[j], barons, sizeof(int) * MAX_HAND);
    int r2 = fullDeckCount(j, baron, &G);
    // printf("%d\n", r2);
    assert((r2) == (MAX_HAND + r));
    memcpy(G.discard[j], barons, sizeof(int) * MAX_HAND);
    int r3 = fullDeckCount(j, baron, &G);
    //  printf("%d\n", r3);
    assert((r3) == ((2 * MAX_HAND) + r));

    memcpy(G.deck[j], barons, sizeof(int) * MAX_DECK);
    int r4 = fullDeckCount(j, baron, &G);
    //    printf("%d\n", r4);
    assert((r4) == (((2 * MAX_HAND) + MAX_DECK) + r));
    G.handCount[j] = 0;
    G.discardCount[j] = 0;
    G.deckCount[j] = 0;

    //Check hand count limit
    int r5 = fullDeckCount(j, baron, &G);
    //  printf("%d\n", r5);
    assert((r5) == 0);

    //check cross player effects
    G.handCount[j] = MAX_HAND;
    G.discardCount[j] = MAX_HAND;
    G.deckCount[j] = MAX_DECK;
    memcpy(G.hand[j], singlecopper, sizeof(int) * 1);

    int r6 = fullDeckCount(j, baron, &G);
    //  printf("%d\n", r6);
    assert(r6 != r4);
    for (int i = j + 1; i < 4; i++)
    {

      assert(fullDeckCount(i, baron, &G) == 0);
    }
  }

  printf("fullDeckCount Passed \n");

  //assert(r == 10);

  return 0;

  return 0;
}
