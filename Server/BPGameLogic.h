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

using namespace std;
using json = nlohmann::json;
int winCondition;

string bpLogic(json jmessageR){
    string key = jmessageR.value("Key", "oops");
    if (key == "Config"){
        string score =  jmessageR.value("Info1", "oops");
        winCondition = stoi(score);
        string obs_amount =  jmessageR.value("Info2", "oops");
        string str_matrix_res = createObstacules(stoi(obs_amount));
        return str_matrix_res;
    }
}