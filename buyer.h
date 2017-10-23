#ifndef BUYER_H
#define BUYER_H

typedef struct Buyer{
   int arrive; //arrival time
   int totSale; // sale time
   int currSale; // sale time that has passed
} Buyer;


/**
 * Creates a queue of |queueLength| buyer for |numQueues| sellers.
 */
Buyer ***createBuyQueues(int numQueues, int queueLength);

void freeBuyQueues(Buyer ***buyQueues, int numQueues, int queueLength);

void printBuyQueue(Buyer **buyQueue, int queueLength);
void printBuyQueues(Buyer ***buyQueues, int queueLength);

#endif
