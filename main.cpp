#include <iostream>
#include <fstream>
#include <router.h>
#include <network.h>

void simulator();
void createNetwork();
void loadNetwork();
map <char, int> dataToRouteTable(string);
void menu(Network *);

int main()
{
    simulator();
    return 0;
}

void simulator () {

    string option;

    cout<<endl;
    cout<<"||||||||||||||||||||||||||||||||||||||||||"<<endl;
    cout<<"|||                                    |||"<<endl;
    cout<<"|||            BIENVENIDO AL           |||"<<endl;
    cout<<"|||        SIMULADOR DE ROUTERS        |||"<<endl;
    cout<<"|||                                    |||"<<endl;
    cout<<"|||          Salir presione *          |||"<<endl;
    cout<<"|||                                    |||"<<endl;
    cout<<"||||||||||||||||||||||||||||||||||||||||||"<<endl;
    cout<<endl;
    cout<<"Opcion: ";

    cin >> option;

    if (option.compare("*"))  {

        if (option == "admin")
            createNetwork();
        else
            loadNetwork();
    }
}

void loadNetwork() {

    Network network;


    try {
        cout << "Ingrese el nombre del archivo de texto" << endl;

        string file;

        fflush(stdin);
        getline(cin, file);


        ifstream fin;
        fin.open(file + ".txt");
        if (!fin.is_open())
            throw '1';

        int i = 0;
        fin.seekg(0);
        for (string line; getline(fin, line); ) {

            network.addRouter('A' + i, Router(dataToRouteTable(line)));
        }

        fin.close();

    }  catch (char c) {
        if (c == '1')
            cout << "Error archivo de lectura" << endl;
        else
            cout << "Error inesperado" << endl;
    }


    if(network.getRouters().size() > 0) {

        menu(&network);
    } else {
        cout << "No se encontraron datos de una red en el archivo" << endl;
    }
}


void createNetwork(){}

map <char, int> dataToRouteTable (string value) {

    string aux;
    map <char, int> table;
    int j = 0;

    for (unsigned i = 0; i < value.length(); i++) {

        if (value[i] == ';') {
            cout << aux << endl;
            table['A' + j++] = atoi(aux.c_str());
            aux.clear();
            i++;
        }

        aux += value[i];
    }

    return table;
}

void menu(Network *network) {

    char option;
    cout << endl << "Ingrese una opcion " << endl;

    cout << endl;
    cout << "a) Agregar router" << endl;
    cout << "b) Remover router" << endl;
    cout << "c) Visualisar tablas de red" << endl;
    cout << "d) Costo y ruta optima para enviar un paquete" << endl;
    cout << endl;
    cout << "Opcion: ";

    cin >> option;

    switch(option) {

    case 'a':
    {
        char id;
        cout << "Ingrese nombre del router: ";
        cin >> id;

        if (network->routerAvailable(id)) {

            cout << endl << endl << "Ingrese peso para el enlace entre routers si no se conectan directamente ingrese x " << endl;

            map <char, Router>::iterator it;
            map <char, int> routeTable;
            string value;

            routeTable[id] = 0;

            for (it = network->getRouters().begin(); it != network->getRouters().end(); it++) {

                cout << id << "->" << it->first;
                cin >> value;

                if (value == "x")
                    routeTable[it->first] = -1;
                else
                    routeTable[it->first] = atoi(value.c_str());
            }

            network->addRouter(id, Router(routeTable));

            cout << endl << "Router agregado con exito" << endl;

        } else {
            cout << "El nombre ingresado ya existe en la red" << endl;
            menu(network);
        }
    }
        break;

    case 'b':
    {
        char id;
        cout << "Ingrese nombre del router a remover: ";
        cin >> id;

        if (network->routerAvailable(id)) {

            network->removeRouter(id);

            cout << endl << "Router removido con exito" << endl;

        } else {
            cout << "El nombre ingresado no existe en la red" << endl;
            menu(network);
        }
    }
        break;

    case 'c':
    {
        char id;
        cout << "Ingrese nombre del router del cual quiere ver la tabla: ";
        cin >> id;

        if (network->routerAvailable(id)) {

            network->removeRouter(id);

            cout << endl << "Router removido con exito" << endl;

        } else {
            cout << "El nombre ingresado no existe en la red" << endl;
            menu(network);
        }
    }
        break;

    case 'd':
        break;

    default:
        cout << "Opcion no valida" << endl;
        menu(network);

    }

}
