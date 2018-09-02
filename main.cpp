#include <iostream>
#include "Ethernet.h"
#include "ipv4.h"

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
    cout << endl;
    cout << "¡Archivo abierto correctamente!" << endl << endl;
    cout << "Dirección destino: " << eth.getDireccionDestino() << endl;
    cout << "Dirección origen: " << eth.getDireccionOrigen() << endl;
    cout << "Tipo de protocolo: " << eth.getTipoProtocolo();
    if(eth.getTipoProtocolo() == "08:00"){
        cout << " - Ipv4" << endl << endl;
        Ipv4 ipv4(archivo);
        cout << "Version: " << ipv4.getVersion() << endl;
        cout << "Longitud de cabecera: " << ipv4.getLongitudCabecera() << endl;
    }
    else if(eth.getTipoProtocolo() == "08:06"){
        cout << " - ARP" << endl << endl;
    }
    else if(eth.getTipoProtocolo() == "80:35"){
        cout << " - RARP" << endl << endl;
    }
    else{
        cout << " - Ipv6" << endl << endl;
    }
    return 0;
}
