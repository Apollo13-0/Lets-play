//
// Created by ingrid on 5/27/21.
//


#include "GAChromosome.h"
#include <iostream>
#include<stdlib.h>
#include <iomanip>


/**
 * Constructor or GAChoromosome
 * @param ex_board GAPad of puzzle
 * @param gen Initial gen to save
 */
GAChromosome::GAChromosome(GAPad ex_board, List<string> gen) : puzzle(ex_board) {

    moves.emplace_back("up");
    moves.emplace_back("down");
    moves.emplace_back("left");
    moves.emplace_back("right");

    gene = gen;

    if (gene.getSize() == 0) {
        int a = rand() % 4;
        gene.insertLast(moves.at(a));
    }

    error = NULL;
    error_puzzle_cost = 0;
    error_gene_len = NULL;
    puzzle = ex_board;
    update_error();
}

/**
 * Method to update the error associated to error of the GAChromosome
 */
void GAChromosome::update_error() {
    GAPad temp = puzzle;
    temp.apply_chain(gene);
    /**for (auto &item : temp.board) {
        for (auto &i : item) {

            cout << setw(2) << i << "-";
        }
        cout << endl;
    }**/

    error_puzzle_cost = temp.cost();
    error_gene_len = gene.getSize() * 0.01;
    error = error_puzzle_cost + error_gene_len;
    //cout<<"puzzle:"<<error_puzzle_cost<<" gene:"<<error_gene_len<<" error:"<<error<<endl;
}

/**
 * Method to cross two GAChromosome to create a new gene
 * @param a First GAChromosome
 * @param b Second GAChromosome
 * @return Resulting genes
 */
vector<GAChromosome> GAChromosome::cross_over(GAChromosome a, GAChromosome b) {
    if (b.gene.getSize() > a.gene.getSize()){
        return GAChromosome::cross_over (b, a);
    }
    /**cout<<"a ";
    for (int i = 0; i < a.gene.size(); ++i) {
        cout<<a.gene.at(i)<<" ";
    }cout<<endl;
    cout<<"b ";
    for (int i = 0; i < b.gene.size(); ++i) {
        cout<<b.gene.at(i)<<" ";
    }cout<<endl;**/

    List<string> genA = {};
    List<string> genB = {};

    int sizeA = a.gene.getSize();
    int sizeB = b.gene.getSize();

    for (int i = 0; i < sizeB; i++){

        if (rand()%100 < 10){

            genA.insertLast(a.gene.find(i)->getValue());
            genB.insertLast(b.gene.find(i)->getValue());
            //cout<<"if "<<genA.size()<<" "<<genB.size()<<endl;
        }
        else{
            genA.insertLast(b.gene.find(i)->getValue());
            genB.insertLast(a.gene.find(i)->getValue());
            //cout<<"else "<<genA.size()<<" "<<genB.size()<<endl;
        }
    }
    if (sizeB != sizeA){
        for (int i = 0; i < (sizeA-sizeB); i++){
            genA.insertLast(a.gene.find(sizeB+i)->getValue());
        }
    }

    vector<GAChromosome> ret = {};
    ret.push_back(GAChromosome(b.puzzle, genA));
    ret.push_back(GAChromosome(a.puzzle, genB));
    return ret;
}

/**
 * Function to mutate an individual's gene
 */
void GAChromosome::mutate() {
    float add_vs_mutate_chance = 0.5;
    if(gene.isEmpty()){
        add_vs_mutate_chance = 1.0;
    }
    float rnd = rand()%10;
    rnd /= 10;
    if (rnd <= add_vs_mutate_chance){
        int index = rand()%4;
        gene.insertLast(moves.at(index));

    }
    else{
        int index = rand()%4;
        if (gene.getSize()==0){gene.insertLast(moves.at(index));}
        else{
            gene.insertLast(moves.at(index));
        }

    }
}


