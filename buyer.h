#ifndef BUYER_H
#define BUYER_H

typedef struct Buyer{
   int arrive; //arrival time
   int totSale; // total time for sale to complete
   int currSale; //  time passed for the current sale
} Buyer;


/**
 * Creates a queue of |queueLength| buyer for |numQueues| sellers.
 */
Buyer ***createBuyQueues(int numQueues, int queueLength);

void freeBuyQueues(Buyer ***buyQueues, int numQueues, int queueLength);

void printBuyQueues(Buyer ***buyQueues, int queueLength);

#endif
