#include "Backtracking.h"


/*!
 * \brief method that finds the path
 *
 * \return bool indicating the path has been found
 */
bool Backtracking::findRoute(List<List<int>> connectionList, int start, int finish, List<int> &visited,List<int> &path)
{
    if (start == finish){
        path.insertFirst(start);
        return true;
    }

    visited.insertLast(start);

    List<int> connections = connectionList.find(start-1)->getValue();


    for (int j = 0; j < connections.getSize() ; j++) {
        int cellValue = connections.find(j)->getValue();
        if (!visited.findValue(cellValue)){
            if (findRoute(connectionList, cellValue, finish, visited, path)){
                path.insertFirst(start);
                return true;
            }
        }
    }
    return false;
}

/*!
 * \brief creates the solution path and the visited list
 *
 * \return List<int> the solution path
 */
string Backtracking::ShortestRoute(List<List<int>> connectionList, int start,int finish)
{
    List<int> visited;
    List<int> solution_path;
    findRoute(connectionList,start,finish,visited,solution_path);
    return backtrakingString(solution_path);
}

/*!
 * \brief generates a list with the connections for each point
 *
 * \return List<List<int>> matrix with the connections for each node
 */
List<List<int>> Backtracking::getConnectionList(int (*gameMatrix)[10]) {

    List<List<int>> connectionList;

    for (int i = 0; i < 5; i++) {

        for (int j = 0; j < 10; j++) {
            List<int> nodeConnection;

            if (j - 1 != -1){ // 1
                if (gameMatrix[i][j - 1] != 0)
                {
                    //cout << "horizontal 2" << endl;
                    nodeConnection.insertLast(gameMatrix[i][j - 1]);
                }
            }

            if (i-1 != -1 && j -1 != -1){ //2
                if (gameMatrix[i - 1][j - 1] != 0)
                {
                    //cout << "diagonal 2" << endl;
                    nodeConnection.insertLast(gameMatrix[i - 1][j - 1]);
                }
            }

            if (i + 1 != 5 && j - 1 != -1){ //3
                if (gameMatrix[i + 1][j - 1] != 0)
                {
                    //cout << "diagonal 1.1" << endl;
                    nodeConnection.insertLast(gameMatrix[i + 1][j - 1]);
                }
            }

            if (i + 1 != 5){ // 4
                if (gameMatrix[i + 1][j] != 0)
                {
                    //cout << "vertical 1" << endl;
                    nodeConnection.insertLast(gameMatrix[i + 1][j]);
                }
            }

            if (i - 1 != -1){ // 5
                if (gameMatrix[i - 1][j] != 0)
                {
                    //cout << "vertical 2" << endl;
                    nodeConnection.insertLast(gameMatrix[i - 1][j]);
                }
            }

            if (j + 1 != 10){ // 6
                if (gameMatrix[i][j + 1] != 0)
                {
                    //cout << "horizontal 1" << endl;
                    nodeConnection.insertLast(gameMatrix[i][j + 1]);
                    //nodeConnection.printList();
                }
            }

            if (i - 1 != -1 && j +1 != 10){ // 7
                if (gameMatrix[i - 1][j + 1] != 0)
                {
                    //cout << "diagonal 1" << endl;
                    nodeConnection.insertLast(gameMatrix[i - 1][j + 1]);
                }
            }

            if (i + 1 != 5 && j + 1 != 10){ //8
                if (gameMatrix[i + 1][j + 1] != 0)
                {
                    //cout << "diagonal 2.2" << endl;
                    nodeConnection.insertLast(gameMatrix[i + 1][j + 1]);
                }
            }

            connectionList.insertLast(nodeConnection);
            //nodeConnection.delete_all();
        }

    }
    return connectionList;
}

Backtracking::Backtracking() {

}

/*!
 * \brief generates a string with the format for printing on display
 *
 * \return string with the solution path
 */
string Backtracking::backtrakingString(List<int> path)
{
    string resultString = "";
    for (int i = 0; i < path.getSize(); i++) {
        resultString = resultString + to_string(path.find(i)->getValue() - 1) + "$";
    }
    return resultString;
}