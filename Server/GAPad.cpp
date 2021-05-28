//
// Created by ingrid on 5/27/21.
//

#include "GAPad.h"
#include <string>
#include "vector"
#include <random>
#include<stdlib.h>


using namespace std;

*GAPad::GAPad() {
    GAPad::rows = 4;
    GAPad::columns = 4;
    vector<vector<int>> vector_board(GAPad::rows, vector<int> (GAPad::columns, 0));
    int index = 0;
    for (auto &item : vector_board) {
        for (auto &i : item) {
            i = index;
            index += 1;
        }
    }
    GAPad::board = vector_board;
}


void GAPad::swap(vector<int> a, vector<int> b){
    int a1 = a.at(0);
    int a2 = a.at(1);
    int b1 = b.at(0);
    int b2 = b.at(1);
    int aux = GAPad::board[a1][a2];
    GAPad::board[a1][a2] = GAPad::board[b1][b2];
    GAPad::board[b1][b2] = aux;

}

bool GAPad::move_left() {
    vector<int> index = find_0(0);
    if (index[1] >= (GAPad::columns-1)){
        return false;
    }
    vector<int> move_to = {index[0], index[1] + 1};
    swap(index, move_to);
    return true;
}

bool GAPad::move_right() {
    vector<int> index = find_0(0);
    if (index[1] == 0){
        return false;
    }
    vector<int> move_to = {index[0], index[1] - 1};
    swap(index, move_to);
    return true;
}

bool GAPad::move_up() {
    vector<int> index = find_0(0);
    if (index[0] >= (GAPad::rows-1)){
        return false;
    }
    vector<int> move_to = {index[0] + 1, index[1] };
    swap(index, move_to);
    return true;
}

bool GAPad::move_down() {
    vector<int> index = find_0(0);
    if (index[0] == 0){
        return false;
    }
    vector<int> move_to = {index[0] - 1, index[1]};
    swap(index, move_to);
    return true;
}

vector<int> GAPad::find_0(int num) {
    int x = -1;
    int y = -1;
    vector<int> myvector = {0,0};
    for (auto &item : GAPad::board) {
        x++;
        for (auto &i : item) {
            y++;
            if (i == num) {
                vector<int> myvector = {x, y};
                return myvector;
            }
        }
        y = -1;
    }

}

void GAPad::shuffle() {

    int a =  rand()%30 + 10;
    for (int i=0 ; i < a; i++) {
        int move =rand()%5;
        switch (move) {
            case 1:
                GAPad::move_left();
                break;
            case 2:
                GAPad::move_right();
                break;
            case 3:
                GAPad::move_up();
                break;
            case 4:
                GAPad::move_down();
                break;
            default:
                break;
        }

    }
}

void GAPad::apply_chain(vector<string> chain) {
    for (int i = 0; i < chain.size(); ++i) {
        string apply = chain.at(i);
        if (apply == "up"){move_up();}
        else if (apply == "down"){ move_down();}
        else if (apply == "left"){ move_left();}
        else if (apply == "right"){move_right();}
    }

}

float GAPad::cost() {

    vector <vector<int>> reference ;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            reference.push_back({i,j});
        }
    }

    float error = 0.0;
    vector<int>index = {};
    vector<int>ref_ind = {};
    for (int i = 0; i < (rows*columns); ++i) {
        index = find_0(i);
        ref_ind = reference.at(i);
        error += pow((index.at(0) - ref_ind.at(0)), 2)
                 + pow((index.at(1) - ref_ind.at(1)), 2);
    }
    float test = rows*columns;
    error /= test;
    return error;
}

