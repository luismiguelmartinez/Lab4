#ifndef NETWORK_H
#define NETWORK_H

#include <router.h>
#include <dijkstra.h>

class Network
{
private:
    map <string, Router> Routers;
    string findMinValue(map <string, Dijkstra> *step);

public:
    Network();
    void addRouter(string id, Router router);
    void removeRouter(string id);
    bool routerAvailable(string id);
    map<string, Router> getRouters() const;
    void optimalRoute(string origin, string destination, int *weight, string *route);
};

#endif // NETWORK_H
