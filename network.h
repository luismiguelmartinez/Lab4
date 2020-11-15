#ifndef NETWORK_H
#define NETWORK_H

#include <router.h>
#include <dijkstra.h>

using namespace std;

class Network
{
private:
    map <char, Router> Routers;
    char findMinValue(map <char, Dijkstra> *step);

public:
    Network();
    void addRouter(char id, Router router);
    void removeRouter(char id);
    bool routerAvailable(char id);
    map<char, Router> getRouters() const;
    void optimalRoute(char origin, char destination, int *weight, string *route);
};

#endif // NETWORK_H
