//
// Created by usuario on 5/18/21.
//

#ifndef SERVER_MATRIX_H
#define SERVER_MATRIX_H


#include "matrixNode.h"

/**
 * Class of the Pathfinding
 */
class Matrix {

protected:
    Matrix();
    static Matrix *instance;
public:
    matrixNode gameField [5][10];
    Matrix(Matrix &other) = delete;
    void operator=(const Matrix &) = delete;
    static Matrix *GetInstance();
    matrixNode FindinPosition(int position);

    void ResetforPathfinding();

    void ResetObstaculesMatrix();
};


#endif //SERVER_MATRIX_H

