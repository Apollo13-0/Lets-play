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