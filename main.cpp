#include <iostream>

#include "List/List.h"
#include "Backtracking.h"


using namespace std;
int main()
{

    int matrix[5][10] =
            {{1,2,3,4,5,6,7,0,9,10},{11,12,0,0,15,16,17,18,19,20},{21,22,23,24,0,26,0,28,0,30},{31,32,33,34,0,36,37,38,39,40},{41,0,43,44,45,0,47,48,0,50}};

    Backtracking tmp = Backtracking();
    List<List<int>> connectionList = tmp.getConnectionList(matrix);

    List<int> result = tmp.ShortestRoute(connectionList,47,21);
    cout << "RESULT:  ";
    result.printList();
    return 0;
}
