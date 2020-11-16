#include "router.h"


void Router::addNode(string node, int value)
{
    RouteTable[node] = value;
}

void Router::removeNode(string node)
{
    map <string, int>::iterator it;

    for (it = RouteTable.begin(); it != RouteTable.end(); it++) {

        if (it->first == node) {
            RouteTable.erase(it);
            break;
        }
    }
}

map<string, int> *Router::getRouteTableAddress()
{
    return &RouteTable;
}

string Router::getID() const
{
    return ID;
}

void Router::setID(const string &value)
{
    ID = value;
}

Router::Router()
{

}

Router::Router(map<string, int> table)
{
    RouteTable = table;
}

Router::Router(string id, map<string, int> table)
{
    ID = id;
    RouteTable = table;
}
