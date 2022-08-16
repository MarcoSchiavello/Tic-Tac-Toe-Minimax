#include <stdio.h>
#include <stdlib.h>

#define FIELD_DIM 3
#define OK_FILE 2
#define ERR -1

int uploadGameSave(char** field, int* round, int* playerNum);
int createGameSave(char** field, int round, int gameMode);