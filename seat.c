#include <stdlib.h>
#include <stdio.h>

#include "seat.h"


char ***createSeats(int rows, int cols) {
   int currRow, currCol;
   char ***seats = malloc(sizeof(char **) * rows);

   for (currRow = 0; currRow < rows; currRow++) {
      seats[currRow] = malloc(sizeof(char *) * cols);

      for (currCol = 0; currCol < cols; currCol++)
         seats[currRow][currCol] = NULL;
   }

   return seats;
}

void printSeats(char ***seats, int rows, int cols) {
   int currRow, currCol;

   for (currRow = 0; currRow < rows; currRow++) {
      for (currCol = 0; currCol < cols; currCol++) {
         if (seats[currRow][currCol] == NULL)
            printf("---- ");
         else
            printf("%s ", seats[currRow][currCol]);
      }
      printf("\n");
   }
}

void countSeats(char ***seats, int rows, int cols) {
   int currRow, currCol, HCount = 0, MCount = 0, LCount = 0;

   for (currRow = 0; currRow < rows; currRow++) {
      for (currCol = 0; currCol < cols; currCol++) {
         if (seats[currRow][currCol] != NULL){
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

   printf("%i H customers served.\n", HCount);
   printf("%i M customers served.\n", MCount);
   printf("%i L customers served.\n", LCount);
}

void freeSeats(char ***seats, int rows, int cols) {
   int currRow;

   for (currRow = 0; currRow < rows; currRow++)
      free(seats[currRow]);

   free(seats);
}
