#ifndef SERVER_BPCREATEOBSTACULES_H
#define SERVER_BPCREATEOBSTACULES_H

#endif //BPCREATEOBSTACULES_H
#include <string>
#include "Matrix.h"

using namespace std;
string createObstacules(int obs_amount){
    Matrix *matrix = Matrix::GetInstance();
    int i=0;
    string str_matrix_res;
    while (i < obs_amount){
        srand (time(NULL));
        int row = rand() %5;
        srand (time(NULL));
        int column = rand() %4;
        if ( !(row == 3 && (column == 0 || column == 9))  && !matrix->gameField[row][column].isObstacule()){
            matrix->gameField[row][column].setObstacule(true);
            str_matrix_res += to_string(row);
            str_matrix_res += to_string(column);
            i++;
        }
    }
    i=0;
    while (i < obs_amount){
        srand (time(NULL));
        int row = rand() %5;
        srand (time(NULL));
        int column = rand() %4+5;

        if ( !(row == 3 && (column == 0 || column == 9))  && !matrix->gameField[row][column].isObstacule()){
            matrix->gameField[row][column].setObstacule(true);
            str_matrix_res += to_string(row);
            str_matrix_res += to_string(column);
            i++;
        }
    }
    return str_matrix_res;
}