#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "seller.h"

Seller *createSeller(int index) {
   Seller *seller = malloc(sizeof(Seller));
   // order of rows for high priced ticket seller to assign seats to
   int Horder[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
   // order of rows for medium priced ticket seller to assign seats to
   int Morder[10] = {5, 6, 4, 7, 3, 8, 2, 9, 1, 0};
   // order of rows for low priced ticket seller to assign seats to
   int Lorder[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

   // allocate space for name
   seller->name = calloc(sizeof(char), 3);
   //allocate space for order of rows for seller to assign seats to
   seller->order = malloc(sizeof(int) * 10);

   // set seller name to seller's type and number of that type
   if (index == 0) {
      strcpy(seller->name, "H1");
      memcpy(seller->order,Horder, sizeof(int) * ROWS);
   }
   else if (index >= 1 && index <= 3) {
      strcpy(seller->name, "M1");
      seller->name[1] = index + 48;

      memcpy(seller->order, Morder, sizeof(int) * ROWS);
   }
   else if(index >= 4 && index<= 10) {
      strcpy(seller->name, "L1");
      seller->name[1] = index + 45;
      memcpy(seller->order, Lorder, sizeof(int) * ROWS);
   }

   // set seller's current indxc in buyer queue to zero
   seller->qIndex = 0;
   // set last buyer to arrive in seller queue to zero
   seller->arrivedIndex = 0;
   // set index in order holding current row to assign seats to to zero
   seller->currRowIndex = 0;
   // set current column to assign seats to to zero
   seller->currCol = 0;
   // set number of seats assigned to zero
   seller->seatCount = 0;

   return seller;
}

Seller **createSellers(int numSellers) {
   int index;
   Seller **sellers = malloc(sizeof(Seller *) * numSellers);

   // create each seller
   for (index = 0; index <  numSellers; index++) {
      sellers[index] = createSeller(index);
   }

   return sellers;
}

void freeSellers(Seller **sellers, int numSellers) {
   int index;

   // iterate through each seller
   for (index = 0; index <  numSellers; index++) {
      // free allocated space for each seller
      free(sellers[index]->name);
      free(sellers[index]->order);
      free(sellers[index]);
   }
}
