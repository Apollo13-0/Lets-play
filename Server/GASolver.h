//
// Created by ingrid on 5/27/21.
//

#ifndef SERVER_GASOLVER_H
#define SERVER_GASOLVER_H
#include "GAPad.h"
#include "GAChromosome.h"
#include <iostream>
#include <random>
#include <iomanip>
#include "GASolver.h"
#include<time.h>
#include<stdlib.h>
//#include "tinyxml/tinyxml.h"

/**
 * Class to create the puzzle Solver
 */
class GASolver {
public:
    GAPad board;
    int initial_population;
    float mutation_chance;
    float cross_over_rate;
    vector<GAChromosome> population = {};
    GAChromosome best = GAChromosome(board, {});
    int isbest;
    float error;

    GASolver(GAPad ex_board, int POPULATION_LEN, float MUTATION_CHANCE, float CROSS_OVER_RATE, GAChromosome par);
    void init_population();
    bool calculate_error();
    void select_best();
    int select_i(vector<float> totals, float running);
    void cross_over(bool always);
    int min(int a, int b);
    void mutate();
    GAChromosome solve(int max_iter, float optimal_error);
    void display(int iter);
    void XML(int iteration);

};
#endif //SERVER_GASOLVER_H
