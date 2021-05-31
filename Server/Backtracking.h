#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include "List.h"

//! Class that find the shortest path between 2 points in a matrix
class Backtracking {

public:

    Backtracking();

    List<List<int>> getConnectionList(matrixNode[][10]);

    bool findRoute(List<List<int>> connectionList, int start, int finish, List<int> &visited, List<int> &path);

    string ShortestRoute(List<List<int>> connectionList, int start, int finish);

    string backtrakingString(List<int> path);

};


#endif BACKTRACKING_H
