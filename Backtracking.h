#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include "List/List.h"

//! Class that find the shortest path between 2 points in a matrix
class Backtracking {

public:

    Backtracking();

    List<List<int>> getConnectionList(int gameMatrix[][10]);

    bool findRoute(List<List<int>> connectionList, int start, int finish, List<int> &visited, List<int> &path);

    List<int> ShortestRoute(List<List<int>> connectionList, int start, int finish);


};


#endif BACKTRACKING_H
