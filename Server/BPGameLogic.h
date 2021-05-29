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

using namespace std;
using json = nlohmann::json;
int winCondition;

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
    return pathS;
}

string bpLogic(json jmessageR){
    string key = jmessageR.value("Key", "oops");
    if (key == "Config"){
        string score =  jmessageR.value("Info1", "oops");
        winCondition = stoi(score);
        string obs_amount =  jmessageR.value("Info2", "oops");
        string str_matrix_res = createObstacules(stoi(obs_amount));
        return str_matrix_res;
    }
    if (key == "J1Path"){

        string ballPos =  jmessageR.value("Info1", "oops");
        List<int> path = AStar().aStar(stoi(ballPos), 29);

        return LtoS(path);
    }
}