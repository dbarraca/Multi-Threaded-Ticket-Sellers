#ifndef SELLER_H
#define SELLER_H

#define SELLERS 10
#define SELL_TYPE 3

typedef struct Seller{
   char * name;
   int qIndex;
   int order;
} Seller;


Seller **createSellers();
#endif
