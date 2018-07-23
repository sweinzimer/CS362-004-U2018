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

  printf("Testing numHandCards.\n");

  r = initializeGame(currPlayers, k, 1, &G);
  drawCard(whoseTurn(&G), &G);
  int c1 = numHandCards(&G);
  drawCard(whoseTurn(&G), &G);
  int c2 = numHandCards(&G);
  assert(c1 != c2);
  assert(c1 + 1 == c2);

  discardCard(0, whoseTurn(&G), &G, 0);
  int c3 = numHandCards(&G);
  assert(c3 != c2);
  assert(c3 == c1);

  printf("numHandCards passed\n");

  return 0;
}
