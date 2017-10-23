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
int buyersPerSeller; // Buyers per Seller
Buyer ***buyQueues; // array of queues of buyers
char ***seats; // seats for sellers to sell and buyers to purchase
Seller **sellers;


// signals the current thread is done selling in the current minute
void doneSelling() {
   // sleep process to help with timing between thread wake ups
   usleep(100000);

   pthread_mutex_lock(&mutex);

   // decrement the number of sellers making a transaction in the current minute
   selling--;
   if (selling <= 0) {
      // move to a next minute
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

int assignSeat(int sellerIndex) {
   Seller *seller = sellers[sellerIndex];
   int foundSeat = 1;

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
      printf("Seller %s assigned their customer %i to a seat in row %i column %i.\n",
       seller->name, sellers[sellerIndex]->qIndex + 1,
       seller->order[seller->currRowIndex], seller->currCol);

      free(seatCount);
   }
   else {
      printTime();
      printf("Customer %i in seller %s queue is told concert is sold out and turned away.\n",
       sellers[sellerIndex]->qIndex + 1, seller->name);
      foundSeat = 0;
   }

   return foundSeat;
}

void turnAwayBuyers(int sellerIndex) {
   while (sellers[sellerIndex]->qIndex < buyersPerSeller) {
      printTime();
      printf("Customer %i in seller %s queue is told concert sale time has finished and is turned away.\n",
       sellers[sellerIndex]->qIndex + 1, sellers[sellerIndex]->name);
      sellers[sellerIndex]->qIndex++;
   }
}

void checkArrived(int sellerIndex) {
   int index;

   for (index = sellers[sellerIndex]->arrivedIndex; index < buyersPerSeller; index++) {
      if (buyQueues[sellerIndex][index]->arrive <= min) {
         printTime();
         printf("Customer %i in seller %s queue has arrived \n", index + 1, sellers[sellerIndex]->name);
         sellers[sellerIndex]->arrivedIndex++;
      }
   }
}

// seller thread to serve one hour
void * sell(int *sellerIndex) {
   Buyer *currBuyer = buyQueues[*sellerIndex][sellers[*sellerIndex]->qIndex];
   int foundSeat = 1;

   // count the minutes until 1 hour of selling
   while (min < 60) {

      pthread_mutex_lock(&mutex);

      // see if a new customer has arrived in end of seller queue
      checkArrived(*sellerIndex);

      // check for ready buyer
      if (sellers[*sellerIndex]->qIndex < buyersPerSeller && currBuyer->arrive <= min) {
         // wait for other threads to signal to say they are done selling
         pthread_cond_wait(&cond, &mutex);

         // check for new buyer
         if (currBuyer->currSale == 0) {
            // assign a seat for new buyer
            foundSeat = assignSeat(*sellerIndex);
         }

         // increment time of buyer's current sale time
         currBuyer->currSale++;

         // check if buyer is finished with sale
         if (currBuyer->currSale > currBuyer->totSale) {
            if (foundSeat == 1) {
               printTime();
               printf("Customer %i in Seller %s queue finished purchase.\n",
                sellers[*sellerIndex]->qIndex + 1, sellers[*sellerIndex]->name);
            }

            // move to next buyer in queue of this thread
            sellers[*sellerIndex]->qIndex++;
            currBuyer = buyQueues[*sellerIndex][sellers[*sellerIndex]->qIndex];
         }
      }
      pthread_mutex_unlock(&mutex);

      // current seller thread is sone selling in current minute
      doneSelling();
   }

   turnAwayBuyers(*sellerIndex);

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
   buyersPerSeller = strtoul(argv[1], NULL, 0);

   // Create necessary data structures for the simulator.
   seats = createSeats(ROWS, COLS);
   sellers = createSellers(SELLERS);

   // Create buyers list for each seller ticket queue based on the
   // N value within an hour and have them in the sorted seller queue.
   buyQueues = createBuyQueues(SELLERS, buyersPerSeller);
   printBuyQueues(buyQueues, buyersPerSeller);

   // Create 10 threads representing the 10 sellers.
   // Have sellers ready to sell after creating
   for (i = 0; i < SELLERS; i++)
      pthread_create(&tids[i], NULL, (void *)sell, &sellerIndex[i]);

   // wakeup all seller threads to start selling
   wakeup_all_seller_threads();

   // wait for all seller threads to exit
   for (i = 0 ; i < SELLERS ; i++)
      pthread_join(tids[i], NULL);

   //printBuyQueues(buyQueues, buyersPerSeller);

   // Printout simulation results
   // print of sellers of seats
   printSeats(seats, ROWS, COLS);
   countSeats(seats, ROWS, COLS);


   fflush(stdout);

   //free seats and data structures holding them
   freeSeats(seats, ROWS, COLS);

   // free buyers and data structures holding them
   freeBuyQueues(buyQueues, SELLERS, buyersPerSeller);

   // free seller and other allocated variables
   freeSellers(sellers, SELLERS);

   pthread_mutex_destroy(&mutex);
   pthread_cond_destroy(&cond);

   exit(0);
}
