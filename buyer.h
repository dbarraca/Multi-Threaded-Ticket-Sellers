#ifndef BUYER_H
#define BUYER_H

typedef struct Buyer{
   int arrive; //arrival time
   int totSale; // total time for sale to complete
   int currSale; //  time passed for the current sale
} Buyer;

/**
 * Compares the arrival time of the buyers. Helper function for qsort.
 *
 * buyA: pointer to buyer
 * buyB: pointer to another buyer
 *
 * returns: 1 if buyer A's arrival time is greater than buyer B's arrival time,
 * -1 id if buyer A's arrival time is less than buyer B's arrival time, and
 * 0 if buyer A's arrival time the same as buyer B's arrival time.
 */
int compareArrive(const void **buyA, const void **buyB);

/**
 * Creates a single buyer.
 *
 * sellerType: type of buyer to be created.
 *  H for high priced ticket buyers,
 *  M for medium priced ticket buyers, and
 *  L for low priced ticket buyers.
 *
 * returns: pointer to the newly created buyer
 */
Buyer *createBuyer(char sellerType);

/**
 * Creates a single queue of buyers.
 *
 * queueLength: number of buyers in queue
 *
 * sellerType: type of each buyer int queue to be created.
 *  H for high priced ticket buyers,
 *  M for medium priced ticket buyers, and
 *  L for low priced ticket buyers.
 *
 * returns: pointer to the newly created queue of buyers
 */
Buyer **createBuyQueue(int queueLength, char sellerType);

/**
 * Creates |numQueues| queues of |queueLength| buyers.
 *
 * numQueues: number of queues of buyers
 * queueLength: number of buyers in each queue
 *
 * returns: pointer to array of queues of buyers
 */
Buyer ***createBuyQueues(int numQueues, int queueLength);

/**
 * Frees each buyer, each queue holding the buyers and pointer to the queue of buyers
 *
 * buyQueues: pointer to queues of buyers
 * numQueues: number of queues of buyers
 * queueLength: number of buyers in each queue
 */
void freeBuyQueues(Buyer ***buyQueues, int numQueues, int queueLength);

/**
 * Prints each queue of buyers with each buyer's arrival time and total sale time
 * needed to complete ticket purchase.
 *
 * buyQueue: pointer to queue of buyers
 * queueLength: number of buyers in each queue
 */
void printBuyQueue(Buyer **buyQueue, int queueLength)

/**
 * Prints a single queue of buyers with each buyer's arrival time and total sale time
 * needed to complete ticket purchase.
 *
 * buyQueues: pointer to queues of buyers
 * queueLength: number of buyers in each queue
 */
void printBuyQueues(Buyer ***buyQueues, int queueLength);

#endif
