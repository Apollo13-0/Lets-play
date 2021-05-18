#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include "List/List.h"


class Backtracking {

public:

    //ver si es mejor hacerlo singleton
    Backtracking();

    List<List<int>> getConnectionList(int gameMatrix[][10]);

    bool findRoute(List<List<int>> connectionList, int start, int finish, List<int> &visited, List<int> &path);

    List<int> ShortestRoute(List<List<int>> connectionList, int start, int finish);


};


#endif BACKTRACKING_H
