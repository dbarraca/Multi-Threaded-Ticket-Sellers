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

   // set buyer's random arrival time in hour
   buyer->arrive = rand() % MIN;

   // set buyer's random total time for a sale
   if (sellerType == 'H')
      buyer->totSale = (rand() % H_MAX) + 1;
   else if (sellerType == 'M')
      buyer->totSale = (rand() % M_MAX) + 2;
   else if (sellerType == 'L')
      buyer->totSale = (rand() % L_MAX) + 4;

   // set time passed for the sale to zero
   buyer->currSale = 0;

   return buyer;
}

Buyer **createBuyQueue(int queueLength, char sellerType) {
   int buyIndex;
   Buyer **buyQueue = malloc(sizeof(Buyer *) * queueLength);

   // Fill queue with newly created buyers
   for (buyIndex = 0; buyIndex < queueLength; buyIndex++)
      buyQueue[buyIndex] = createBuyer(sellerType);

   return buyQueue;
}

Buyer ***createBuyQueues(int numQueues, int queueLength) {
   int qIndex;
   Buyer ***buyQueues = malloc(sizeof(Buyer **) * numQueues);

   // initialize random number generateor
   srand(0);


   // create queues of buyers with different seller types
   for (qIndex = 0; qIndex < 1; qIndex++)
      buyQueues[qIndex] = createBuyQueue(queueLength, 'H');

   for (qIndex = 1; qIndex < 4; qIndex++)
      buyQueues[qIndex] = createBuyQueue(queueLength, 'M');

   for (qIndex = 4; qIndex < 10; qIndex++)
      buyQueues[qIndex] = createBuyQueue(queueLength, 'L');

   // sort queues by buyer's arrival time
   for (qIndex = 0; qIndex < numQueues; qIndex++)
      qsort(buyQueues[qIndex], queueLength, sizeof(Buyer *), compareArrive);

   return buyQueues;
}

void freeBuyQueues(Buyer ***buyQueues, int numQueues, int queueLength) {
   int qIndex, buyIndex;

   // iterate through queus
   for (qIndex = 0; qIndex < numQueues; qIndex++) {
      //iterate through buyers in queues
      for(buyIndex = 0; buyIndex < queueLength; buyIndex++)
         // free the current buyer
         free(buyQueues[qIndex][buyIndex]);
      // free the current queue of buyers
      free(buyQueues[qIndex]);
   }

   free(buyQueues);
}

void printBuyQueue(Buyer **buyQueue, int queueLength) {
   int buyIndex;
   Buyer *currBuy;

   // iterate through buyers in queue
   for (buyIndex = 0; buyIndex < queueLength; buyIndex++) {
      currBuy = buyQueue[buyIndex];
      // print current buyer's arrival time and needed time for a purchase
      printf("arrive: %i sale: %i\n", currBuy->arrive, currBuy->totSale);
   }
}

void printBuyQueues(Buyer ***buyQueues, int queueLength) {
   int qIndex;

   // print high price buyer queue
   for (qIndex = 0; qIndex < 1; qIndex++) {
      printf("\nH Seller Queue\n");
      printBuyQueue(buyQueues[qIndex], queueLength);
   }

   // print each medium price buyer queue
   for (qIndex = 1; qIndex < 4; qIndex++) {
      printf("\nM Seller Queue\n");
      printBuyQueue(buyQueues[qIndex], queueLength);
   }

   // print each low price buyer queue
   for (qIndex = 4; qIndex < 10; qIndex++) {
      printf("\nL Seller Queue\n");
      printBuyQueue(buyQueues[qIndex], queueLength);
   }
   printf("\n");
 }
