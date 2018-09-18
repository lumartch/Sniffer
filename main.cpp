#include <iostream>
#include "Ethernet.h"
#include "ipv4.h"
#include "ICMPv4.h"
#include "arpRarp.h"
#include "ipv6.h"
#include "icmpv6.h"

#if _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif // _WIN32

using namespace std;

int main() {
	string archivo, opc;
	do {
		system(CLEAR);
		cout << "---------Sniffer---------";
		cout << endl << "Ingrese el nombre del archivo: ";
		getline(cin, archivo);
		Ethernet eth;
		if (!eth.abrirArchivo(archivo)) {
			cout << "No fue posible abrir el archivo deseado. ¿Desea intentarlo de nuevo? (S/N): " << endl;
		} else {
			cout << endl;
			cout << "¡Archivo abierto correctamente!" << endl << endl;
			cout << "Dirección destino: " << eth.getDireccionDestino() << endl;
			cout << "Dirección origen: " << eth.getDireccionOrigen() << endl;
			cout << "Tipo de protocolo: " << eth.getTipoProtocolo();
			if(eth.getTipoProtocolo() == "08:00") {
				cout << " - Ipv4" << endl << endl;
				Ipv4 ipv4(archivo);
				cout << "Version: " << ipv4.getVersion() << endl;
				cout << "Longitud de cabecera: " << ipv4.getLongitudCabecera() << endl;
				cout << "Servicios: " << ipv4.getServicio() << endl;
				cout << "Desglose de bits: " << ipv4.getDesgloseDeBits() << endl;
				cout << "Longitud total: " << ipv4.getLongitudTotal() << endl;
				cout << "Identificador: " << ipv4.getIdentificador() << endl;
				cout << "Flags: " << ipv4.getFlags() << endl;
				cout << "Posición del fragmento: " << ipv4.getPosicionFragmento() << endl;
				cout << "Tiempo de vida: " << ipv4.getTiempoDeVida() << endl;
				cout << "Protocolo: " << ipv4.getTipoProtocolo() << endl;
				cout << "Suma de cabecera: " << ipv4.getSumaCabecera() << endl;
				cout << "Ip Origen: " << ipv4.getIpOrigen() << endl;
				cout << "Ip Destino: " << ipv4.getIpDestino() << endl;
				if(ipv4.getTipoProtocolo() == "ICMP") {
					ICMPv4 icmp(archivo);
					cout << endl << endl << "-----ICMP-----" << endl;
					cout << "Mensaje informativo: " << icmp.getMensajeInformativo() << endl;
					cout << "Mensaje mensaje de error: " << icmp.getMensajeError() << endl;
					cout << "Checksum: " << icmp.getChecksum() << endl;
				}
			} else if(eth.getTipoProtocolo() == "08:06") {
				cout << " - ARP" << endl << endl;
				ArpRarp arpRarp(archivo);
				cout << "Tipo Hardware: "  << arpRarp.getTipoHardware()    << endl;
				cout << "Tipo Protocolo: " << arpRarp.getTipoProtocolo()   << endl;
				cout << "Longitud Mac: "   << arpRarp.getLongitudMac()     << endl;
				cout << "Longitud Ip: "    << arpRarp.getLongitudIp()      << endl;
				cout << "Codigo Operacion: " << arpRarp.getCodigoOperacion() << endl;
				cout << "Mac Emisor: "     << arpRarp.getMacEmisor()       << endl;
				cout << "Ip Emisor: "      << arpRarp.getIpEmisor()        << endl;
				cout << "Mac Receptor: "   << arpRarp.getMacReceptor()     << endl;
				cout << "Ip Receptor: "    << arpRarp.getIpReceptor()      << endl;
			} else if(eth.getTipoProtocolo() == "80:35") {
				cout << " - RARP" << endl << endl;
				ArpRarp arpRarp(archivo);
				cout << "Tipo Hardware: "  << arpRarp.getTipoHardware()    << endl;
				cout << "Tipo Protocolo: " << arpRarp.getTipoProtocolo()   << endl;
				cout << "Longitud Mac: "   << arpRarp.getLongitudMac()     << endl;
				cout << "Longitud Ip: "    << arpRarp.getLongitudIp()      << endl;
				cout << "Codigo Operacion: " << arpRarp.getCodigoOperacion() << endl;
				cout << "Mac Emisor: "     << arpRarp.getMacEmisor()       << endl;
				cout << "Ip Emisor: "      << arpRarp.getIpEmisor()        << endl;
				cout << "Mac Receptor: "   << arpRarp.getMacReceptor()     << endl;
				cout << "Ip Receptor: "    << arpRarp.getIpReceptor()      << endl;
			} else {
				cout << " - Ipv6" << endl << endl;
				IpV6 ipv6(archivo);
				cout << "Versión: " << ipv6.getVersion() << endl;
				cout << "Tipo de tráfico: " << ipv6.getTrafico() << endl;
				cout << "Etiqueta: " << ipv6.getEtiqueta() << endl;
				cout << "Tamaño de los datos: " << ipv6.getTamanioDatos() << endl;
				cout << "Siguiente cabecera: " << ipv6.getSigCabecera() << endl;
				cout << "Limite de salto: " << ipv6.getLimSalto() << endl;
				cout << "Dirección origen: " << ipv6.getDirOrigen() << endl;
				cout << "Dirección destino: " << ipv6.getDirDestino() << endl;
				cout << "Datos: " << ipv6.getDatos() << endl;
				if(ipv6.getSigCabecera() == "ICMP"){
					ICMPv6 icmp(archivo);
					cout << endl << endl << "-----ICMPv6-----" << endl;
					cout << "Tipo: " << icmp.getTipo() << endl;
					cout << "Codigo: " << icmp.getCodigo() << endl;
					cout << "Checksum: " << icmp.getChecksum() << endl;
				}
			}
			cout << endl << endl << "¿Desea abrir un nuevo archivo?(S/N): ";
		}
		do {
			getline(cin, opc);
		} while(opc != "N" and opc != "n" and
		        opc != "S" and opc != "s");
	} while(opc == "S" or opc == "s");
	cout << endl << "Gracias por usar el analizador de paquetes 'Sniffer'.";
	return 0;
}
