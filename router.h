#ifndef ROUTER_H
#define ROUTER_H

#include <map>

using namespace std;

class Router
{
    string ID;
    map <string, int> RouteTable;

public:
    Router();
    Router(map <string, int> table);
    Router(string id, map<string, int> table);
    void addNode(string node, int value);
    void removeNode(string node);
    map<string, int> *getRouteTableAddress();
    string getID() const;
    void setID(const string &value);
};

#endif // ROUTER_H
