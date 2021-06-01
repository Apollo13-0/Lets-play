//
// Created by usuario on 5/18/21.
//

#ifndef SERVER_BPGAMELOGIC_H
#define SERVER_BPGAMELOGIC_H

#endif //SERVER_BPGAMELOGIC_H
#include <string>
#include "Matrix.h"
#include "json.hpp"
#include "BPCreateObstacules.h"
#include "A* Pathfindig.h"
#include "Backtracking.h"

using namespace std;
using json = nlohmann::json;
int winCondition;
int J1goals;
int J2goals;

/**
 * Parse List of string to string
 */
string LtoS(List<int> path){
    string pathS;
    for (int i=0; i<path.getSize(); i++){
        if (to_string(path.find(i)->getValue()).size() == 1){
            pathS+="0"+to_string(path.find(i)->getValue())+"$";
        }
        else{
            pathS+=to_string(path.find(i)->getValue())+"$";
        }

    }
    cout << pathS << endl;
    return pathS;
}

/**
 * Manage game events of BP Game
 * @param jmessageR Event
 * @return Instrucctions to do
 */
string bpLogic(json jmessageR){
    string key = jmessageR.value("Key", "oops");
    if (key == "Config"){
        string score =  jmessageR.value("Info1", "oops");
        winCondition = stoi(score);
        string obs_amount =  jmessageR.value("Info2", "oops");
        string str_matrix_res = createObstacules(stoi(obs_amount));
        return str_matrix_res;
    }
    if (key == "J1"){
        string Info1 =  jmessageR.value("Info1", "oops");
        if (Info1 == "goal"){
            J1goals +=1;
            if (J1goals >= winCondition) {
                return "WIN";
            }
        }
        else{
            List<int> path = AStar().aStar(stoi(Info1), 29);
            return LtoS(path);
        }

    }
    if (key == "J2"){
        string Info1 =  jmessageR.value("Info1", "oops");
        if (Info1 == "goal"){
            J2goals +=1;
            if (J2goals >= winCondition) {
                return "LOSE";
            }
        }
        else{
            Matrix *matrix = Matrix::GetInstance();
            Backtracking tmp = Backtracking();
            List<List<int>> connectionList = tmp.getConnectionList(matrix->gameField);
            string result = tmp.ShortestRoute(connectionList, stoi(Info1) + 1, 21);
            return result;
        }

    }
}