#include "router.h"


void Router::addNode(string node, int value)
{
    RouteTable[node] = value;
}

void Router::removeNode(string node)
{
    RouteTable.erase(node);
}

map<string, int> *Router::getRouteTableAddress()
{
    return &RouteTable;
}

Router::Router()
{

}

Router::Router(map<string, int> table)
{
    RouteTable = table;
}
