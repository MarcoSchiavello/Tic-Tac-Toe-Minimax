#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include "IO.h"

#define FIELD_DIM 3

typedef struct {
    short int row;
    short int col;
} position_t;

typedef struct {
    int value;
    position_t actionPosition; 
} evalRecord_t;

evalRecord_t minimax(char** field, int high, int apha, int beta, bool maximize = true);
position_t findNthBlankSpace(char** field, int blankNum = 1);
void AIpick(char** field);
int checkWinner(char** field);