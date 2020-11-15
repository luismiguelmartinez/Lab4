#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <string>



class Dijkstra
{
    int Charge;
    char PreNode;
    std::string route;
    bool Visited;

public:
    Dijkstra();
    Dijkstra(int charge, char preNode);
    Dijkstra(int charge, char preNode, bool visited);
    int getCharge() const;
    void setCharge(int value);
    char getPreNode() const;
    void setPreNode(char value);
    bool getVisited() const;
    void setVisited(bool value);
};

#endif // DIJKSTRA_H
