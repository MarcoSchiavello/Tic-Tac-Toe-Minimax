#include "../implh/IO.h"

/**
*   dato un array fa selezionare dove mettere il segno
*   che sar� indicato come secondo parametro
*   params:
*       @param char campo[][] : output : campo di gioco
*       @param char segno : input : indica quale simbolo posizionale
*       @param int turno : input : numero del turno
*       @param int gameMode : input : indica se c'e il giocatore singolo o multigiocatore
*       @return int : status code
*/
int manualSelection(char** field, char letter, int round, int gameMode) {
    int row, col, choice;
    bool err;

    printf("1) scegli cordinate dove mettere la %c\n", letter);
    printf("0) esci\n");
    printf("scegli:");
    scanf("%d",&choice);

    if(!choice)
        return createGameSave(field, round, gameMode);

    do {
        err = false;

        printf("indice righa tra 1 e 3: ");
        scanf ("%d", &row);
        row--;

        printf("indica colonna tra 1 e 3: ");
        scanf ("%d", &col);
        col--;

        if(field[row][col] != ' ' || ( row < 0 || row > 2 ) ||  ( col < 0 || col > 2 )) {
            err = true;
            printf("questa posizione e' gia' stata occupata o e' fuori dal campo rimetti \n");
        }

        printf("\n\n");
    } while(err);

    field[row][col] = letter;

  return OK;
}

/**
*   stampa il campo di gioco
*   params:
*       @param char campo[][] : output : campo di gioco da stampare
*       @return void
*/
void drawField(char** field) {
    printf("   1   2   3 \n");
    printf(" o---o---o---o \n");

	for(int i = 0; i < FIELD_DIM; i++) {
        printf("%d", i + 1);

        for(int j = 0; j < FIELD_DIM; j++)
            printf("| %c ", field[i][j]);

        printf("|\n");
        printf(" o---o---o---o \n");
	}
}

/**
*   ripulisce lo schermo
*   params:
*       @return void
*/
void clearScreen() {
  system("clear");
}

char askGameSave(char** field, int* round, int* playerNum) {
    int fileStatus = 0;
    char choice;

    do {
        clearScreen();

        if(fileStatus == ERR) {
            printf("Impossibile trovare il file\n\n");
            fileStatus = 0;
        }

        printf("Benvenuto nel gioco del tris\n");
        printf("vuoi caricare una partita gia in processo (S o N): ");
        scanf(" %c",&choice);

        if(toupper(choice) == 'S')
        fileStatus = uploadGameSave(field, round, playerNum);

    } while((toupper(choice) != 'S' && toupper(choice) != 'N') || fileStatus == ERR);

    return choice;
}

int askNumberPlayer() {
    int playerNum;

    do {
      printf("quanti giocatori min 1 max 2: ");
      scanf("%d", &playerNum);
    } while(playerNum < 1 || playerNum > 2);

    return playerNum;
}

void displayWinner(int playerNum, int winner) {
    switch(winner) {
        case 0:
            printf("\nPARITA'\n\n");
        break;

        case 1:
            if(playerNum == 2)
                printf("\nHA VINTO X\n\n");
            else
                printf("\nHAI VINTO \n\n");
        break;

        case 2:
            if(playerNum == 2)
                printf("\nHA VINTO O\n\n");
            else
                printf("\nHAI PERSO \n\n");
        break;

    }
}