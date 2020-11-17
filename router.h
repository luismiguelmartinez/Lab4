#ifndef ROUTER_H
#define ROUTER_H

#include <map>

using namespace std;

class Router
{
    map <string, int> RoutingTable;

public:
    Router();
    Router(map <string, int> table);
    void addNode(string node, int value);
    void removeNode(string node);
    map<string, int> *getRouteTableAddress();
    string getID() const;
    void setWeightNode(string *id, int *weight);
};

#endif // ROUTER_H
