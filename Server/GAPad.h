//
// Created by ingrid on 5/27/21.
//

#ifndef SERVER_GAPAD_H
#define SERVER_GAPAD_H
#include "vector"
#include "string"
#include "List/List.h"

using namespace std;

/**
 * Initial pad constructor
 */
class GAPad {

public:
    int rows;
    int columns;
    vector <vector<int>> board ;

    *GAPad(int rows_, int columns_);
    void swap(vector<int> a, vector<int> b);
    bool move_left();
    bool move_right();
    bool move_up();
    bool move_down();
    vector<int> find_0(int num);
    void shuffle();
    void apply_chain(List<string> chain);
    float cost ();

};

#endif //SERVER_GAPAD_H
