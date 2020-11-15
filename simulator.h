#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <fstream>
#include <network.h>

class Simulator
{
private:
    Network network;

    void createNetwork();
    void loadNetwork();
    Router dataToRouter (string data);
    void menu();

public:
    Simulator();
    void start();
};

#endif // SIMULATOR_H
