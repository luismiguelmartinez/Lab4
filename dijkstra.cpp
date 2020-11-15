#include "dijkstra.h"

int Dijkstra::getCharge() const
{
    return Charge;
}

void Dijkstra::setCharge(int value)
{
    Charge = value;
}

char Dijkstra::getPreNode() const
{
    return PreNode;
}

void Dijkstra::setPreNode(char value)
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

Dijkstra::Dijkstra(int charge, char preNode)
{
    Charge = charge;
    PreNode = preNode;
    Visited = false;
}

Dijkstra::Dijkstra(int charge, char preNode, bool visited)
{
    Charge = charge;
    PreNode = preNode;
    Visited = visited;
}
