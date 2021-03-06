#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <string>

using namespace std;

class Dijkstra
{
    int Charge;
    string PreNode;
    bool Visited;

public:
    Dijkstra();
    Dijkstra(int charge, string preNode);
    Dijkstra(int charge, string preNode, bool visited);
    int getCharge() const;
    void setCharge(int value);
    string getPreNode() const;
    void setPreNode(string value);
    bool getVisited() const;
    void setVisited(bool value);
};

#endif // DIJKSTRA_H
