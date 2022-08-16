#include <stdio.h>
#include <stdlib.h>
#include "implh/utils.h"
#include "implh/minimax.h"
#include "implh/files.h"
#include "implh/IO.h"

/*__________Main___________*/
int main() {
	int i, j, round = 0, winner = 0, playerNum;
    char** field;
	NEW_MATRIX(FIELD_DIM, FIELD_DIM, char, field)

	srand(time(NULL));

    if(toupper(askGameSave(field, &round, &playerNum)) != 'S') {
        playerNum = askNumberPlayer();

        for(int i = 0; i < FIELD_DIM; i++)
            for(int j = 0; j < FIELD_DIM; j++)
                field[i][j] = ' ';
    }

    clearScreen();
    drawField(field);

    while(round < 9 && winner == 0) {
        if(round % 2 == 0) {
            if(manualSelection(field, 'X', round, playerNum) == OK_FILE) {
              printf("\n\nil file e stato salvato, alla prossima");
              return 0;
            }
        } else {
            switch(playerNum) {
                case 1:                    
                    AIpick(field);
                break;

                case 2:
                    clearScreen();
                    drawField(field);

                    if(manualSelection(field, 'O', round, playerNum) == OK_FILE) {
                      printf("\n\nil file e stato salvato, alla prossima");
                      return 0;
                    }
                break;
            }
        }

        winner = checkWinner(field);

        round++;

        clearScreen();
        drawField(field);
    }

    displayWinner(playerNum, winner);
  
    //FREE_MATRIX(field, char)

    scanf("%d", &i);

    return 0;
}