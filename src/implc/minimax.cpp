#include "../implh/minimax.h"

evalRecord_t minimax(char** field, int high, int alpha, int beta, bool maximize) {
    int eval = checkWinner(field);
    if((findNthBlankSpace(field).row == -1) || eval != 0 || !high) {
        return (evalRecord_t) {
            .value = eval == 2 ? 1 : (eval == 1 ? -1 : 0) ,
            .actionPosition = { -1, -1 }
        };
    }
        
    int childNum = 0;
    evalRecord_t maxEvalRecord = (evalRecord_t){ INT_MIN, { -1, -1 } }, minEvalRecord = (evalRecord_t){ INT_MAX, { -1, -1 } };
    position_t nextPos;

    while((nextPos = findNthBlankSpace(field, ++childNum)).row != -1) {
        field[nextPos.row][nextPos.col] = (maximize * 'O') + (!maximize * 'X');

        evalRecord_t evalRecord = minimax(field, high - 1, alpha, beta, !maximize);
        evalRecord.actionPosition = (position_t){ nextPos.row, nextPos.col };

        maxEvalRecord = (evalRecord.value > maxEvalRecord.value) ? evalRecord : maxEvalRecord;
        minEvalRecord = (evalRecord.value < minEvalRecord.value) ? evalRecord : minEvalRecord;

        if(maximize)
            alpha = alpha > evalRecord.value ? alpha : evalRecord.value;
        else
            beta = beta > evalRecord.value ? evalRecord.value : beta;

        field[nextPos.row][nextPos.col] = ' ';

        if(beta <= alpha)
            break;
    }

    return maximize ? maxEvalRecord : minEvalRecord;
} 

position_t findNthBlankSpace(char** field, int blankNum) {
    for(int i = 0; i < FIELD_DIM; i++)
        for(int j = 0; j < FIELD_DIM; j++)
            if(field[i][j] == ' ') {
                blankNum--;
                if(blankNum <= 0)
                    return (position_t) {
                        .row = (short int) i,
                        .col = (short int) j
                    };
            }

    return { -1, -1 };
}


/**
*   dato un array mette una X dove non ce ninte la posizione
*   precisa e random negli spazi vuoti
*   params:
*       @param char field[][] : output : field di gioco
*       @return void
*/
void AIpick(char** field) {
    evalRecord_t res = minimax(field, INT_MAX, INT_MIN, INT_MAX);

    field[res.actionPosition.row][res.actionPosition.col] = 'O';
}

/**
*   dato un array controlla tutte le combinazioni possibili
*   per vincere di un determinato segno scelto come secondo parametro
*   params:
*       @param char field[][] : output : field di gioco
*       @param char segno : input : segno da controllare se ha vinto
*       @return int : chi ha vinto
*/
int checkWinner(char** field) {

  for(int i = 0; i < FIELD_DIM; i++) {
    if(field[i][0] == field[i][1] && field[i][1] == field[i][2] && field[i][2] != ' ')
      return 2 * (field[i][1] == 'O') + (field[i][1] == 'X');

    if(field[0][i] == field[1][i] && field[1][i] == field[2][i] && field[2][i] != ' ')
      return 2 * (field[1][i] == 'O') + (field[1][i] == 'X');
  }

  if(((field[0][0]==field[1][1] && field[1][1]==field[2][2])
    ||
    (field[0][2]==field[1][1] && field[1][1]==field[2][0])) && field[1][1] != ' ')
    return (2 * (field[1][1] == 'O') + (field[1][1] == 'X'));

  return 0;
}