
#ifndef SERVER_GENLOGIC_H
#define SERVER_GENLOGIC_H

#include <string>
#include "Matrix.h"
#include "json.hpp"
#include "divideImage.h"
#include "GAChromosome.h"
#include "GASolver.h"
#include <math.h>

using namespace std;
using json = nlohmann::json;


string geneticResult(int num){

    float MUTATION_CHANCE = 0.9;
    float CROSS_OVER_RATE = 0.3;
    int POPULATION_LEN = 1000;
    int MAX_ITERATION = 100;
    int x,y;
    bool run = false;
    string mixMatrix;

    if(isSquare(num))
    {
        x = y = sqrt(num);
        run = true;
    } else if (num == 8){
        x = 2;
        y = 4;
        run = true;
    }

    if (run){
        try {

            GAPad myPad = GAPad(x, y);

            myPad.shuffle();

            for (auto &item : myPad.board) {
                for (auto &i : item) {
                    mixMatrix += to_string(i) + "-";
                }
                mixMatrix += "/";
            }
            mixMatrix += "&";

            string divString = "&" + to_string(num);

            List<string> gene;
            GAChromosome par = GAChromosome(myPad, gene);
            GASolver gSolver = GASolver(myPad, POPULATION_LEN, MUTATION_CHANCE, CROSS_OVER_RATE, par);
            GAChromosome res = gSolver.solve(MAX_ITERATION, 0.000001);  //hacer esto como un str
            //myPad.apply_chain(res.gene);  //hacer este metodo en c#
            return mixMatrix + gSolver.getResultPath() + divString;
        }

        catch (const std::exception &exc){
            cout<<"Ha ocurrido un error\n";
            std::cerr << exc.what();
        }
    }

}

string genLogic(json jmessageR){

    string key = jmessageR.value("Key", "oops");

    if (key == "Config"){

        string divisionNum =  jmessageR.value("Info1", "oops");
        string imgPath =  jmessageR.value("Info2", "oops");

        std::vector<cv::Mat> blocks;

        // read png image

        cv::Mat image = cv::imread(imgPath, cv::IMREAD_UNCHANGED);
        //cv::imshow("Display window", image);

        int tmp = std::stoi(divisionNum);

        // divide image into multiple blocks
        int divideStatus = divideImage(image, tmp, blocks);

        // debug: save blocks
        cv::utils::fs::createDirectory("/home/ignacio/Datos2/Lets-play/Server/blocksFolder");
        for (int j = 0; j < blocks.size(); j++)
        {
            std::string blockId = std::to_string(j);
            std::string blockImgName = "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + blockId + ".png";
            imwrite(blockImgName, blocks[j]);
        }

        return geneticResult(tmp);
    }

}



#endif //SERVER_GENLOGIC_H
