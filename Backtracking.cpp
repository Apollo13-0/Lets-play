#include "Backtracking.h"



bool Backtracking::findRoute(List<List<int>> connectionList, int start, int finish, List<int> &visited,List<int> &path)
{
    if (start == finish){
        path.insertFirst(start);
        return true;
    }

    visited.insertLast(start);

    // recorrer filas
    for (int i = 0; i <= connectionList.getSize()-1; ++i) {
        List<int> connections = connectionList.find(i)->getValue();

        // recorrer columnas
        for (int j = 0; j <= connections.getSize() - 1 ; ++j) {
            int cellValue = connections.find(j)->getValue();
            if (!visited.findValue(cellValue)){
                if (findRoute(connectionList, cellValue, finish, visited, path)){
                    path.insertFirst(start);
                    return true;
                }
            }
        }

    }
}

List<int> Backtracking::ShortestRoute(List<List<int>> connectionList, int start,int finish)
{
    List<int> visited;
    List<int> solution_path;
    findRoute(connectionList,start,finish,visited,solution_path);
    return solution_path;
}

List<List<int>> Backtracking::getConnectionList(int (*gameMatrix)[10]) {

    List<List<int>> connectionList;
    List<int> nodeConnection;
    // tamañp del array
    int rows = (sizeof(gameMatrix)/ sizeof(gameMatrix[0]));
    int columns = (sizeof(gameMatrix[0])/ sizeof(gameMatrix[0]));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {

            // horizontal
            if (gameMatrix[i][j + 1] != 0)
            {
                nodeConnection.insertFirst(gameMatrix[i][j + 1]);
            }

            if (gameMatrix[i][j - 1] != 0)
            {
                nodeConnection.insertFirst(gameMatrix[i][j - 1]);
            }

            // vertical
            if (gameMatrix[i + 1][j] != 0)
            {
                nodeConnection.insertFirst(gameMatrix[i + 1][j]);
            }

            if (gameMatrix[i - 1][j] != 0)
            {
                nodeConnection.insertFirst(gameMatrix[i - 1][j]);
            }

            // diagonal 1
            if (gameMatrix[i - 1][j + 1] != 0)
            {
                nodeConnection.insertFirst(gameMatrix[i - 1][j + 1]);
            }
            if (gameMatrix[i + 1][j - 1] != 0)
            {
                nodeConnection.insertFirst(gameMatrix[i + 1][j - 1]);
            }

            // diagonal 2
            if (gameMatrix[i - 1][j - 1] != 0)
            {
                nodeConnection.insertFirst(gameMatrix[i - 1][j - 1]);
            }
            if (gameMatrix[i + 1][j + 1] != 0)
            {
                nodeConnection.insertFirst(gameMatrix[i + 1][j + 1]);
            }

        }
        connectionList.insertLast(nodeConnection);
        nodeConnection.delete_all();
    }
}