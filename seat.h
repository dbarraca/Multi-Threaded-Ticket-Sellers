#ifndef SEAT_H
#define SEAT_H

#define ROWS 10
#define COLS 10

/**
 * Create strings representing seats in the theater to hold the name of the
 *  seller who will sell the seat to a buyer and the number of buyers who have
 *  purchase from the seller thus far. Seats are in two dimensional array.
 *
 * rows: number of rows of seats
 * cols: number of columns of seats
 *
 * returns: pointer to two dimensional array of seats
 *
 */
char ***createSeats(int rows, int cols);

void printSeats(char ***seats, int rows, int cols);

void countSeats(char ***seats, int rows, int cols);

void freeSeats(char ***seats, int rows, int cols);

#endif
