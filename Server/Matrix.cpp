//
// Created by usuario on 5/18/21.
//

#include <iostream>
#include "Matrix.h"

using namespace std;
Matrix* Matrix::instance= NULL;
Matrix::Matrix() {
    int rows = (sizeof (Matrix::gameField)/sizeof (Matrix::gameField [0]));
    int columns = (sizeof (Matrix::gameField[0])/sizeof (Matrix::gameField [0][0]));
    int position =1;
    for (int i=0; i < rows; i++ ){
        for (int j=0; j < columns; j++){
            Matrix::gameField [i][j].setPosition(position);
            position++;
        }
    }
}

Matrix *Matrix::GetInstance() {
    if (instance == NULL){
        instance = new Matrix();
    }
    return instance;
}


