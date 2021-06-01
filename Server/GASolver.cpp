//
// Created by ingrid on 5/27/21.
//

#include <iostream>
#include <random>
#include "GASolver.h"
#include<stdlib.h>
#include "tinyxml2.h"
#include <filesystem>

/**
 * Constructor of the Puzzle solver
 * @param ex_board Pad of the puzzle
 * @param POPULATION_LEN Population initial
 * @param MUTATION_CHANCE The chance to a chromosome go to mutate
 * @param CROSS_OVER_RATE Percentage of the population go to cross
 * @param best The best Chromosome so far
 */
namespace fs = std::filesystem;

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
 * Auxiliar method of select_best for selection a random position in the population
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
 *Function to determinate if a individual go to mutate
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

/**
 * Method to search the solution
 * @param max_iter Number of maximum iterations
 * @param optimal_error 
 * @return
 */
GAChromosome GASolver::solve(int max_iter, float optimal_error) {

    init_population();
    int iteration = 0;
    string result ="";
    fs::remove_all("/home/usuario/Proyectos/Lets-play/Server/xml");
    fs::create_directories("/home/usuario/Proyectos/Lets-play/Server/xml");
    while (iteration < max_iter && (isbest == 0 ||
                                    best.error_puzzle_cost > optimal_error)){
        cross_over(true);

        calculate_error();
        select_best();
        mutate();
        //display(iteration);
        XML(iteration);

        iteration += 1;
        //string tmp = usrPath(best);



        for (int i = 0; i < best.gene.getSize(); ++i) {
            if (i == best.gene.getSize() -1){
                result = result + best.gene.find(i)->getValue();
            } else{
                result = result + best.gene.find(i)->getValue() + "@";
            }
        }
        append(result);
        result = "";
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

string GASolver::usrPath(GAChromosome path_)
{
    string result ="";
    for (int i = 0; i < path_.gene.getSize(); ++i) {
        if (i == path_.gene.getSize() -1){
            result = result + path_.gene.find(i)->getValue();
        } else {
            result = result + path_.gene.find(i)->getValue() + "@";
        }
    }
}

void GASolver::append(string result) {
    resultPath = resultPath + result + "#";
}

const string &GASolver::getResultPath() const {
    return resultPath;
}

void GASolver::setResultPath(const string &resultPath) {
    GASolver::resultPath = resultPath;
}


void GASolver::XML(int iteration) {
    string g = "Generation" + to_string(iteration +1); const char * generation = g.c_str();

    string ps = to_string(population.size()); const char * population_size = ps.c_str();

    string te = to_string(error); const char * total_error = te.c_str();

    string be = to_string(best.error); const char * best_error = be.c_str();

    string bep = to_string(best.error_puzzle_cost); const char * best_error_puzzle = bep.c_str();

    string beg = to_string(best.error_gene_len); const char * best_error_gen = beg.c_str();

    string bgs = to_string(best.gene.getSize()); const char * best_gen_size = bgs.c_str();

    string bg=" ";
    for (int i = 0; i < best.gene.getSize(); i++) { bg += best.gene.find(i)->getValue()+" ";}
    const char * best_gen = bg.c_str();

    tinyxml2::XMLDocument doc;

    doc.LinkEndChild(doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\""));
    doc.LinkEndChild(doc.NewComment("Description of Generation"));
    auto htmlElement = doc.NewElement(generation);
    auto headElement1 = doc.NewElement("Population_lenght");
    headElement1->SetText(population_size);
    auto headElement2 = doc.NewElement("Total_error");
    headElement2->SetText(total_error);
    auto bodyElement = doc.NewElement("Best");
    htmlElement->LinkEndChild(headElement1);
    htmlElement->LinkEndChild(headElement2);
    htmlElement->LinkEndChild(bodyElement);

    auto pElement1 = doc.NewElement("Best_error_total");
    pElement1->SetText(best_error);
    bodyElement->LinkEndChild(pElement1);
    auto pElement2 = doc.NewElement("Best_error_puzzle");
    pElement2->SetText(best_error_puzzle);
    bodyElement->LinkEndChild(pElement2);
    auto pElement3 = doc.NewElement("Best_error_gen");
    pElement3->SetText(best_error_gen);
    bodyElement->LinkEndChild(pElement3);
    auto pElement4 = doc.NewElement("Best_gen_lenght");
    pElement4->SetText(best_gen_size);
    bodyElement->LinkEndChild(pElement4);
    auto pElement5 = doc.NewElement("Best_gen");
    pElement5->SetText(best_gen);
    bodyElement->LinkEndChild(pElement5);

    doc.LinkEndChild(htmlElement);
    tinyxml2::XMLPrinter printer;
    doc.Print(&printer);
    cout<< printer.CStr() << endl;

    string dn = "/home/usuario/Proyectos/Lets-play/Server/xml/Generation"+ to_string(iteration +1)+".xml"; const char * document_name = dn.c_str();
    doc.SaveFile(document_name);
}





