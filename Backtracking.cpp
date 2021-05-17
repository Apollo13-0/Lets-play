#include "Backtracking.h"

bool Backtracking::findRoute(List<List<int>> connectionList, int start, int finish, List<int> &visited,List<int> &path)
{
//    if (start == finish){
//        path.insertFirst(start);
//        return true;
//    }
//
//    visited.insertLast(start);

}

List<int> Backtracking::ShortestRoute(List<List<int>> connectionList, int start,int finish)
{
    List<int> visited;
    List<int> solution_path;
    findRoute(connectionList,start,finish,visited,solution_path);
    return solution_path;
}