//
// Created by ingrid on 5/27/21.
//

#include <iostream>
#include <random>
#include "GASolver.h"
#include<stdlib.h>
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"


/**
 * Constructor of the Puzzle solver
 * @param ex_board Pad of the puzzle
 * @param POPULATION_LEN Population initial
 * @param MUTATION_CHANCE The chance to a chromosome go to mutate
 * @param CROSS_OVER_RATE Percentage of the population go to cross
 * @param best The best Chromosome so far
 */

GASolver::GASolver(GAPad ex_board, int POPULATION_LEN, float MUTATION_CHANCE, float CROSS_OVER_RATE, GAChromosome best) : board(ex_board) {
    board = ex_board;
    initial_population = POPULATION_LEN;
    mutation_chance = MUTATION_CHANCE;
    cross_over_rate = CROSS_OVER_RATE;

    vector<GAChromosome> population;
    best = best;
    isbest=0;
    error = NULL;
}

/**
 * Function to init the population
 */
void GASolver::init_population() {
    for(int i = 0; i < initial_population; i++) {
        population.push_back(GAChromosome(board, {}));
    }
}

/**
 * Operate to calculate the error of each Chromosome
 * @return If it can be calculated
 */
bool GASolver::calculate_error() {

    if(population.empty()) {
        return false;
    }
    if(isbest == 0){
        best = population.at(0);
        isbest++;
    }
    float myerror = 0;
    GAChromosome p = population.at(0);
    for(int i = 0; i < population.size(); i++){
        p = population.at(i);
        p.update_error();
        if (p.error < best.error){
            best = population.at(i);
        }
        myerror += p.error;

    }

    error = myerror / population.size();
}

/**
 * Function to selec best of the generation
 */
void GASolver::select_best() {
    vector<float> totals = {};
    float running_total = 0;

    for(int i = 0; i < population.size(); i++){
        float w = 1 / (0.000001 + population.at(i).error);
        running_total += w;
        totals.push_back(running_total);
    }

    vector<GAChromosome> result = {};
    while (result.size() < initial_population){
        int i = select_i(totals, running_total);
        result.push_back(population.at(i));
    }
    population = result;
}

/**
 *
 * @param totals
 * @param running
 * @return
 */
int GASolver::select_i(vector<float> totals, float running) {

    float rnd = rand()%10;
    rnd = (rnd/10)*running;
    for( int i =0; i < totals.size(); i++) {
        if (rnd < totals.at(i)){
            return i;
        }
    }
}

/**
 * Function to cross the population
 * @param always
 */
void GASolver::cross_over(bool always) {
    if (population.size() < 2){
        return;
    }
    float cross_over_occur = ceil(population.size() * cross_over_rate);
    vector<int> list_fertile = {};
    for (int i = 0; i < population.size(); ++i) {
        list_fertile.push_back(i);
    }
    for (int i = 0; i < cross_over_occur; i++) {
        int rnd = rand()%list_fertile.size();
        int a = list_fertile.at(rnd);
        rnd = rand()%list_fertile.size();
        int b = list_fertile.at(rnd);
        for (int index = 0; index < list_fertile.size(); index++) {
            if (list_fertile.at(index) == b || list_fertile.at(index) == a){
                list_fertile.erase(list_fertile.begin() + index);
            }
        }
        vector <GAChromosome> offspring = GAChromosome::cross_over(population.at(a), population.at(b));
        GAChromosome offspring_a = offspring.at(0);
        GAChromosome offspring_b = offspring.at(1);
        if ((offspring_a.error < min(population.at(a).error, population.at(b).error)
             && offspring_b.error < min(population.at(a).error, population.at(b).error))
            || always){
            population.at(a) = offspring_a;
            population.at(b) = offspring_b;
        }
    }
}

/**
 * Function to find the least number of two
 * @param a First number
 * @param b Second number
 * @return Least number
 */
int GASolver::min(int a, int b) {
    if (a >= b){return a;}
    else {return b;}
}

/**
 *
 */
void GASolver::mutate() {
    for (int i = 0; i < population.size(); ++i) {
        float rnd = rand()%10;
        rnd /= 10;
        if (rnd < mutation_chance){

            population.at(i).mutate();
        }
    }
}

GAChromosome GASolver::solve(int max_iter, float optimal_error) {

    init_population();
    int iteration = 0;
    while (iteration < max_iter && (isbest == 0 ||
                                    best.error_puzzle_cost > optimal_error)){
        cross_over(true);

        calculate_error();
        select_best();
        mutate();
        display(iteration);
        //XML(iteration);

        iteration += 1;
    }

    return best;
}

void GASolver::display(int iter) {
    cout<< "~~~~~~~~ iteration: "<<iter<<" ~~~~~~~~"<<endl;
    cout<< "'population: len "<<population.size()<<"   Total Error "<<error<<endl;

    if (isbest != 0){
        cout<<"best: "<<best.error << "   ->   p:"<< best.error_puzzle_cost<< " +  g:"<<best.error_gene_len<<endl;
    }
    cout<<"best is: " << best.gene.getSize()<< "   ";
    for (int i = 0; i < best.gene.getSize(); ++i) {
        cout << best.gene.find(i)->getValue()<< "  ";
    }
    cout<< endl<< "--------------------------------"<<endl;

}

/**void GASolver::XML(int iteration) {
    TiXmlDocument doc;
    TiXmlDeclaration * decl = new TiXmlDeclaration("1.0","utf-8", "");
    doc.LinkEndChild(decl);
    string iter = "Generacion: "  + to_string(iteration);
    TiXmlElement * root;
        root = new TiXmlElement("iter");
            root->SetAttribute("Generacion", iteration);
            for (int i = 0; i < population.size(); i++) {
                root->SetAttribute("Individuo", i);
                string cadena;
                for (int j = 0; j < population.at(i).gene.getSize(); j++) {
                    cadena += population.at(i).gene.find(j)->getValue();
                }
                //root->SetAttribute("Gen", cadena)
                doc.LinkEndChild(root);
    doc.SaveFile("madeByHand.xml");
    }

}**/



