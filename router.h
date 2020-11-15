#ifndef ROUTER_H
#define ROUTER_H

#include <map>

using namespace std;

class Router
{
    char ID;
    map <char, int> RouteTable;

public:
    Router();
    Router(char id);
    Router(map <char, int> table);
    Router(char id, map <char, int> table);
    char getId() const;
    void setId(char id);
    void addNode(char node, int value);
    void removeNode(char node);
    map<char, int> getRouteTable() const;
};

#endif // ROUTER_H
