#include <iostream>
#include <fstream>
#include <router.h>
#include <network.h>

void simulator();
void createNetwork();
void loadNetwork();
map <char, int> dataToRouteTable(string);

int main()
{
    simulator();
    return 0;
}

void simulator () {

    string option;

    cout<<endl;
    cout<<"|||||||||||||||||||||||||||||||||||||||||||"<<endl;
    cout<<"|||                                     |||"<<endl;
    cout<<"|||            BIENVENIDO AL            |||"<<endl;
    cout<<"|||         SIMULADOR DE REDES          |||"<<endl;
    cout<<"|||                                     |||"<<endl;
    cout<<"|||           Salir presione *          |||"<<endl;
    cout<<"|||                                     |||"<<endl;
    cout<<"|||||||||||||||||||||||||||||||||||||||||||"<<endl;
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

            network.addRouter('A' + i, Router('A' + i, dataToRouteTable(line)));
        }

        fin.close();

    }  catch (char c) {
        if (c == '1')
            cout << "Error archivo de lectura" << endl;
        else
            cout << "Error inesperado" << endl;
    }


    if(network.getRouters().size() > 0) {



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
