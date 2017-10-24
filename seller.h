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

/**
 * Creates a seller. The seller's name and order of rows to assign seats to
 * are different for each price level seller type which is determined by the
 * index. Other relevant data on seller is set to zero.
 *
 * index: index of seller which is used to determine the seler type and name.
 *
 * returns: pointer the created seller
 */
Seller *createSeller(int index);

/**
 * Creates the sellers for each sell thread to use.
 *
 * returns: pointer the created sellers
 */
Seller **createSellers();

/**
 * Free each seller and free allocated data for each seller including the
 * seller's name and order of rows for seller to assign seats to.
 *
 * sellers: pointer to the sellers to be freed
 * numSellers: number of sellers to be freed
 */
void freeSellers(Seller **sellers, int numSellers);

#endif
