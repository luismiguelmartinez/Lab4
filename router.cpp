#include "router.h"

char Router::getId() const
{
    return ID;
}

void Router::setId(char id)
{
    ID = id;
}

void Router::addNode(char node, int value)
{
    RouteTable[node] = value;
}

void Router::removeNode(char node)
{
    map <char, int>::iterator it;

    for (it = RouteTable.begin(); it != RouteTable.end(); it++) {

        if (it->first == node) {
            RouteTable.erase(it);
            break;
        }
    }
}

map<char, int> Router::getRouteTable() const
{
    return RouteTable;
}

Router::Router()
{

}

Router::Router(char id)
{
    ID = id;
}

Router::Router(map<char, int> table)
{
    RouteTable = table;
}

Router::Router(char id, map<char, int> table)
{
    ID = id;
    RouteTable = table;
}
