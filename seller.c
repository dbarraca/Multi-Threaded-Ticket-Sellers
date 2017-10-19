#include <string.h>

#include "seller.h"

Seller *createSeller(int index) {
   Seller *seller = malloc(sizeof(Seller));
   if (index == 0)
      seller->name = "H1";
   else if (index >= 1 && index <= 3)
      seller->name = strcat("M", index);
   else if(index >= 4 && index<= 10)
      seller->name = strcat("l", index - 3);

   seller->qIndex = 0;

//   seller->order=;

   return seller;
}

Seller **createSellers() {
   int index;
   Seller **sellers = malloc(sizeof(Seller *) * SELLERS);

   for (index = 0; index < SELLERS; sellers++)
      sellers[index] = createSeller(index);

   return sellers;
}
