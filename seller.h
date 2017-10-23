#ifndef SELLER_H
#define SELLER_H

#include "seat.h"

#define SELLERS 10
#define SELL_TYPE 3

typedef struct Seller{
   char * name; // name of seller
   int qIndex; // index of seller in queue
   int arrivedIndex; // index of last arrived customer in queue
   int *order; // order of rows seller should assign seats
   int currRowIndex; // index in order variable holding current row to assign seats
   int currCol; // current column to assign a seat
   int seatCount; // number of seat seller has assigned.
} Seller;


Seller **createSellers();

void freeSellers(Seller **sellers, int numSellers);

#endif
