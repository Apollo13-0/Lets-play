//
// Created by usuario on 5/22/21.
//

#ifndef SERVER_A_PATHFINDIG_H
#define SERVER_A_PATHFINDIG_H
#pragma once
#include <stack>
#include <vector>
#include <array>
#include "cfloat"
#include "matrixNode.h"
#include "Matrix.h"
#include "List.h"

class AStar {
public:

    static bool isValid(int x, int y) { //If our Node is an obstacle it is not valid
        Matrix *matrix = Matrix::GetInstance();
        matrix->gameField[x][y].isObstacule();

        return !matrix->gameField[x][y].isObstacule();
    }

    static bool isDestination(int x, int y, matrixNode dest) {
        if (x == dest.getX() && y == dest.getY()) {
            return true;
        }
        return false;
    }

    static double calculateH(int x, int y, matrixNode dest) {
        double H = (sqrt((x - dest.getX())*(x - dest.getX())
                         + (y - dest.getY())*(y - dest.getY())));
        return H;
    }

    static List<int> makePath(matrixNode gameField [5][10], matrixNode dest) {
        try {
            cout << "Found a path" << endl;
            int x = dest.getX();
            int y = dest.getY();
            List<int> path;
            List<int> usablePath;

            while (!(gameField[x][y].getParentX() == x && gameField[x][y].getParentY() == y)
                   && gameField[x][y].getX() != -1 && gameField[x][y].getY() != -1)
            {
                path.insertFirst(gameField[x][y].getPosition());
                int tempX = gameField[x][y].getParentX();
                int tempY = gameField[x][y].getParentY();
                x = tempX;
                y = tempY;

            }
            path.insertFirst(gameField[x][y].getPosition());

            while (path.getSize()!=0) {
                Node<int> *topNode = path.find(0);
                int top = topNode->getValue();
                path.deleteNode(topNode->getValue());
                //cout << top.x << " " << top.y << endl;
                usablePath.insertLast(top);
            }
            return usablePath;
        }
        catch(const exception& e){
            cout << e.what() << endl;
        }
    }


    static List<int> aStar(int playerPos, int destPos) {
        Matrix *matrix = Matrix::GetInstance();
        matrixNode player = matrix->FindinPosition(playerPos);
        matrixNode dest = matrix->FindinPosition(destPos);

        List<int> empty;
        if (isValid(dest.getX(), dest.getY()) == false) {
            cout << "Destination is an obstacle" << endl;
            return empty;
            //Destination is invalid
        }
        if (isDestination(player.getX(), player.getY(), dest)) {
            cout << "You are the destination" << endl;
            return empty;
            //You clicked on yourself
        }
        if (isValid(player.getX(), player.getY()) == false) {
            return aStar(playerPos+1,destPos);
        }
        bool closedList[5][10];

        //Initialize whole map
        matrix->ResetforPathfinding();
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 10; j++) {
                closedList[i][j] = false;
            }
        }

        //Initialize our starting list
        int x = player.getX();
        int y = player.getY();
        matrix->gameField[x][y].setFCost(0.0);
        matrix->gameField[x][y].setGCost(0.0);
        matrix->gameField[x][y].setHCost(0.0);
        matrix->gameField[x][y].setParentX(x);
        matrix->gameField[x][y].setParentY(y);

        List<matrixNode> openList;
        openList.insertLast(matrix->gameField[x][y]);
        bool destinationFound = false;
        while (openList.getSize()!=0&&openList.getSize()<50) {
            matrixNode node;
            do {
                float temp = FLT_MAX;
                matrixNode itNode;
                Node<matrixNode> *it = openList.find(0);
                for (int i =0;i < openList.getSize(); i++) {
                    matrixNode n = it->getValue();
                    if (n.getFCost() < temp) {
                        temp = n.getFCost();
                        itNode = it->getValue();
                    }

                    it = it->getNext();
                }
                node = itNode;
                openList.deletematrixNode(itNode);
            } while (isValid(node.getX(), node.getY()) == false);
            x = node.getX();
            y = node.getY();
            closedList[x][y] = true;

            //For each neighbour starting from North-West to South-East
            for (int newX = -1; newX <= 1; newX++) {
                for (int newY = -1; newY <= 1; newY++) {
                    double gNew, hNew, fNew;
                    if (isValid(x + newX, y + newY)) {
                        if (isDestination(x + newX, y + newY, dest))
                        {
                            matrix->gameField[x + newX][y + newY].setParentX(x);
                            matrix->gameField[x + newX][y + newY].setParentY(y);
                            destinationFound = true;
                            return makePath(matrix->gameField, dest);
                        }
                        else if (closedList[x + newX][y + newY] == false)
                        {
                            if(newX == newY){
                                gNew = node.getGCost() + 1.4;
                            } else {
                                gNew = node.getGCost() + 1.0;
                            }
                            hNew = calculateH(x + newX, y + newY, dest);
                            fNew = gNew + hNew;
                            if (matrix->gameField[x + newX][y + newY].getFCost() == FLT_MAX ||
                                matrix->gameField[x + newX][y + newY].getFCost() > fNew)
                            {
                                // Actualizar datos de los vecinos
                                matrix->gameField[x + newX][y + newY].setFCost(fNew);
                                matrix->gameField[x + newX][y + newY].setGCost(gNew);
                                matrix->gameField[x + newX][y + newY].setHCost(hNew);
                                matrix->gameField[x + newX][y + newY].setParentX(x);
                                matrix->gameField[x + newX][y + newY].setParentY(y);
                                openList.insertLast(matrix->gameField[x + newX][y + newY]);

                            }
                        }
                    }
                }
            }
        }
        if (destinationFound == false) {
            cout << "Destination not found" << endl;
            return empty;
        }
    }
};
#endif //SERVER_A_PATHFINDIG_H
