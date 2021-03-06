#include "network.h"


map<string, Router> *Network::getRoutersAddress()
{
    return &Routers;
}

void Network::getOptimalRoute(string origin, string destination, int *weight, string *route)
{
    map <string, Router>::iterator it1;

    map <string, int> *routeTable;
    map <string, int>::iterator it2;

    map <string, Dijkstra> stepA, stepB;

    for (unsigned i = 0; i < Routers.size(); i++) {

        if (i == 0) {

            routeTable = Routers[origin].getRouteTableAddress();

            for (it2 = routeTable->begin(); it2 != routeTable->end(); it2++) {

                if (it2->first == origin){
                    stepA[it2->first] = Dijkstra(it2->second, origin, true);
                } else
                    stepA[it2->first] = Dijkstra(it2->second, origin);
            }

        } else {

            map <string, Dijkstra>::iterator it;

            string def_tag = findMinValue(&stepA);
            stepA[def_tag].setVisited(true);

            routeTable = Routers[def_tag].getRouteTableAddress();

            for (it = stepA.begin(); it != stepA.end(); it++) {

                if (!it->second.getVisited()) {

                    // extrayendo el peso de la etiqueta anterior, si es mayor a cero se hacen los calculos respectivos
                    //si aparece un numero negativo significa que aun no hay una ruta hacia ese router
                    if (it->second.getCharge() > 0) {

                        // Se debe verificar que haya coneccion entre los dos nodos, para esto se debe ver en la tabla
                        // de ruteo el valor que viene, y este debe ser diferente de -1
                        if (routeTable->at(it->first) > 0) {

                            int weight = stepA[def_tag].getCharge() + routeTable->at(it->first);

                            // Si la eqtiqueta calculada actual es menor o igual que la anterior se reemplaza
                            //si no se sigue con la que se tenia
                            if (weight <= stepA[it->first].getCharge()) {

                                stepB[it->first] = Dijkstra(weight, def_tag);
                            } else {

                                stepB[it->first] = stepA[it->first];
                            }

                        } else
                            stepB[it->first] = stepA[it->first];

                    } else {

                        //si la etiqueta anterior es menor a cero, se verifica el valor de la siguiente si es mayor a cero
                        //se calcula el peso y se llevan los repectivos datos al sigiente paso o si es menor que cero se
                        //sigue con el mismo valor menor a cero para aclarar que aun no hay una ruta hacia ese nodo

                        if (routeTable->at(it->first) < 0) {

                            stepB[it->first] = stepA[it->first];
                        } else {

                            int weight = stepA[def_tag].getCharge() + routeTable->at(it->first);
                            stepB[it->first] = Dijkstra(weight, def_tag);
                        }
                    }

                } else {

                    //Si la etiqueta es definitiva o ya ha sido visitada pasa directamente al siguiente paso
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

    while (aux.substr(aux.length() - 1) != origin)
        aux += stepA[aux.substr(aux.length() - 1)].getPreNode();

    for (unsigned i = 1; i <= aux.length(); i++)
        *route += aux[aux.length() - i];
}

map<string, int> Network::getOptimalRouteTable(string id)
{
    map <string, Router>::iterator it1;

    map <string, int> *routeTable;
    map <string, int>::iterator it2;

    map <string, Dijkstra> stepA, stepB;

    for (unsigned i = 0; i < Routers.size(); i++) {

        if (i == 0) {

            unsigned aux = 0;

            routeTable = Routers[id].getRouteTableAddress();

            for (it2 = routeTable->begin(); it2 != routeTable->end(); it2++) {

                if (it2->first == id){
                    stepA[it2->first] = Dijkstra(it2->second, id, true);
                } else
                    stepA[it2->first] = Dijkstra(it2->second, id);

                if(it2->second == -1)
                    aux++;
            }

            // Si en la taba de cos
            if (aux == (Routers.size() - 1))
                return *routeTable;

        } else {

            map <string, Dijkstra>::iterator it;

            string def_tag = findMinValue(&stepA);

            stepA[def_tag].setVisited(true);

            routeTable = Routers[def_tag].getRouteTableAddress();

            for (it = stepA.begin(); it != stepA.end(); it++) {

                if (!it->second.getVisited()) {

                    // extrayendo el peso de la etiqueta anterior, si es mayor a cero se hacen los calculos respectivos
                    //si aparece un numero negativo significa que aun no hay una ruta hacia ese router
                    if (it->second.getCharge() > 0) {

                        // Se debe verificar que haya coneccion entre los dos nodos, para esto se debe ver en la tabla
                        // de ruteo el valor que viene, y este debe ser diferente de -1
                        if (routeTable->at(it->first) > 0) {

                            int weight = stepA[def_tag].getCharge() + routeTable->at(it->first);

                            // Si la eqtiqueta calculada actual es menor o igual que la anterior se reemplaza
                            //si no se sigue con la que se tenia
                            if (weight <= stepA[it->first].getCharge()) {

                                stepB[it->first] = Dijkstra(weight, def_tag);
                            } else {

                                stepB[it->first] = stepA[it->first];
                            }

                        } else
                            stepB[it->first] = stepA[it->first];

                    } else {

                        //si la etiqueta anterior es menor a cero, se verifica el valor de la siguiente si es mayor a cero
                        //se calcula el peso y se llevan los repectivos datos al sigiente paso o si es menor que cero se
                        //sigue con el mismo valor menor a cero para aclarar que aun no hay una ruta hacia ese nodo

                        if (routeTable->at(it->first) < 0) {

                            stepB[it->first] = stepA[it->first];
                        } else {

                            int weight = stepA[def_tag].getCharge() + routeTable->at(it->first);
                            stepB[it->first] = Dijkstra(weight, def_tag);
                        }
                    }

                } else {

                    //Si la etiqueta es definitiva o ya ha sido visitada pasa directamente al siguiente paso
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

    map <string, int> optimalRouteTable;
    map <string, Dijkstra>::iterator it;

    for (it = stepA.begin(); it != stepA.end(); it++)
        optimalRouteTable[it->first] = it->second.getCharge();

    return optimalRouteTable;
}

void Network::setLinkCost(string *origin, string *destination, int weight)
{
    Routers[*origin].setWeightNode(destination, &weight);
    Routers[*destination].setWeightNode(origin, &weight);
}

string Network::findMinValue(map<string, Dijkstra> *weightTable)
{
    int aux = -1;
    string node;
    map <string, Dijkstra>::iterator it;

    for (it = weightTable->begin(); it != weightTable->end(); it++) {

        if (!it->second.getVisited() && (it->second.getCharge() > 0)) {
            aux = it->second.getCharge();
            node = it->first;
            break;
        }
    }

    if (aux == -1) {
        return weightTable->begin()->first;
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

    //Se actualiza la tabla de cada router agregandole a todos ellos el nuevo ID y costo hacia este
    for (it = Routers.begin(); it != Routers.end(); it++)
        it->second.addNode(id, router.getRouteTableAddress()->at(it->first));

    //se agrega el nuevo router con su respectiva tabla
    Routers[id] = router;
}

void Network::removeRouter(string id)
{
    // Se elimina el router con la clave con la cual fue almacenado
    Routers.erase(id);

    // Se recorre todos los routers para que en cada uno de ellos se elimine
    map <string, Router>::iterator it;
    for (it = Routers.begin(); it != Routers.end(); it++)
            it->second.removeNode(id);


}

bool Network::routerIdAvailable(string id)
{
    map <string, Router>::iterator it;

    // Funcion que verifica si un ID se encuentra disponible en la red para asignarlo
    // se puede utilizar de manera inversa (!) para sber si un router existe en la red
    for (it = Routers.begin(); it != Routers.end(); it++) {

        if (it->first == id)
            return false;
    }

    return true;
}
