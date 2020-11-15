#include "dijkstra.h"

int Dijkstra::getCharge() const
{
    return Charge;
}

void Dijkstra::setCharge(int value)
{
    Charge = value;
}

string Dijkstra::getPreNode() const
{
    return PreNode;
}

void Dijkstra::setPreNode(string value)
{
    PreNode = value;
}

bool Dijkstra::getVisited() const
{
    return Visited;
}

void Dijkstra::setVisited(bool value)
{
    Visited = value;
}

Dijkstra::Dijkstra()
{

}

Dijkstra::Dijkstra(int charge, string preNode)
{
    Charge = charge;
    PreNode = preNode;
    Visited = false;
}

Dijkstra::Dijkstra(int charge, string preNode, bool visited)
{
    Charge = charge;
    PreNode = preNode;
    Visited = visited;
}
