#include "simulator.h"

void Simulator::createNetwork()
{

}

void Simulator::loadNetwork()
{
    try {
        cout << "Ingrese el nombre del archivo de texto" << endl;

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
        if (c == '1')
            cout << "Error archivo de lectura" << endl;
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
    cout << endl << "Ingrese una opcion " << endl;

    cout << endl;
    cout << "a) Agregar router" << endl;
    cout << "b) Remover router" << endl;
    cout << "c) Visualisar tablas de red" << endl;
    cout << "d) Ruta optima para enviar un paquete" << endl;
    cout << "d) Volver al menu principal" << endl;
    cout << endl;
    cout << "Opcion: ";

    cin >> option;

    switch(option) {

    case 'a':
    {
        string id;
        cout << "Ingrese nombre del router: ";
        cin >> id;

        if (network.routerAvailable(id)) {

            cout << endl << endl << "Ingrese peso para el enlace entre routers si no se conectan directamente ingrese x " << endl;

            map <string, Router>::iterator it;
            map <string, int> routeTable;
            string value;

            routeTable[id] = 0;

            for (it = network.getRouters().begin(); it != network.getRouters().end(); it++) {

                cout << id << "->" << it->first;
                cin >> value;

                if (value == "x")
                    routeTable[it->first] = -1;
                else
                    routeTable[it->first] = atoi(value.c_str());
            }

            network.addRouter(id, Router(routeTable));

            cout << endl << "Router agregado con exito" << endl;

        } else {
            cout << "El nombre ingresado ya existe en la red" << endl;
            menu();
        }
    }
        break;

    case 'b':
    {
        string id;
        cout << "Ingrese nombre del router a remover: ";
        cin >> id;

        if (network.routerAvailable(id)) {

            network.removeRouter(id);

            cout << endl << "Router removido con exito" << endl;

        } else {
            cout << "El nombre ingresado no existe en la red" << endl;
            menu();
        }
    }
        break;

    case 'c':
    {
        string id;
        cout << "Ingrese nombre del router del cual quiere ver la tabla: ";
        cin >> id;

        if (network.routerAvailable(id)) {

            network.removeRouter(id);

            cout << endl << "Router removido con exito" << endl;

        } else {
            cout << "El router ingresado no existe en la red" << endl;
            menu();
        }
    }
        break;

    case 'd':
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
