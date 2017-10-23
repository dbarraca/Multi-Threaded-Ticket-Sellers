#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
char ***seats; // seats for sellers to sell and buyers to purchase
Seller **sellers;

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
   //sleep(1);
   usleep(100000);

   pthread_mutex_lock(&mutex);

   // decrement the number of sellers making a transaction in the current minute
   selling--;
   if (selling <= 0) {
      // move to a next minute
     // printf("min %i\n", min);
      min++;
      // set number of current sellers to default value
      selling = SELLERS;
   }
   //signal another thread to sell
   pthread_cond_signal(&cond);
   pthread_mutex_unlock(&mutex);
}

void printTime() {
   if (min < 10)
      printf("0:0%i ", min);
   else
      printf("0:%i ", min);
}

char * intToStr(int toConvert) {
   char *retStr = malloc(sizeof(char) * 3);

   retStr[0] = '0' + toConvert / 10;
   retStr [1] = '0' + toConvert % 10;
   retStr [2] = '\0';

   return retStr;
}

void assignSeat(int sellerIndex) {
   Seller *seller = sellers[sellerIndex];

   while (seller->currRowIndex < ROWS &&
    seats[seller->order[seller->currRowIndex]][seller->currCol] != NULL) {
      seller->currCol++;

      if (seller->currCol >= COLS) {
         seller->currCol = 0;
         seller->currRowIndex++;
      }
   }

   if (seller->currRowIndex < ROWS &&
    seats[seller->order[seller->currRowIndex]][seller->currCol] == NULL) {
      seller->seatCount++;

      seats[seller->order[seller->currRowIndex]][seller->currCol] = malloc(sizeof(char *));
      strcpy(seats[seller->order[seller->currRowIndex]][seller->currCol], seller->name);

      char *seatCount = intToStr(seller->seatCount);

      strcat(seats[seller->order[seller->currRowIndex]][seller->currCol],
       seatCount);

      printTime();
      printf("Seller %s assigned their customer %i to a seat in row %i column %i\n",
       seller->name, qIndex[sellerIndex] + 1, seller->order[seller->currRowIndex], seller->currCol);

      free(seatCount);
   }
}

// seller thread to serve one hour
void * sell(int *sellerIndex) {
   Buyer *currBuyer = buyQueues[*sellerIndex][qIndex[*sellerIndex]];

   // count the minutes until 1 hour of selling
   while (min < 60) {

      pthread_mutex_lock(&mutex);
      if (qIndex[*sellerIndex] < buyPerSeller &&
       currBuyer->arrive <= min) {
         if (currBuyer->currSale == 0) {
            // assign a seat for new buyer
            assignSeat(*sellerIndex);
         }

         pthread_cond_wait(&cond, &mutex);

         currBuyer->currSale++;

         if (currBuyer->currSale >= currBuyer->totSale) {
            // move to next buyer in queue of this thread
            qIndex[*sellerIndex]++;
            currBuyer = buyQueues[*sellerIndex][qIndex[*sellerIndex]];
         }
      }
      pthread_mutex_unlock(&mutex);

      doneSelling();
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
   seats = createSeats(ROWS, COLS);
   sellers = createSellers(SELLERS);

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

   //printBuyQueues(buyQueues, buyPerSeller);

   // Printout simulation results
   // print of sellers of seats
   printSeats(seats, ROWS, COLS);
   //free seats and data structures holding them
   fflush(stdout);
   freeSeats(seats, ROWS, COLS);

   // free buyers and data structures holding them
   freeBuyQueues(buyQueues, SELLERS, buyPerSeller);

   // free seller and other allocated variables
   freeSellers(sellers, SELLERS);

   pthread_mutex_destroy(&mutex);
   pthread_cond_destroy(&cond);

   exit(0);
}
