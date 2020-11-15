#include "network.h"


map<string, Router> Network::getRouters() const
{
    return Routers;
}

void Network::optimalRoute(string origin, string destination, int *weight, string *route)
{
    map <string, Router>::iterator router;
    map <string, int>::iterator node;
    map <string, Dijkstra> stepA, stepB;

    for (unsigned i = 0; i < Routers.size(); i++) {

        if (i == 0) {

            for (router = Routers.begin(); router != Routers.end(); router++) {

                if (router->first == origin) {

                    for (node = router->second.getRouteTable().begin(); node != router->second.getRouteTable().end(); node++) {

                        if (node->first == origin){
                            stepA[node->first] = Dijkstra(node->second, origin, true);
                        } else
                            stepA[node->first] = Dijkstra(node->second, origin);
                    }

                    break;
                }
            }
        } else {

            map <string, Dijkstra>::iterator it;

            string lastTag = findMinValue(&stepA);
            stepA[lastTag].setVisited(true);

            for (it = stepA.begin(); it != stepA.end(); it++) {

                if (!it->second.getVisited()) {

                    if (it->second.getCharge() > 0) {

                        int weight = stepA[lastTag].getCharge() + Routers[lastTag].getRouteTable()[it->first];

                        if (weight <= stepA[it->first].getCharge()) {

                            stepB[it->first] = Dijkstra(weight, lastTag);
                        } else {

                            stepB[it->first] = stepA[it->first];
                        }

                    } else {

                        if (stepA[lastTag].getCharge() < 0) {

                            stepB[it->first] = stepA[it->first];
                        } else {

                            int weight = stepA[lastTag].getCharge() + Routers[lastTag].getRouteTable()[it->first];
                            stepB[it->first] = Dijkstra(weight, lastTag);
                        }
                    }

                } else {

                    stepB[it->first] = stepA[it->first];
                }
            }
        }

        if (i != 0) {
            stepA.clear();
            stepA = stepB;
            stepB.clear();
        }
    }

    // Costo de la ruta
    *weight = stepA[destination].getCharge();

    //Ruta optima
    string aux = destination;

    *route = aux;

    while (true) {

        if (aux == origin) {

            *route += stepA[aux].getPreNode();
            break;
        } else {

            *route += stepA[aux].getPreNode();
            aux = stepA[aux].getPreNode();
        }
    }
}

string Network::findMinValue(map<string, Dijkstra> *weightTable)
{
    int aux;
    string node;
    map <string, Dijkstra>::iterator it;

    for (it = weightTable->begin(); it != weightTable->end(); it++) {

        if (!it->second.getVisited() && (it->second.getCharge() > 0)) {
            aux = it->second.getCharge();
            node = it->first;
            break;
        }
    }

    for (it = weightTable->begin(); it != weightTable->end(); it++) {

        if (!it->second.getVisited() && (it->second.getCharge() < aux) && (it->second.getCharge() > 0)) {
            aux = it->second.getCharge();
            node = it->first;
        }
    }

    return node;
}

Network::Network()
{

}

void Network::addRouter(string id, Router router)
{
    map <string, Router>::iterator it;

    for (it = Routers.begin(); it != Routers.end(); it++)
        it->second.addNode(id, router.getRouteTable()[it->first]);

    Routers[id] = router;
}

void Network::removeRouter(string id)
{
    map <string, Router>::iterator it;

    for (it = Routers.begin(); it != Routers.end(); it++) {

        if (it->first == id)
            Routers.erase(it);
        else
           it->second.removeNode(id);
    }
}

bool Network::routerAvailable(string id)
{
    map <string, Router>::iterator it;

    for (it = Routers.begin(); it != Routers.end(); it++) {

        if (it->first == id)
            return false;
    }

    return true;
}
