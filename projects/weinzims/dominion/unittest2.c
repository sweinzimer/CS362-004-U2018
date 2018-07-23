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

  printf("Testing endTurn.\n");

  r = initializeGame(currPlayers, k, 1, &G);

  printf("initializeGame(4, k, 1, &G) = %d\n", r);
  assert(r == 0);
  //end turn
  int p1 = whoseTurn(&G);
  r = endTurn(&G);
  assert(r == 0);
  int p2 = whoseTurn(&G);
  //check player has chnaged
  assert(p1 != p2);
  if (p1 != currPlayers)
    assert(p2 == p1 + 1);
  else
    assert(p2 == 0);
  //check values reinitalized
  assert(G.handCount[p2] == 5);
  assert(G.outpostPlayed == 0);
  assert(G.phase == 0);
  assert(G.numActions == 1);

  assert(G.numBuys == 1);
  assert(G.playedCardCount == 0);

  printf("end turn passed");

  //assert(r == 10);

  return 0;

  return 0;
}
