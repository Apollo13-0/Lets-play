//
// Created by usuario on 5/18/21.
//

#include <iostream>
#include "Matrix.h"
#include "cfloat"

using namespace std;
Matrix* Matrix::instance= NULL;
Matrix::Matrix() {
    int rows = (sizeof (Matrix::gameField)/sizeof (Matrix::gameField [0]));
    int columns = (sizeof (Matrix::gameField[0])/sizeof (Matrix::gameField [0][0]));
    int position =0;
    for (int i=0; i < rows; i++ ){
        for (int j=0; j < columns; j++){
            Matrix::gameField [i][j].setPosition(position);
            Matrix::gameField[i][j].setFCost(FLT_MAX);
            Matrix::gameField[i][j].setGCost(FLT_MAX);
            Matrix::gameField[i][j].setHCost(FLT_MAX);
            Matrix::gameField[i][j].setParentX(-1);
            Matrix::gameField[i][j].setParentY(-1);
            Matrix::gameField[i][j].setX(i);
            Matrix::gameField[i][j].setY(j);
            position++;
        }
    }
}
void Matrix::ResetObstaculesMatrix(){
    int rows = (sizeof (Matrix::gameField)/sizeof (Matrix::gameField [0]));
    int columns = (sizeof (Matrix::gameField[0])/sizeof (Matrix::gameField [0][0]));
    for (int i=0; i < rows; i++ ){
        for (int j=0; j < columns; j++){
            Matrix::gameField [i][j].setObstacule(false);
        }
    }
}
Matrix *Matrix::GetInstance() {
    if (instance == NULL){
        instance = new Matrix();
    }
    return instance;
}

matrixNode Matrix::FindinPosition(int position){
    int row=0;
    int column= position%10;
    if (column != position){
        row = position/10;
    }

    return Matrix::gameField [row][column];
}

void Matrix::ResetforPathfinding (){
    int rows = (sizeof (Matrix::gameField)/sizeof (Matrix::gameField [0]));
    int columns = (sizeof (Matrix::gameField[0])/sizeof (Matrix::gameField [0][0]));
    int position =0;
    for (int i=0; i < rows; i++ ){
        for (int j=0; j < columns; j++){
            Matrix::gameField[i][j].setFCost(FLT_MAX);
            Matrix::gameField[i][j].setGCost(FLT_MAX);
            Matrix::gameField[i][j].setHCost(FLT_MAX);
            Matrix::gameField[i][j].setParentX(-1);
            Matrix::gameField[i][j].setParentY(-1);
        }
    }
}