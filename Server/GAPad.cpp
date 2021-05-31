//
// Created by ingrid on 5/27/21.
//

#include "GAPad.h"
#include <string>
#include "vector"
#include <random>
#include<stdlib.h>
#include <iostream>
#include "List.h"


using namespace std;

/**
 * Initial pad constructor
 */
*GAPad::GAPad(int rows_, int columns_) {
    rows = rows_;
    columns = columns_;
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

/**
 * Function in charge of change the position of two pieces
 * @param a Position of piece one
 * @param b Position of piece two
 */
void GAPad::swap(vector<int> a, vector<int> b){
    int a1 = a.at(0);
    int a2 = a.at(1);
    int b1 = b.at(0);
    int b2 = b.at(1);
    int aux = GAPad::board[a1][a2];
    GAPad::board[a1][a2] = GAPad::board[b1][b2];
    GAPad::board[b1][b2] = aux;

}

/**
* Funtion to move the left piece
* @return If possible
*/
bool GAPad::move_left() {
    vector<int> index = find_0(0);
    if (index[1] >= (GAPad::columns - 1)){
        return false;
    }
    vector<int> move_to = {index[0], index[1] + 1};
    swap(index, move_to);
    return true;
}

/**
* Funtion to move the right piece
* @return If possible
*/
bool GAPad::move_right() {
    vector<int> index = find_0(0);
    if (index[1] == 0){
        return false;
    }
    vector<int> move_to = {index[0], index[1] - 1};
    swap(index, move_to);
    return true;
}

/**
* Funtion to move the top piece
* @return If possible
*/
bool GAPad::move_up() {
    vector<int> index = find_0(0);
    if (index[0] >= (GAPad::rows - 1)){
        return false;
    }
    vector<int> move_to = {index[0] + 1, index[1] };
    swap(index, move_to);
    return true;
}

/**
* Funtion to move the bottom piece
* @return If possible
*/
bool GAPad::move_down() {
    vector<int> index = find_0(0);
    if (index[0] == 0){
        return false;
    }
    vector<int> move_to = {index[0] - 1, index[1]};
    swap(index, move_to);
    return true;
}

/**
* Funtion to localizate a piece in the Pad
* @param num Piece to search
* @return Position in the pad
*/
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

/**
* Function in charge of mixing the Pad created to start the puzzle
*/
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

/**
* function to apply a series of movements to the pad
* @param chain to the movements
*/
void GAPad::apply_chain(List<string> chain) {
    for (int i = 0; i < chain.getSize(); ++i) {
        string apply = chain.find(i)->getValue();
        if (apply == "up"){move_up();}
        else if (apply == "down"){ move_down();}
        else if (apply == "left"){ move_left();}
        else if (apply == "right"){move_right();}
    }

}

/**
* Function to calculate the error associated to the Pad (fitness)
* @return
*/
float GAPad::cost() {
    /**vector<vector<int>> reference;
    reference.push_back({0,0});
    reference.push_back({0,1});
    reference.push_back({0,2});
    reference.push_back({1,0});
    reference.push_back({1,1});
    reference.push_back({1,2});
    reference.push_back({2,0});
    reference.push_back({2,1});
    reference.push_back({2,2});**/

    vector <vector<int>> reference ;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            reference.push_back({i,j});
        }
    }

    float error = 0.0;
    vector<int>index = {};
    vector<int>ref_ind = {};
    //for (int i = 0; i < 9; ++i) {
    for (int i = 0; i < (rows*columns); ++i) {
        index = find_0(i);
        ref_ind = reference.at(i);
        error += pow((index.at(0) - ref_ind.at(0)), 2)
                 + pow((index.at(1) - ref_ind.at(1)), 2);
    }
    float test = rows*columns;
    error /= test;
    //error /= 9.0;
    return error;
}

