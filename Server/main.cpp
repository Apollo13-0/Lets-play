#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include "json.hpp"
#include "BPGameLogic.h"
#include "tinyxml2.h"
#include "genLogic.h"

//Prueba
#include <iomanip>
#include <fstream>
#include "GAPad.h"
#include "GASolver.h"

#include "divideImage.h"

float MUTATION_CHANCE = 0.9;
float CROSS_OVER_RATE = 0.3;
int POPULATION_LEN = 1000;
int MAX_ITERATION = 100;
//


using namespace std;
using json = nlohmann::json;;
//using namespace tinyxml2;

int StartListenign(){

    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        cerr << "No se pudo crear el Socket. Cerrando..." << endl;
        return -1;
    }

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(11000);

    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
    bind(listening, (sockaddr*)&hint, sizeof(hint));

    listen(listening, SOMAXCONN);

    while(true){
        sockaddr_in client;
        socklen_t clientSize = sizeof(client);

        int clientSocket = accept(listening, (sockaddr *) &client, &clientSize);

        char host[NI_MAXHOST];      // Nombre del cliente remoto
        char service[NI_MAXSERV];

        memset(host, 0, NI_MAXHOST);
        memset(service, 0, NI_MAXSERV);

        if (getnameinfo((sockaddr *) &client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
            cout << host << " conectado " << endl;
        } else {
            inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
            cout << host << " conectado al puerto " << ntohs(client.sin_port) << endl;
        }
        char buf[4096];
        memset(buf, 0, 4096);

        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == -1) {
            cerr << "Error al recibir mensaje. Cerrando..." << endl;
            break;
        }

        if (bytesReceived == 0) {
            cout << "Cliente desconectado " << endl;
            break;
        }

        string messageR = string(buf, 0, bytesReceived);
        json jmessageR = json::parse(messageR);
        string game = jmessageR.value("Game", "oops");
        if (game == "BP"){
            string message = bpLogic(jmessageR);
            send(clientSocket, message.c_str(), message.size() + 1, 0);
        }

        if (game == "Genetic")
        {
            string message = genLogic(jmessageR);
            send(clientSocket, message.c_str(), message.size() + 1, 0);
        }
        close(clientSocket);
    }

    return 0;
}


int main() {
    srand(time(NULL));
    try {

        GAPad myPad = GAPad(3, 3);
        for (auto &item : myPad.board) {
            for (auto &i : item) {

                cout << setw(3)<< i <<" ; ";
            }
            cout << endl;
        }
        cout << endl;
        myPad.shuffle();
        for (auto &item : myPad.board) {
            for (auto &i : item) {


                cout << setw(3) << i << " - ";
            }
            cout << endl;
        }
        cout << endl;

        List<string> gene;
        GAChromosome par = GAChromosome(myPad, gene);
        GASolver gSolver = GASolver(myPad, POPULATION_LEN, MUTATION_CHANCE, CROSS_OVER_RATE, par);
        GAChromosome res = gSolver.solve(MAX_ITERATION, 0.000001);
        myPad.apply_chain(res.gene);

        for (auto &item : myPad.board) {
            for (auto &i : item) {

                cout << setw(3)<< i << " | ";
            }
            cout << endl;
        }
        cout << endl;


        cout<< "**************************"<< endl;

        cout << gSolver.getResultPath() << endl;
    }


    catch (const std::exception &exc){
        cout<<"Ha ocurrido un error\n";
        std::cerr << exc.what();
    }



//    List<GAChromosome*> prueba;
//    GAPad myPad = GAPad();
//    GAChromosome original = GAChromosome(myPad, {});
//    GAChromosome par = original;
//    GAChromosome* ptrpar= &par;
//    prueba.insertFirst(ptrpar);

//    StartListenign();

//    // init vars
//    const int blockw = 50;
//    const int blockh = 50;
//    std::vector<cv::Mat> blocks;
//
//    // read png image
//
//    cv::Mat image = cv::imread("/home/ignacio/Datos2/Lets-play/Server/perrito.jpg", cv::IMREAD_UNCHANGED);
//    //cv::imshow("Display window", image);
//
//    // divide image into multiple blocks
//    int divideStatus = divideImage(image, 9, blocks);
//
//    // debug: save blocks
//    cv::utils::fs::createDirectory("/home/usuario/Proyectos/Lets-play/Server/blocksFolder");
//    for (int j = 0; j < blocks.size(); j++)
//    {
//        std::string blockId = std::to_string(j);
//        std::string blockImgName = "/home/usuario/Proyectos/Lets-play/Server/blocksFolder/block#" + blockId + ".jpg";
//        imwrite(blockImgName, blocks[j]);
//    }



    return 0;
}

