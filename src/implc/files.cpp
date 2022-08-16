#include "../implh/files.h"

/**
*   legge il file di salvataggio
*   params:
*       @param char field[][FIELD_DIM] : output : field di gioco che deve essere riempito
*       @param int * round : output : puntatore che punta al round del gioco per cambiarlo a quello salvato
*       @param int * playerNum : output : puntatore che punta al numero di giocatori del gioco per cambiarlo a quello salvato
*       @return int : status code
*/
int uploadGameSave(char** field, int* round, int* playerNum) {
  FILE* file;
  char* fileData;

  file = fopen("SalvTris.txt", "r");

  if(file == NULL)
    return ERR;

  fgets(fileData, (FIELD_DIM * FIELD_DIM)+3, file);

  *round = fileData[0] - 48;

  *playerNum = fileData[1] - 48;

  for(int i = 0; i < FIELD_DIM; i++)
    for(int j = 0; j < FIELD_DIM; j++)
        field[i][j] = fileData[ ( ( i * FIELD_DIM ) + j ) + 2 ];

    return OK_FILE;
}

/**
*   crea il file di salvataggio
*   params:
*       @param char field[][FIELD_DIM] : input : field di gioco che deve essere salvato
*       @param int round : input : numero del round
*       @param int gameMode : input : indica se c'e il giocatore singolo o multigiocatore
*       @return int : status code
*/
int createGameSave(char** field, int round, int gameMode) {
  FILE* file;

  file = fopen("SalvTris.txt", "w");

  if(file == NULL)
    return ERR;

  fprintf(file, "%d", round);

  fprintf(file, "%d", gameMode);

  for(int i = 0; i < FIELD_DIM; i++)
    for(int j = 0; j < FIELD_DIM; j++)
        fprintf(file, "%c", field[i][j]);

  return OK_FILE;
}