#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "buyer.h"
#include "seller.h"
#include "seat.h"

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int min; // current time in minutes
int selling; // number of sellers making a transaction in the current minute
int buyPerSeller; // Buyers per Seller
Buyer ***buyQueues; // array of queues of buyers
char *seats[ROWS][COLS]; // seats for sellers to sell and buyers to purchase

// array holding places of each seller in their respective queues
int qIndex[SELLERS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void mutexWait() {
   pthread_mutex_lock(&mutex);
   // atomically release mutex and wait on cond until somebody does signal or broadcast.
   // when you are awaken as a result of signal or broadcast, you acquire the mutex again.
   pthread_cond_wait(&cond, &mutex);
   pthread_mutex_unlock(&mutex);
}

// signals the current thread is done selling in the current minute
void doneSelling() {
   // sleep process to help with timing between thread wake ups
   sleep(1);
//   usleep(1000000);

   pthread_mutex_lock(&mutex);

   // decrement the number of sellers making a transaction in the current minute
   selling--;

   //signal another thread to sell
   pthread_cond_signal(&cond);
   pthread_mutex_unlock(&mutex);
}

// reset the number of sellers making a transaction in the current minute
// to number of total sellers at start on new minute
void resetSelling() {
   pthread_mutex_lock(&mutex);

   // the number of current sellers
   if (selling <= 0) {
      // move to a next minute
      min++;
      // set number of current sellers to default value
      selling = SELLERS;
   }
   pthread_mutex_unlock(&mutex);
}

// seller thread to serve one time slice (1 minute)
void * sell(int *sellerIndex) {
//   int qIndex[SELLERS] = {};

   // count the minutes until 1 hour of selling
   while (min < 60) {

      pthread_mutex_lock(&mutex);
      while (qIndex[*sellerIndex] < buyPerSeller &&
       buyQueues[*sellerIndex][qIndex[*sellerIndex]]->arrive == min) {

         printf("arrived %i min %i seller  %i\n",
          buyQueues[*sellerIndex][qIndex[*sellerIndex]]->arrive, min, *sellerIndex);

         pthread_cond_wait(&cond, &mutex);

         // move to next buyer in queue of this thread
         qIndex[*sellerIndex]++;
      }
      pthread_mutex_unlock(&mutex);

      doneSelling();

      resetSelling();
   }

   pthread_exit(0);
//   return NULL; // thread exits
}

void wakeup_all_seller_threads() {
   // get the lock to have predictable scheduling
   pthread_mutex_lock(&mutex);

   // wakeup all threads waiting on the cond variable
   pthread_cond_broadcast(&cond);

   pthread_mutex_unlock(&mutex);
}

int main(int argc, char *argv[]) {
   int i; // generic index for sellers
   pthread_t tids[SELLERS]; // Thread Ids
   int sellerIndex[SELLERS] = {0,1,2,3,4,5,6,7,8,9}; // Seller Indices

   // Set data shared on threads to default values
   min = 0;
   selling = SELLERS;
   buyPerSeller = strtoul(argv[1], NULL, 0);

   // Create necessary data structures for the simulator.
  // seats = createSeats(ROWS, COLS);

   // Create buyers list for each seller ticket queue based on the
   // N value within an hour and have them in the sorted seller queue.
   buyQueues = createBuyQueues(SELLERS, buyPerSeller);
   printBuyQueues(buyQueues, buyPerSeller);

   // Create 10 threads representing the 10 sellers.
   // Have sellers ready to sell after creating
   for (i = 0; i < SELLERS; i++)
      pthread_create(&tids[i], NULL, (void *)sell, &sellerIndex[i]);

   // wakeup all seller threads to start selling
   wakeup_all_seller_threads();

   // wait for all seller threads to exit
   for (i = 0 ; i < SELLERS ; i++)
      pthread_join(tids[i], NULL);

   // Printout simulation results
   //printBuyQueues(buyQueues, buyPerSeller);
   fflush(stdout);

   //free buyers and data structures holding them
   freeBuyQueues(buyQueues, SELLERS, buyPerSeller);

   pthread_mutex_destroy(&mutex);
   pthread_cond_destroy(&cond);

   exit(0);
}
