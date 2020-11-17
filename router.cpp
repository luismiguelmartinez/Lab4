#include "router.h"


void Router::addNode(string node, int value)
{
    RoutingTable[node] = value;
}

void Router::removeNode(string node)
{
    RoutingTable.erase(node);
}

map<string, int> *Router::getRouteTableAddress()
{
    return &RoutingTable;
}

void Router::setWeightNode(string *id, int *weight)
{
    RoutingTable[*id] = *weight;
}

Router::Router()
{

}

Router::Router(map<string, int> table)
{
    RoutingTable = table;
}
