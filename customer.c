#include <stdlib.h>
#include <stdio.h>

#include "customer.h"

#define ARV_MAX 60
#define H_MAX 2
#define M_MAX 3
#define L_MAX 4

Customer createCustomer(char sellerType) {
   Customer customer;

   customer.arrive = rand() % ARV_MAX; // set arrival time

   if (sellerType == 'H')
      customer.sale = (rand() % H_MAX) + 1;
   else if (sellerType == 'M')
      customer.sale = (rand() % M_MAX) + 2;
   else if (sellerType == 'L')
      customer.sale = (rand() % L_MAX) + 4;

   printf("%c arrive: %i sale: %i\n", sellerType, customer.arrive,
    customer.sale);

   return customer;
}

Customer *createCustQueue(int queueLength, char sellerType) {
   int custIndex;
   Customer *custQueue = malloc(sizeof(Customer) * queueLength);

   for (custIndex = 0; custIndex < queueLength; custIndex++)
      custQueue[custIndex] = createCustomer(sellerType);

   return custQueue;
}

Customer **createCustQueues(int numQueues, int queueLength) {
   int qIndex;
   Customer **custQueues = malloc(sizeof(Customer *) * numQueues);
   printf("numQueues %i, queueLength %i\n", numQueues, queueLength);

   srand(0);

   for (qIndex = 0; qIndex < 1; qIndex++)
      custQueues[qIndex] = createCustQueue(queueLength, 'H');

   for (qIndex = 1; qIndex < 4; qIndex++)
      custQueues[qIndex] = createCustQueue(queueLength, 'M');

   for (qIndex = 4; qIndex < 10; qIndex++)
      custQueues[qIndex] = createCustQueue(queueLength, 'L');

   return custQueues;
}

void freeCustQueues(Customer **custQueues, int numQueues, int queueLength) {
   int qIndex, custIndex;

   for (qIndex = 0; qIndex < numQueues; qIndex++) {

      free(custQueues[qIndex]);
   }
   free(custQueues);
}
