#include <stdlib.h>
#include <stdio.h>

#include "buyer.h"
#include "seller.h"

#define MIN 60
#define H_MAX 2
#define M_MAX 3
#define L_MAX 4

int compareArrive(const void **buyA, const void **buyB) {
   int ret = 0;

   if (((Buyer *) *buyA)->arrive > ((Buyer *) *buyB)->arrive) {
      ret = 1;
   }
   else if (((Buyer *) *buyA)->arrive < ((Buyer *) *buyB)->arrive) {
      ret = -1;
   }

    return ret;
}

Buyer *createBuyer(char sellerType) {
   Buyer *buyer = malloc(sizeof(Buyer));

   buyer->arrive = rand() % MIN; // set arrival time

   if (sellerType == 'H')
      buyer->sale = (rand() % H_MAX) + 1;
   else if (sellerType == 'M')
      buyer->sale = (rand() % M_MAX) + 2;
   else if (sellerType == 'L')
      buyer->sale = (rand() % L_MAX) + 4;

   buyer->passed = 0; // set arrival time

   return buyer;
}

Buyer **createBuyQueue(int queueLength, char sellerType) {
   int buyIndex;
   Buyer **buyQueue = malloc(sizeof(Buyer *) * queueLength);

   for (buyIndex = 0; buyIndex < queueLength; buyIndex++)
      buyQueue[buyIndex] = createBuyer(sellerType);

   return buyQueue;
}

Buyer ***createBuyQueues(int numQueues, int queueLength) {
   int qIndex;
   Buyer ***buyQueues = malloc(sizeof(Buyer **) * numQueues);
   printf("numQueues %i, queueLength %i\n", numQueues, queueLength);

   srand(0);

   for (qIndex = 0; qIndex < 1; qIndex++)
      buyQueues[qIndex] = createBuyQueue(queueLength, 'H');

   for (qIndex = 1; qIndex < 4; qIndex++)
      buyQueues[qIndex] = createBuyQueue(queueLength, 'M');

   for (qIndex = 4; qIndex < 10; qIndex++)
      buyQueues[qIndex] = createBuyQueue(queueLength, 'L');

   for (qIndex = 0; qIndex < numQueues; qIndex++)
      qsort(buyQueues[qIndex], queueLength, sizeof(Buyer *), compareArrive);

   return buyQueues;
}

void freeBuyQueues(Buyer ***buyQueues, int numQueues, int queueLength) {
   int qIndex, buyIndex;

   for (qIndex = 0; qIndex < numQueues; qIndex++) {
      for(buyIndex = 0; buyIndex < queueLength; buyIndex++)
         free(buyQueues[qIndex][buyIndex]);
      free(buyQueues[qIndex]);
   }

   free(buyQueues);
}

void printBuyQueue(Buyer **buyQueue, int queueLength) {
   int buyIndex;
   Buyer *currBuy;

   for (buyIndex = 0; buyIndex < queueLength; buyIndex++) {
      currBuy = buyQueue[buyIndex];
      printf("arrive: %i sale: %i\n", currBuy->arrive, currBuy->sale);
   }
}

void printBuyQueues(Buyer ***buyQueues, int queueLength) {
   int qIndex;

   for (qIndex = 0; qIndex < 1; qIndex++) {
      printf("\nH Seller Queue\n");
      printBuyQueue(buyQueues[qIndex], queueLength);
   }

   for (qIndex = 1; qIndex < 4; qIndex++) {
      printf("\nM Seller Queue\n");
      printBuyQueue(buyQueues[qIndex], queueLength);
   }

   for (qIndex = 4; qIndex < 10; qIndex++) {
      printf("\nL Seller Queue\n");
      printBuyQueue(buyQueues[qIndex], queueLength);
   }
   printf("\n");
 }
