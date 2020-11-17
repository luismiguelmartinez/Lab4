#include "simulator.h"

void Simulator::createNetwork()
{
    menu();
}

void Simulator::loadNetwork()
{
    try {
        cout << endl << "Ingrese el nombre del archivo de texto: ";

        string file;
        cin >> file;

        ifstream fin;
        fin.open(file);
        if (!fin.is_open())
            throw '1';

        string id;
        map <string, int> routingTable;

        fin.seekg(0);
        for (string data; getline(fin, data); ) {

            dataToRouter(data, &id, &routingTable);
            network.addRouter(id, routingTable);
            routingTable.clear();
            id.clear();
        }

        fin.close();

    }  catch (char c) {
        if (c == '1') {
            cout << " ------> Error archivo de lectura, verifique que el nombre este correcto" << endl;
            start();
        }
        else
            cout << "Error inesperado" << endl;
    }

    if (network.getRoutersAddress()->size() == 0) {

        cout << endl << "No existen datos de una red en el archivo" << endl;
        start();
    } else if (network.getRoutersAddress()->size() == 1) {

        cout << "Cantidad de routers actuales: " << network.getRoutersAddress()->size() << endl;
        menu();
    } else
        menu();
}

void Simulator::dataToRouter(string data, string *id, map <string, int> *routingTable)
{
    bool extractData = true;
    string aux1, aux2;


    for (unsigned i = 0; data.length(); i++) {

        if (data.substr(i, 1) != " ")
            *id += data.substr(i, 1);
        else {
            data = data.substr(++i);
            break;
        }
    }


    while (extractData) {

        for (unsigned i = 0; i < data.length(); i++) {

            if (data.substr(i, 1) != ";")
                aux1 += data.substr(i, 1);
            else {
                data = data.substr(++i);
                break;
            }
        }

        for (unsigned i = 0; i < data.length(); i++) {

            if (data.substr(i, 1) != " ")
                aux2 += data.substr(i, 1);
            else {
                if(data.length() > 1)
                    data = data.substr(++i);

                break;
            }
        }


        if (aux2 == "x" )
            routingTable->insert(pair <string, int> (aux1, -1));
        else
            routingTable->insert(pair <string, int> (aux1, atoi(aux2.c_str())));

        for (unsigned i = 0; i < data.length(); i++) {

            if (data.substr(i, 1) == ";") {
                extractData = true;
                break;
            } else
                extractData = false;
        }

        if (data.length() == 0)
            break;

        aux1.clear();
        aux2.clear();
    }
}

