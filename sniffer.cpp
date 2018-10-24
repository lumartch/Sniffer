#include "sniffer.h"

void Sniffer::showData() {
	string archivo("new_archivo.bin"), opc;
	do {
		system(CLEAR);
		cout << "---------Sniffer---------";
		Ethernet eth;
		if (!eth.abrirArchivo(archivo)) {
			cout << "No fue posible abrir el archivo deseado. �Desea intentarlo de nuevo? (S/N): " << endl;
		} else {
			cout << endl;
			cout << "�Archivo abierto correctamente!" << endl << endl;
			cout << "Direcci�n destino: " << eth.getDireccionDestino() << endl;
			cout << "Direcci�n origen: " << eth.getDireccionOrigen() << endl;
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
				cout << "Posici�n del fragmento: " << ipv4.getPosicionFragmento() << endl;
				cout << "Tiempo de vida: " << ipv4.getTiempoDeVida() << endl;
				cout << "Protocolo: " << ipv4.getTipoProtocolo() << endl;
				cout << "Suma de cabecera: " << ipv4.getSumaCabecera() << endl;
				cout << "Ip Origen: " << ipv4.getIpOrigen() << endl;
				cout << "Ip Destino: " << ipv4.getIpDestino() << endl;
				cout << "Datos: " << ipv4.getDatos() << endl;
				if(ipv4.getTipoProtocolo() == "ICMP") {
					ICMPv4 icmp(archivo);
					cout << endl << endl << "-----ICMP-----" << endl;
					cout << "Mensaje informativo: " << icmp.getMensajeInformativo() << endl;
					cout << "Mensaje mensaje de error: " << icmp.getMensajeError() << endl;
					cout << "Checksum: " << icmp.getChecksum() << endl;
				} else if(ipv4.getTipoProtocolo() == "TCP") {
					cout << endl << endl << "-----TCP-----" << endl;
					TCP tcp(archivo);
					cout << "Puerto origen: " << tcp.getPuertoOrigen() << endl;
					cout << "Puerto destino: " << tcp.getPuertoDestino() << endl;
					cout << "Numero de secuencia: " << tcp.getNumeroSecuencia() << endl;
					cout << "Numero de acuse de recibido: " << tcp.getNuemeroAcuseRecibido() << endl;
					cout << "Longitud de cabecera: " << hex << tcp.getLongitudDeCabecera() << endl;
					cout << "Reservado: " << tcp.getReservado() << endl;
					cout << "Banderas:\n";
					cout << "\tNS:  " << tcp.getNs() << endl;
					cout << "\tCWR: " << tcp.getCwr() << endl;
					cout << "\tECE: " << tcp.getEce() << endl;
					cout << "\tURG: " << tcp.getUrg() << endl;
					cout << "\tACK: " << tcp.getAck() << endl;
					cout << "\tPSH: " << tcp.getPsh() << endl;
					cout << "\tRST: " << tcp.getRst() << endl;
					cout << "\tSYN: " << tcp.getSyn() << endl;
					cout << "\tFIN: " << tcp.getFin() << endl;
					cout << "Ventana de recepcion: " << tcp.getVentanaDeTransaccion() << endl;
					cout << "Suma de verificacion: " << tcp.getSumaDeVerificacion() << endl;
					cout << "Puntero urgente: " << tcp.getPunteroUrgente() << endl;
					cout << "Datos: " << tcp.getDatos() << endl;
				} else if(ipv4.getTipoProtocolo() == "UDP") {
					cout << endl << endl << "-----UDP-----" << endl;
					UDP udp(archivo);
					cout << "Puerto Origen: " 			<< udp.getPuertoOrigen() 	<< endl;
					cout << "Puerto destino: " 			<< udp.getPuertoDestino() 	<< endl;
					cout << "Longitud total: " 			<< udp.getLongitud()	 	<< endl;
					cout << "Suma de verificacion: " 	<< udp.getSumaCabecera() 	<< endl;
					cout << "Datos: " << udp.getDatos() << endl;
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
				cout << "Datos: " << arpRarp.getDatos() << endl;
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
				cout << "Datos: " << arpRarp.getDatos() << endl;
			} else {
				cout << " - Ipv6" << endl << endl;
				IpV6 ipv6(archivo);
				cout << "Versi�n: " << ipv6.getVersion() << endl;
				cout << "Tipo de tr�fico: " << ipv6.getTrafico() << endl;
				cout << "Etiqueta: " << ipv6.getEtiqueta() << endl;
				cout << "Tama�o de los datos: " << ipv6.getTamanioDatos() << endl;
				cout << "Siguiente cabecera: " << ipv6.getSigCabecera() << endl;
				cout << "Limite de salto: " << ipv6.getLimSalto() << endl;
				cout << "Direcci�n origen: " << ipv6.getDirOrigen() << endl;
				cout << "Direcci�n destino: " << ipv6.getDirDestino() << endl;
				cout << "Datos: " << ipv6.getDatos() << endl;
				if(ipv6.getSigCabecera() == "ICMP") {
					ICMPv6 icmp(archivo);
					cout << endl << endl << "-----ICMPv6-----" << endl;
					cout << "Tipo: " << icmp.getTipo() << endl;
					cout << "Codigo: " << icmp.getCodigo() << endl;
					cout << "Checksum: " << icmp.getChecksum() << endl;
				} else if(ipv6.getSigCabecera() == "TCP") {
					cout << endl << endl << "-----TCP-----" << endl;
					TCPV6 tcp(archivo);
					cout << "Puerto origen: " << tcp.getPuertoOrigen() << endl;
					cout << "Puerto destino: " << tcp.getPuertoDestino() << endl;
					cout << "Numero de secuencia: " << tcp.getNumeroSecuencia() << endl;
					cout << "Numero de acuse de recibido: " << tcp.getNuemeroAcuseRecibido() << endl;
					cout << "Longitud de cabecera: " << hex << tcp.getLongitudDeCabecera() << endl;
					cout << "Reservado: " << tcp.getReservado() << endl;
					cout << "Banderas:\n";
					cout << "\tNS:  " << tcp.getNs() << endl;
					cout << "\tCWR: " << tcp.getCwr() << endl;
					cout << "\tECE: " << tcp.getEce() << endl;
					cout << "\tURG: " << tcp.getUrg() << endl;
					cout << "\tACK: " << tcp.getAck() << endl;
					cout << "\tPSH: " << tcp.getPsh() << endl;
					cout << "\tRST: " << tcp.getRst() << endl;
					cout << "\tSYN: " << tcp.getSyn() << endl;
					cout << "\tFIN: " << tcp.getFin() << endl;
					cout << "Ventana de recepcion: " << tcp.getVentanaDeTransaccion() << endl;
					cout << "Suma de verificacion: " << tcp.getSumaDeVerificacion() << endl;
					cout << "Puntero urgente: " << tcp.getPunteroUrgente() << endl;
					cout << "Datos: " << tcp.getDatos() << endl;
				} else if(ipv6.getSigCabecera() == "UDP") {
					cout << endl << endl << "-----UDP-----" << endl;
					UDPV6 udp(archivo);
					cout << "Puerto Origen: " 			<< udp.getPuertoOrigen() 	<< endl;
					cout << "Puerto destino: " 			<< udp.getPuertoDestino() 	<< endl;
					cout << "Longitud total: " 			<< udp.getLongitud()	 	<< endl;
					cout << "Suma de verificacion: " 	<< udp.getSumaCabecera() 	<< endl;
					cout << "Datos: " << udp.getDatos() << endl;
				}
			}
		}
	} while(opc == "S" or opc == "s");
	cout << endl << "Gracias por usar el analizador de paquetes 'Sniffer'.";
}

