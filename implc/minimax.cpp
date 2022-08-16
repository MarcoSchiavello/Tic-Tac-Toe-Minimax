#include "../implh/minimax.h"

#define OPTIM
//#define DEBUG

evalRecord_t minimax(char** field, int high, int alpha, int beta, bool maximize) {
    #ifdef DEBUG
        char input;
    #endif

    int eval = checkWinner(field);
    if((findNthBlankSpace(field).row == -1) || eval != 0 || !high) {
        #ifdef DEBUG
            printf("eval res: %d\n", eval);
            scanf("%c", &input); 
        #endif

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

        #ifdef DEBUG
            printf("|| childNum: %d - high: %d | role: %s\n", childNum, high, maximize ? "true" : "false");
            drawField(field);
            
            scanf("%c", &input);
        #endif

        evalRecord_t evalRecord = minimax(field, high - 1, alpha, beta, !maximize);
        evalRecord.actionPosition = (position_t){ nextPos.row, nextPos.col };

        #ifdef DEBUG
            printf("child res{ value: %d || row: %d || col: %d }\n", evalRecord.value, evalRecord.actionPosition.row, evalRecord.actionPosition.col);

            scanf("%c", &input);
        #endif

        maxEvalRecord = (evalRecord.value > maxEvalRecord.value) ? evalRecord : maxEvalRecord;
        minEvalRecord = (evalRecord.value < minEvalRecord.value) ? evalRecord : minEvalRecord;

        #ifdef OPTIM
            if(maximize)
                alpha = alpha > evalRecord.value ? alpha : evalRecord.value;
            else
                beta = beta > evalRecord.value ? evalRecord.value : beta;
        #endif

        field[nextPos.row][nextPos.col] = ' ';

        #ifdef OPTIM
            if(beta <= alpha)
                break;
        #endif
    }

    #ifdef DEBUG
        printf("END CHILDREN LIST\n\n");
        scanf("%c", &input);
    #endif

    return maximize ? maxEvalRecord : minEvalRecord;
} 

position_t findNthBlankSpace(char** field, int blankNum) {
    for(int i = 0; i < FIELD_DIM; i++)
        for(int j = 0; j < FIELD_DIM; j++)
            if(field[i][j] == ' ') {

                #ifdef DEBUG
                    printf("current blank{ row: %d || col: %d || blankLeft: %d }\n", i, j, blankNum);
                #endif

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

    #ifdef DEBUG
        for(int i = 0; i < FIELD_DIM; i++)
            for(int j = 0; j < FIELD_DIM; j++)
                field[i][j] = ' ';

        field[0][0] = 'O';
        field[0][1] = ' ';
        field[0][2] = 'X';

        field[1][0] = ' ';
        field[1][1] = ' ';
        field[1][2] = ' ';

        field[2][0] = 'O';
        field[2][1] = ' ';
        field[2][2] = 'X';
    #endif

    evalRecord_t res = minimax(field, INT_MAX, INT_MIN, INT_MAX);

    #ifdef DEBUG
        printf("optimal solution{ row: %d || col: %d |||| value:  %d }\n", res.actionPosition.row, res.actionPosition.col, res.value);
    #endif

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