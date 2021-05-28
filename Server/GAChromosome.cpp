//
// Created by ingrid on 5/27/21.
//

#include "GAChromosome.h"
#include <iostream>
#include<stdlib.h>
#include <iomanip>


GAChromosome::GAChromosome(GAPad ex_board, vector<string> gen) {

    moves.emplace_back("up");
    moves.emplace_back("down");
    moves.emplace_back("left");
    moves.emplace_back("right");

    gene = gen;

    if (gene.size() == 0) {
        int a = rand() % 4;
        gene.push_back(moves.at(a));
    }

    error = NULL;
    error_puzzle_cost = 0;
    error_gene_len = NULL;
    puzzle = ex_board;
    update_error();
}

void GAChromosome::update_error() {
    GAPad temp = puzzle;
    temp.apply_chain(gene);

    error_puzzle_cost = temp.cost();
    error_gene_len = gene.size() * 0.01;
    error = error_puzzle_cost + error_gene_len;
    //cout<<"puzzle:"<<error_puzzle_cost<<" gene:"<<error_gene_len<<" error:"<<error<<endl;
}

vector<GAChromosome> GAChromosome::cross_over(GAChromosome a, GAChromosome b) {
    if (b.gene.size() > a.gene.size()){
        return GAChromosome::cross_over (b, a);
    }

    vector<string> genA = {};
    vector<string> genB = {};

    int sizeA = a.gene.size();
    int sizeB = b.gene.size();

    for (int i = 0; i < sizeB; i++){

        if (rand()%100 < 10){

            genA.push_back(a.gene.at(i));
            genB.push_back(b.gene.at(i));
            //cout<<"if "<<genA.size()<<" "<<genB.size()<<endl;
        }
        else{
            genA.push_back(b.gene.at(i));
            genB.push_back(a.gene.at(i));
            //cout<<"else "<<genA.size()<<" "<<genB.size()<<endl;
        }
    }
    if (sizeB != sizeA){
        for (int i = 0; i < (sizeA-sizeB); i++){
            genA.push_back(a.gene.at(sizeB+i));
        }
    }

    vector<GAChromosome> ret = {};
    ret.push_back(GAChromosome(b.puzzle, genA));
    ret.push_back(GAChromosome(a.puzzle, genB));
    return ret;
}

void GAChromosome::mutate() {
    float add_vs_mutate_chance = 0.5;
    if(gene.empty()){
        add_vs_mutate_chance = 1.0;
    }
    float rnd = rand()%10;
    rnd /= 10;
    if (rnd <= add_vs_mutate_chance){
        int index = rand()%4;
        gene.push_back(moves.at(index));

    }
    else{
        int index = rand()%4;
        if (gene.size()==0){gene.push_back(moves.at(index));}
        else{
            gene.pop_back();
            gene.push_back(moves.at(index));
        }

    }
}