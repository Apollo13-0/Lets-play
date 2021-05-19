#include "Backtracking.h"



bool Backtracking::findRoute(List<List<int>> connectionList, int start, int finish, List<int> &visited,List<int> &path)
{
    if (start == finish){
        cout << "caso base" << endl;
        path.insertFirst(start);
        return true;
    }

    visited.insertLast(start);
    cout << "inserte visited  ";
    visited.printList();
    // recorrer filas
   // for (int i = 0; i <= connectionList.getSize()-1; ++i) {
    List<int> connections = connectionList.find(start-1)->getValue();
    connections.printList();
    // recorrer columnas
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

    //}
}

List<int> Backtracking::ShortestRoute(List<List<int>> connectionList, int start,int finish)
{
    List<int> visited;
    List<int> solution_path;
    cout << "shortest route"<< endl;
    findRoute(connectionList,start,finish,visited,solution_path);
    cout << "shortest route end"<< endl;
    return solution_path;
}

List<List<int>> Backtracking::getConnectionList(int (*gameMatrix)[10]) {

    List<List<int>> connectionList;


    // entro a la fila
    for (int i = 0; i < 5; i++) {

        //entro a las columnas
        for (int j = 0; j < 10; j++) {
            List<int> nodeConnection;

            //if (gameMatrix[i][j] != 0) {  // quitar los obstaculos

                if (j - 1 != -1){ // 1
                    if (gameMatrix[i][j - 1] != 0)
                    {
                        //cout << "horizontal 2" << endl;
                        nodeConnection.insertLast(gameMatrix[i][j - 1]);
                    }
                }

                // diagonal 2

                if (i-1 != -1 && j -1 != -1){ //2
                    if (gameMatrix[i - 1][j - 1] != 0)
                    {
                        //cout << "diagonal 2" << endl;
                        nodeConnection.insertLast(gameMatrix[i - 1][j - 1]);
                    }
                }

                if (i + 1 != 5 && j - 1 != -1){ //3
                    if (gameMatrix[i + 1][j - 1] != 0)  // PROBLEMA
                    {
                        //cout << "diagonal 1.1" << endl;
                        nodeConnection.insertLast(gameMatrix[i + 1][j - 1]);
                    }
                }

                // vertical
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

                // horizontal
                if (j + 1 != 10){ // 6
                    if (gameMatrix[i][j + 1] != 0)
                    {
                        //cout << "horizontal 1" << endl;
                        nodeConnection.insertLast(gameMatrix[i][j + 1]);
                        //nodeConnection.printList();
                    }
                }

                // diagonal 1
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




    //            cout << "-------------" << gameMatrix[i][j] << "----";
    //            nodeConnection.printList();
                connectionList.insertLast(nodeConnection);
                //cout<< connectionList.getSize()<< "  back" <<endl;
                //nodeConnection.delete_all();

            //}
        }

    }

//    for (int i = 0; i < 50; i++) {
//        cout << "------- "<< i << " ";
//        connectionList.find(i)->getValue().printList();
//    }

    return connectionList;
}

Backtracking::Backtracking() {

}