void Simulator::menu()
{
    while (true) {

        char option;
        cout << endl << " >>>  Ingrese una opcion  <<< " << endl;

        cout << endl;
        cout << "a) Agregar router" << endl;
        cout << "b) Remover router" << endl;
        cout << "c) Visualizar tablas de red" << endl;
        cout << "d) Ruta optima para enviar un paquete" << endl;
        cout << "e) Volver al menu principal" << endl;
        cout << endl;
        cout << "Opcion: ";

        cin >> option;

        switch(option) {

        case 'a':
        {
            string id;
            cout << "Ingrese ID de router a agregar: ";
            cin >> id;

            if (network.routerIdAvailable(id)) {

                if (network.getRoutersAddress()->size() > 1)
                    cout << endl << endl << "Ingrese peso para el enlace entre routers"
                                            "\nsi no se conectan o no directamente ingrese x " << endl << endl;
                else
                    cout << endl << "Se debe ingresar mas routers para empezar a agregar costos entre enlaces" << endl;


                map <string, Router> *routers = network.getRoutersAddress();
                map <string, Router>::iterator it;
                map <string, int> routeTable;
                string value;

                routeTable[id] = 0;

                for (it = routers->begin(); it != routers->end(); it++) {

                    if (it->first != id) {

                        cout << id << "->" << it->first << " ";
                        cin >> value;

                        if (value == "x")
                            routeTable[it->first] = -1;
                        else
                            routeTable[it->first] = atoi(value.c_str());
                    }
                }

                network.addRouter(id, Router(routeTable));

                cout << endl << " **/ Router agregado con exito /** " << endl;

            } else
                cout << endl << "El ID ingresado ya se encuentra asignado" << endl;
        }
            break;

        case 'b':
        {
            checkRoutersQuantity();

            string id;
            cout << "Ingrese ID de router a remover: ";
            cin >> id;

            if (!network.routerIdAvailable(id)) {

                network.removeRouter(id);
                cout << endl << "Router removido con exito" << endl;

            } else
                cout << endl << "El ID ingresado no existe en la red" << endl;
        }
            break;

        case 'c':
        {
            checkRoutersQuantity();

            string id;
            cout << "Ingrese ID del router para el cual desea visualizar la tabla: ";
            cin >> id;

            if (!network.routerIdAvailable(id)) {

                map <string, int>::iterator it;
                map <string, int> *routingTable = (network.getRoutersAddress()->at(id)).getRouteTableAddress();

                cout << endl << "Tabla para router " << id << endl << endl;

                for (it = routingTable->begin(); it != routingTable->end(); it++) {

                    if (it->second >= 0)
                        cout << id << "->" << it->first << " " << it->second << endl;
                    else
                        cout << id << "->" << it->first << " x" << endl;
                }

                cout << endl << endl << "Tabla optimizada para router " << id << endl << endl;

                map <string, int> optimalRoutingTable = network.getOptimalRouteTable(id);

                for (it = optimalRoutingTable.begin(); it != optimalRoutingTable.end(); it++) {

                    if (it->second >= 0)
                        cout << id << "->" << it->first << " " << it->second << endl;
                    else
                        cout << id << "->" << it->first << " x" << endl;
                }
            } else
                cout << endl << "El ID de router ingresado no existe en la red" << endl;
        }
            break;

        case 'd':
        {
            checkRoutersQuantity();

            string origin, route;
            int weight;

            cout << "Ingrese ID de origen: ";
            cin >> origin;

            if (!network.routerIdAvailable(origin)) {

                string destination;
                cout << "Ingrese ID de destino: ";
                cin >> destination;

                if (!network.routerIdAvailable(destination)) {

                    network.getOptimalRoute(origin, destination, &weight, &route);

                    cout << endl << "Ruta optima: " << route << endl;
                    cout << "Costo: " << weight << endl;


                } else
                    cout << endl << "El ID " << destination << " no existe en la red" << endl;

            } else
                cout << endl << "El ID " << origin << " no existe en la red" << endl;
        }
            break;

        case 'e':
        {
            network.getRoutersAddress()->clear();
            start();
        }
            break;

        default:
            cout << "Opcion no valida" << endl;
        }
    }
}

void Simulator::checkRoutersQuantity()
{
    if (network.getRoutersAddress()->size() == 0) {

        cout << endl << "No hay routers en la red" << endl;
        cout << "Cantidad de routers actuales: " << network.getRoutersAddress()->size() << endl;
        menu();
    } else if (network.getRoutersAddress()->size() == 1) {

        cout << endl << "Debe de existir mas de un router en la red" << endl;
        cout << "Cantidad de routers actuales: " << network.getRoutersAddress()->size() << endl;
        menu();
    }
}

Simulator::Simulator()
{
    //Constructor de la clase
}

void Simulator::start()
{
    string option;

    cout<<endl;
    cout<<"||||||||||||||||||||||||||||||||||||||||||"<<endl;
    cout<<"|||                                    |||"<<endl;
    cout<<"|||            BIENVENIDO AL           |||"<<endl;
    cout<<"|||        SIMULADOR DE ROUTERS        |||"<<endl;
    cout<<"|||                                    |||"<<endl;
    cout<<"|||    a) Crear red desde cero         |||"<<endl;
    cout<<"|||    b) Cargar red desde un archivo  |||"<<endl;
    cout<<"|||                                    |||"<<endl;
    cout<<"|||          Salir presione *          |||"<<endl;
    cout<<"|||                                    |||"<<endl;
    cout<<"||||||||||||||||||||||||||||||||||||||||||"<<endl;
    cout<<endl;
    cout<<"Opcion: ";

    cin >> option;

    if (option.compare("*"))  {

        if (option == "a")
            createNetwork();
        else if (option == "b")
            loadNetwork();
        else {
            cout<<"Opcion no valida"<<endl;
            start();
        }
    }
}
