#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "seller.h"

Seller *createSeller(int index) {
   Seller *seller = malloc(sizeof(Seller));
   int Horder[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
   int Morder[10] = {5, 6, 4, 7, 3, 8, 2, 9, 1, 0};
   int Lorder[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

   seller->name = calloc(sizeof(char), 3);
   seller->order = malloc(sizeof(int) * 10);

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

   seller->qIndex = 0;
   seller->arrivedIndex = 0;
   seller->currRowIndex = 0;
   seller->currCol = 0;
   seller->seatCount = 0;

   return seller;
}

Seller **createSellers(int numSellers) {
   int index;
   Seller **sellers = malloc(sizeof(Seller *) * numSellers);

   for (index = 0; index <  numSellers; index++) {
      sellers[index] = createSeller(index);
   }

   return sellers;
}

void freeSellers(Seller **sellers, int numSellers) {
   int index;

   for (index = 0; index <  numSellers; index++) {
      free(sellers[index]->name);
      free(sellers[index]->order);
      free(sellers[index]);
   }
}
