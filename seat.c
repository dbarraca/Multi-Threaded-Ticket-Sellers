#include <stdlib.h>
#include <stdio.h>

#include "seat.h"


char ***createSeats(int rows, int cols) {
   int currRow, currCol;
   char ***seats = malloc(sizeof(char **) * rows);

   // iterate through rows of seats
   for (currRow = 0; currRow < rows; currRow++) {
      // allocate space for seats
      seats[currRow] = malloc(sizeof(char *) * cols);

      // set each seat to null for start of selling period
      for (currCol = 0; currCol < cols; currCol++)
         seats[currRow][currCol] = NULL;
   }

   return seats;
}

void printSeats(char ***seats, int rows, int cols) {
   int currRow, currCol;

   printf("\n");

   // iterate through each row of seats
   for (currRow = 0; currRow < rows; currRow++) {
      // iterate through each column of seats
      for (currCol = 0; currCol < cols; currCol++) {

         // check if seat was ever assigned
         if (seats[currRow][currCol] == NULL)
            // print place holder if seat was never assigned
            printf("---- ");
         else
            // print buyer identify, the seller and number of tickets sold at
            // time of seat assignment
            printf("%s ", seats[currRow][currCol]);
      }
      printf("\n");
   }
}

void countSeats(char ***seats, int rows, int cols) {
   int currRow, currCol, HCount = 0, MCount = 0, LCount = 0;

   printf("\n");

   // iterate through each rows of seats
   for (currRow = 0; currRow < rows; currRow++) {
      // iterate through each column of seats
      for (currCol = 0; currCol < cols; currCol++) {

         // check if seat was ever assigned
         if (seats[currRow][currCol] != NULL){

            // increment count of sold tickets for each ticket price level
            if (*seats[currRow][currCol] == 'H') {
               HCount++;
            }
            else if (*seats[currRow][currCol] == 'M') {
               MCount++;
            }
            else if (*seats[currRow][currCol] == 'L') {
               LCount++;
            }
         }
      }
   }

   // print count of sold tickets for each price levels
   printf("%i H customers served.\n", HCount);
   printf("%i M customers served.\n", MCount);
   printf("%i L customers served.\n", LCount);
}

void freeSeats(char ***seats, int rows, int cols) {
   int currRow;

   //iterate through each row
   for (currRow = 0; currRow < rows; currRow++) {
      // free pointer to current row of seats
      free(seats[currRow]);
   }

   //free two dimensional array of seats
   free(seats);
}
