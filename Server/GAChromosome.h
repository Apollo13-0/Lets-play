//
// Created by ingrid on 5/27/21.
//

#ifndef SERVER_GACHROMOSOME_H
#define SERVER_GACHROMOSOME_H
#include "GAPad.h"
#include "string"
#include "List.h"

//! Class in charge of storing the chromosome information of each individual
class GAChromosome {
public:
    vector<string> moves;

    List<string> gene;
    float error;
    float error_puzzle_cost;
    float error_gene_len;
    GAPad puzzle;



    explicit GAChromosome(GAPad ex_board, List<string> gen);


    void update_error();
    static vector<GAChromosome> cross_over(GAChromosome a, GAChromosome b);
    void mutate();




};
#endif //SERVER_GACHROMOSOME_H
