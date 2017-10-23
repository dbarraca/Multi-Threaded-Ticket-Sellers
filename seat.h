#ifndef SEAT_H
#define SEAT_H

#define ROWS 10
#define COLS 10

char ***createSeats(int row, int cols);

void printSeats(char ***seats, int rows, int cols);

void freeSeats(char ***seats, int rows, int cols);

#endif
