#include "network.h"


map<string, Router> Network::getRouters() const
{
    return Routers;
}

void Network::getOptimalRoute(string origin, string destination, int *weight, string *route)
{
    map <string, Router>::iterator it1;

    map <string, int> routeTable;
    map <string, int>::iterator it2;

    map <string, Dijkstra> stepA, stepB;

    for (unsigned i = 0; i < Routers.size(); i++) {

        if (i == 0) {

            routeTable = Routers[origin].getRouteTable();

            for (it2 = routeTable.begin(); it2 != routeTable.end(); it2++) {

                if (it2->first == origin){
                    stepA[it2->first] = Dijkstra(it2->second, origin, true);
                } else
                    stepA[it2->first] = Dijkstra(it2->second, origin);
            }

        } else {

            map <string, Dijkstra>::iterator it;

            string def_tag = findMinValue(&stepA);
            stepA[def_tag].setVisited(true);

            routeTable = Routers[def_tag].getRouteTable();

            for (it = stepA.begin(); it != stepA.end(); it++) {

                if (!it->second.getVisited()) {

                    // extrayendo el peso de la etiqueta anterior, si es mayor a cero se hacen los calculos respectivos
                    //si aparece un numero negativo significa que aun no hay una ruta hacia ese router
                    if (it->second.getCharge() > 0) {

                        //Se debe verificar que haya coneccion entre los dos nodos para esto en la tabla de ruteo el
                        //valor debe ser mayor a cero
                        if (routeTable[it->first] > 0) {

                            int weight = stepA[def_tag].getCharge() + routeTable[it->first];

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

                        if (routeTable[it->first] < 0) {

                            stepB[it->first] = stepA[it->first];
                        } else {

                            int weight = stepA[def_tag].getCharge() + routeTable[it->first];
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

        routeTable.clear();
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

    map <string, int> routeTable;
    map <string, int>::iterator it2;

    map <string, Dijkstra> stepA, stepB;

    for (unsigned i = 0; i < Routers.size(); i++) {

        if (i == 0) {

            routeTable = Routers[id].getRouteTable();

            for (it2 = routeTable.begin(); it2 != routeTable.end(); it2++) {

                if (it2->first == id){
                    stepA[it2->first] = Dijkstra(it2->second, id, true);
                } else
                    stepA[it2->first] = Dijkstra(it2->second, id);
            }

        } else {

            map <string, Dijkstra>::iterator it;

            string def_tag = findMinValue(&stepA);
            stepA[def_tag].setVisited(true);

            routeTable = Routers[def_tag].getRouteTable();

            for (it = stepA.begin(); it != stepA.end(); it++) {

                if (!it->second.getVisited()) {

                    // extrayendo el peso de la etiqueta anterior, si es mayor a cero se hacen los calculos respectivos
                    //si aparece un numero negativo significa que aun no hay una ruta hacia ese router
                    if (it->second.getCharge() > 0) {

                        //Se debe verificar que haya coneccion entre los dos nodos para esto en la tabla de ruteo el
                        //valor debe ser mayor a cero
                        if (routeTable[it->first] > 0) {

                            int weight = stepA[def_tag].getCharge() + routeTable[it->first];

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

                        if (routeTable[it->first] < 0) {

                            stepB[it->first] = stepA[it->first];
                        } else {

                            int weight = stepA[def_tag].getCharge() + routeTable[it->first];
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

        routeTable.clear();
    }

    map <string, int> optimalRouteTable;
    map <string, Dijkstra>::iterator it;

    for (it = stepA.begin(); it != stepA.end(); it++)
        optimalRouteTable[it->first] = it->second.getCharge();

    return optimalRouteTable;
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

    //si no se encontro algun valor como minimo significa que el
    //router no esta conectado a ningun otro
    //TODO: "no se tiene control cuando un nodo no esta conectado a los demas";
    if (aux == -1) {
        node = weightTable->begin()->first;
        return node;
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

bool Network::routerIdAvailable(string id)
{
    map <string, Router>::iterator it;

    for (it = Routers.begin(); it != Routers.end(); it++) {

        if (it->first == id)
            return false;
    }

    return true;
}
