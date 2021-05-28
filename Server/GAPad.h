//
// Created by ingrid on 5/27/21.
//

#ifndef SERVER_GAPAD_H
#define SERVER_GAPAD_H
#include "vector"
#include "string"

using namespace std;

class GAPad {

public:
    int rows;
    int columns;
    vector <vector<int>> board ;

    *GAPad();
    void swap(vector<int> a, vector<int> b);
    bool move_left();
    bool move_right();
    bool move_up();
    bool move_down();
    vector<int> find_0(int num);
    void shuffle();
    void apply_chain(vector<string> chain);
    float cost ();

};





#endif //SERVER_GAPAD_H
