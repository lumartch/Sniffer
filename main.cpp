#include <iostream>
#include "Ethernet.h"

using namespace std;

int main() {
    string archivo;
    Ethernet eth;
    cout << "---------Sniffer---------" << endl;
    cout << "Ingrese el nombre del archivo: ";
    getline(cin, archivo);
    if (!eth.abrirArchivo(archivo)){
        cout << "No fue posible abrir el archivo deseado." << endl;
        return 0;
    }
    cout << "¡Archivo abierto correctamente!" << endl;
    cout << "Dirección destino: " << eth.getDireccionDestino() << endl;
    cout << "Dirección origen: " << eth.getDireccionOrigen() << endl;
    cout << "Tipo de protocolo: " << eth.getTipoProtocolo() << endl;
    if(eth.getTipoProtocolo() == "0800"){

    }
    else if(eth.getTipoProtocolo() == "0806"){

    }
    else if(eth.getTipoProtocolo() == "8035"){

    }
    else{

    }
    return 0;
}
