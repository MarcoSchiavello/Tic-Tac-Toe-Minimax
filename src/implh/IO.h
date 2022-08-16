#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "files.h"

#define FIELD_DIM 3
#define OK 1

int manualSelection(char** field, char letter, int round, int gameMode);
void drawField(char** field);
void clearScreen();
char askGameSave(char** field, int* round, int* playerNum);
int askNumberPlayer();
void displayWinner(int playerNum, int winner);