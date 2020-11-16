#include "simulator.h"

void Simulator::createNetwork()
{

}

void Simulator::loadNetwork()
{
    try {
        cout << endl << "Ingrese el nombre del archivo de texto: ";

        string file;
        cin >> file;

        ifstream fin;
        fin.open(file + ".txt");
        if (!fin.is_open())
            throw '1';

        fin.seekg(0);
        for (string line; getline(fin, line); ) {

            Router router = dataToRouter(line);

            network.addRouter(router.getID(), router);
        }

        fin.close();

    }  catch (char c) {
        if (c == '1') {
            cout << "Error archivo de lectura" << endl;
            start();
        }
        else
            cout << "Error inesperado" << endl;
    }


    if(network.getRouters().size() > 1) {

        menu();
    } else {
        cout << "No se encontraron datos de una red en el archivo" << endl;
    }
}

Router Simulator::dataToRouter(string data)
{
    map <string, int> routeTable;
    bool lastNode;
    string aux1, aux2, temp;


    for (unsigned i = 0; data.length(); i++) {

        if (data.substr(i, 1) != " ")
            temp += data.substr(i, 1);
        else {
            data = data.substr(++i);
            break;
        }
    }


    while (true) {

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
            routeTable[aux1] = -1;
        else
            routeTable[aux1] = atoi(aux2.c_str());

        for (unsigned i = 0; i < data.length(); i++) {

            if (data.substr(i, 1) == ";") {
                lastNode = false;
                break;
            } else
                lastNode = true;
        }

        if (lastNode)
            break;

        aux1.clear();
        aux2.clear();
    }

    return Router(temp, routeTable);

}

void Simulator::menu()
{
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

            cout << endl << endl << "Ingrese peso para el enlace entre routers\nsi no se conectan o no directamente ingrese x " << endl << endl;

            map <string, Router> routers = network.getRouters();
            map <string, Router>::iterator it;
            map <string, int> routeTable;
            string value;

            routeTable[id] = 0;

            for (it = routers.begin(); it != routers.end(); it++) {

                if (it->first != id) {

                    cout << id << "->" << it->first << " ";
                    cin >> value;

                    if (value == "x")
                        routeTable[it->first] = -1;
                    else
                        routeTable[it->first] = atoi(value.c_str());
                }
            }

            network.addRouter(id, Router(id, routeTable));

            cout << endl << "Router agregado con exito" << endl;
            menu();

        } else {
            cout << "El ID ingresado ya se encuentra asignado" << endl;
            menu();
        }
    }
        break;

    case 'b':
    {
        string id;
        cout << "Ingrese ID de router a remover: ";
        cin >> id;

        if (!network.routerIdAvailable(id)) {

            network.removeRouter(id);
            cout << endl << "Router removido con exito" << endl;
            menu();

        } else {

            cout << "El ID ingresado no existe en la red" << endl;
            menu();
        }
    }
        break;

    case 'c':
    {
        string id;
        cout << "Ingrese ID del router para el cual desea visualizar la tabla: ";
        cin >> id;

        if (!network.routerIdAvailable(id)) {

            map <string, int>::iterator it;
            map <string, int> routeTable = network.getRouters()[id].getRouteTable();

            cout << endl << "Tabla router " << id << endl << endl;

            for (it = routeTable.begin(); it != routeTable.end(); it++) {

                if (it->second >= 0)
                    cout << id << "->" << it->first << " " << it->second << endl;
                else
                    cout << id << "->" << it->first << " x" << endl;
            }

            cout << endl << endl << "Tabla optimizada para router " << id << endl << endl;

            routeTable.clear();
            routeTable = network.getOptimalRouteTable(id);

            for (it = routeTable.begin(); it != routeTable.end(); it++) {

                if (it->second >= 0)
                    cout << id << "->" << it->first << " " << it->second << endl;
                else
                    cout << id << "->" << it->first << " x" << endl;
            }

            menu();

        } else {

            cout << "El ID de router ingresado no existe en la red" << endl;
            menu();
        }
    }
        break;

    case 'd':
    {
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
                menu();

            } else {

                cout << "El ID " << destination << " no existe en la red" << endl;
                menu();
            }

        } else {

            cout << "El ID " << origin << " no existe en la red" << endl;
            menu();
        }
    }
        break;

    case 'e':
    {
        network.getRouters().clear();
        start();
    }
        break;

    default:
        cout << "Opcion no valida" << endl;
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
