typedef struct Customer{
   int arrive; //arrival time
   int sale; // sale time
} Customer;


/**
 * Creates a queue of |queueLength| customer for |numQueues| sellers.
 */
Customer **createCustQueues(int numQueues, int queueLength);

void freeCustQueues(Customer **custQueues, int numQueues, int queueLength);
