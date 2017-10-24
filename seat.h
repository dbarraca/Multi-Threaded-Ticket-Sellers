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

/**
 * Prints the seating chart. Buyers are identified the seller who sold the seat
 * the number of tickets sold by the seller at the time of the seat being
 * assigned.
 *
 * seats: pointer to two dimensional array of seats
 * rows: number of rows of seats
 * cols: number of columns of seats
 */
void printSeats(char ***seats, int rows, int cols);

/**
 * Counts and prints the number of tickets for each price level.
 *
 * seats: pointer to two dimensional array of seats
 * rows: number of rows of seats
 * cols: number of columns of seats
 */
void countSeats(char ***seats, int rows, int cols);

/**
 * Frees the two dimensional array holding the seats and each pointer to the
 * rows of seats.

 * seats: pointer to two dimensional array of seats
 * rows: number of rows of seats
 * cols: number of columns of seats
 */
void freeSeats(char ***seats, int rows, int cols);

#endif
