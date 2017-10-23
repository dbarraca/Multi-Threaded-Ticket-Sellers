#ifndef SELLER_H
#define SELLER_H

#include "seat.h"

#define SELLERS 10
#define SELL_TYPE 3

typedef struct Seller{
   char * name;
   int qIndex;
   int *order;
   int currRowIndex;
   int currCol;
   int seatCount;
} Seller;


Seller **createSellers();

void freeSellers(Seller **sellers, int numSellers);

#endif
