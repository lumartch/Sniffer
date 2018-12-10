#include "tcpv6.h"

TCPV6::TCPV6() {
	puertoOrigen = "";
	puertoDestino = "";
	numeroSecuencia = 0;
	nuemeroAcuseRecibido = 0;
	longitudDeCabecera = "";
	reservado = "";
	ns = "";
	cwr = "";
	ece = "";
	urg = "";
	ack = "";
	psh = "";
	rst = "";
	syn = "";
	fin = "";
	ventanaDeTransaccion = "";
	sumaDeVerificacion = "";
	punteroUrgente = "";
	datos = "";
}

TCPV6::TCPV6(const std::string& archivo) {
	TCPV6();
	abrirArchivo(archivo);
}

void TCPV6::abrirArchivo(const std::string& archivo) {
	std::fstream fin(archivo);
	if(fin.good()) {
		fin.seekg(INICIOTCPV6, std::ios::beg);
		setPuertoOrigen(fin);
		setPuertoDestino(fin);
		setNumeroSecuencia(fin);
		setNuemeroAcuseRecibido(fin);
		setLongitudDeCabecera(fin);
		setFlags(fin);
		setVentanaDeTransaccion(fin);
		setSumaDeVerificacion(fin);
		setPunteroUrgente(fin);
		setDatos(fin);
	}
	fin.close();
}

void TCPV6::setPuertoOrigen(std::fstream& archivo) {
	std::string port = "";
	port = port + hexadecimalToBinario(archivo,1);
	port = port + hexadecimalToBinario(archivo,1);
	port = std::to_string(binarioToDecimal(port));
	if(port == "20" || port == "21")		{
		puertoOrigen = port + ": File Transfer Protocol (FTP)";
	} else if(port == "22")					{
		puertoOrigen = port + ": Secure Shell (SSH)";
	} else if(port == "23")					{
		puertoOrigen = port + ": Telnet";
	} else if(port == "25")					{
		puertoOrigen = port + ": Simple Mail Transfer Protocol (SMTP)";
	} else if(port == "50" || port == "51")	{
		puertoOrigen = port + ": IPSec";
	} else if(port == "53")					{
		puertoOrigen = port + ": Domain Name Server (DNS)";
	} else if(port == "67" || port == "68")	{
		puertoOrigen = port + ": Dynamic Host Configuration Protocol (DHCP)";
	} else if(port == "69")					{
		puertoOrigen = port + ": Trivial File Transfer Protocol (TFTP)";
	} else if(port == "80")					{
		puertoOrigen = port + ": HyperText Transfer Protocol (HTTP)";
	} else if(port == "110")					{
		puertoOrigen = port + ": Post Office Protocol (POP3)";
	} else if(port == "119")					{
		puertoOrigen = port + ": Network News Transport Protocol (NNTP";
	} else if(port == "123")					{
		puertoOrigen = port + ": Network Time Protocol (NTP)";
	} else if(port == "135" || port == "136" || port == "137" || port == "138" || port == "139") {
		puertoOrigen = port + ": NetBIOS";
	} else if(port == "143")					{
		puertoOrigen = port + ": Internet Message Access Protocol (IMAP4)";
	} else if(port == "161" || port == "162")	{
		puertoOrigen = port + ": Simple Network Management Protocol (SNMP)";
	} else if(port == "389")					{
		puertoOrigen = port + ": Lightweight Directory Access Protocol";
	} else if(port == "443")					{
		puertoOrigen = port + ": HTTP with Secure Sockets Layer (SSL)";
	} else if(port == "49158") {
		puertoOrigen = port + ": Certificate Management over CMS";
	} else									{
		puertoOrigen = port + ": puerto desconocido";
	}
}

void TCPV6::setPuertoDestino(std::fstream& archivo) {
	std::string port = "";
	port = port + hexadecimalToBinario(archivo,1);
	port = port + hexadecimalToBinario(archivo,1);
	port = std::to_string(binarioToDecimal(port));
	if(port == "20" || port == "21")		{
		puertoDestino = port + ": File Transfer Protocol (FTP)";
	} else if(port == "22")					{
		puertoDestino = port + ": Secure Shell (SSH)";
	} else if(port == "23")					{
		puertoDestino = port + ": Telnet";
	} else if(port == "25")					{
		puertoDestino = port + ": Simple Mail Transfer Protocol (SMTP)";
	} else if(port == "50" || port == "51")	{
		puertoDestino = port + ": IPSec";
	} else if(port == "53")					{
		puertoDestino = port + ": Domain Name Server (DNS)";
	} else if(port == "67" || port == "68")	{
		puertoDestino = port + ": Dynamic Host Configuration Protocol (DHCP)";
	} else if(port == "69")					{
		puertoDestino = port + ": Trivial File Transfer Protocol (TFTP)";
	} else if(port == "80")					{
		puertoDestino = port + ": HyperText Transfer Protocol (HTTP)";
	} else if(port == "110")					{
		puertoDestino = port + ": Post Office Protocol (POP3)";
	} else if(port == "119")					{
		puertoDestino = port + ": Network News Transport Protocol (NNTP";
	} else if(port == "123")					{
		puertoDestino = port + ": Network Time Protocol (NTP)";
	} else if(port == "135" || port == "136" || port == "137" || port == "138" || port == "139") {
		puertoDestino = port + ": NetBIOS";
	} else if(port == "143")					{
		puertoDestino = port + ": Internet Message Access Protocol (IMAP4)";
	} else if(port == "161" || port == "162")	{
		puertoDestino = port + ": Simple Network Management Protocol (SNMP)";
	} else if(port == "389")					{
		puertoDestino = port + ": Lightweight Directory Access Protocol";
	} else if(port == "443")					{
		puertoDestino = port + ": HTTP with Secure Sockets Layer (SSL)";
	} else if(port == "49158") {
		puertoDestino = port + ": Certificate Management over CMS";
	} else									{
		puertoDestino = port + ": puerto desconocido";
	}
}

void TCPV6::setNumeroSecuencia(std::fstream& archivo) {
	std::string resultado = "";
	for(int i = 0; i < 4; i++) {
		int dato = 0;
		std::stringstream stream;
		archivo.read((char*)&dato, BITS1);
		if(dato < 10) {
			stream << "0" << std::hex << dato;
		} else {
			stream << std::hex << dato;
		}
		resultado += stream.str();
	}
	numeroSecuencia = std::stoul (resultado,nullptr,16);
}

void TCPV6::setNuemeroAcuseRecibido(std::fstream& archivo) {
	std::string resultado = "";
	for(int i = 0; i < 4; i++) {
		int dato = 0;
		std::stringstream stream;
		archivo.read((char*)&dato, BITS1);
		if(dato < 10) {
			stream << "0" << std::hex << dato;
		} else {
			stream << std::hex << dato;
		}
		resultado += stream.str();
	}
	nuemeroAcuseRecibido = std::stoul (resultado,nullptr,16);
}

void TCPV6::setLongitudDeCabecera(std::fstream& archivo) {
	std::string binario = hexadecimalToBinario(archivo,1);
	longitudDeCabecera = std::to_string(binarioToDecimal(separarBinario(binario,0,4))) + " bytes";
	reservado = separarBinario(binario,4,7);
	ns = getActivadoDesactivado(std::to_string(binarioToDecimal(separarBinario(binario,7,8))));
}

void TCPV6::setFlags(std::fstream& archivo) {
	std::string binario = hexadecimalToBinario(archivo,1);
	cwr = getActivadoDesactivado(separarBinario(binario,0,1));
	ece = getActivadoDesactivado(separarBinario(binario,1,2));
	urg = getActivadoDesactivado(separarBinario(binario,2,3));
	ack = getActivadoDesactivado(separarBinario(binario,3,4));
	psh = getActivadoDesactivado(separarBinario(binario,4,5));
	rst = getActivadoDesactivado(separarBinario(binario,5,6));
	syn = getActivadoDesactivado(separarBinario(binario,6,7));
	fin = getActivadoDesactivado(separarBinario(binario,7,8));
}

std::string TCPV6::getActivadoDesactivado(std::string bandera) {
	if(bandera == "1") {
		return "Activado";
	}
	return "Desactivado";
}

void TCPV6::setVentanaDeTransaccion(std::fstream& archivo) {
	std::string port = "";
	port = port + hexadecimalToBinario(archivo,1);
	port = port + hexadecimalToBinario(archivo,1);
	ventanaDeTransaccion = std::to_string(binarioToDecimal(port));
}

void TCPV6::setSumaDeVerificacion(std::fstream& archivo) {
	for(int i = 0; i < 2; i++) {
		int dato = 0;
		std::stringstream stream;
		archivo.read((char*)&dato, BITS1);
		if(dato < 10) {
			stream << "0" << std::hex << dato;
		} else {
			stream << std::hex << dato;
		}
		sumaDeVerificacion += stream.str();
	}
}

void TCPV6::setPunteroUrgente(std::fstream& archivo) {
	std::string port = "";
	port = port + hexadecimalToBinario(archivo,1);
	port = port + hexadecimalToBinario(archivo,1);
	punteroUrgente = std::to_string(binarioToDecimal(port));
}

void TCPV6::setDatos(std::fstream& archivo) {
	int cont = 1;
	while(!archivo.eof()) {
		if(archivo.eof()) {
			break;
		}
		int dato = 0;
		std::stringstream stream;
		archivo.read((char*)&dato, 1);
		if(dato < 10) {
			stream << "0" << std::hex << dato;
		} else {
			stream << std::hex << dato;
		}
		if(cont%2 == 0) {
			stream << ":";
		}
		datos += stream.str();
		cont++;
	}
}

std::string TCPV6::getPuertoOrigen() {
	return puertoOrigen;
}

std::string TCPV6::getPuertoDestino() {
	return puertoDestino;
}

unsigned long TCPV6::getNumeroSecuencia() {
	return numeroSecuencia;
}

unsigned long TCPV6::getNuemeroAcuseRecibido() {
	return nuemeroAcuseRecibido;
}

std::string TCPV6::getLongitudDeCabecera() {
	return longitudDeCabecera;
}

std::string TCPV6::getReservado() {
	return reservado;
}

std::string TCPV6::getNs() {
	return ns;
}

std::string TCPV6::getCwr() {
	return cwr;
}

std::string TCPV6::getEce() {
	return ece;
}

std::string TCPV6::getUrg() {
	return urg;
}

std::string TCPV6::getAck() {
	return ack;
}

std::string TCPV6::getPsh() {
	return psh;
}

std::string TCPV6::getRst() {
	return rst;
}

std::string TCPV6::getSyn() {
	return syn;
}

std::string TCPV6::getFin() {
	return fin;
}

std::string TCPV6::getVentanaDeTransaccion() {
	return ventanaDeTransaccion;
}

std::string TCPV6::getSumaDeVerificacion() {
	return sumaDeVerificacion;
}

std::string TCPV6::getPunteroUrgente() {
	return punteroUrgente;
}

std::string TCPV6::getDatos() {
	return datos;
}

int TCPV6::binarioToDecimal(const std::string& bin) {
	int res = 0;
	for(unsigned int i = 0, j = bin.length() - 1; i < bin.length(); i++, j--) {
		if(bin[i] == '1') {
			res += pow(2, j);
		}
	}
	return res;
}

std::string TCPV6::hexadecimalToBinario(std::fstream& archivo, int size) {
	int res = 0;
	archivo.read((char*)&res, size);
	std::string bin = std::bitset<8>(res).to_string(), myRes;
	return bin;
}

std::string TCPV6::separarBinario(const std::string& bin, const int& limInf, const int& limSup) {
	std::string res = "";
	for(int i = limInf; i < limSup; i++) {
		res += bin[i];
	}
	return res;
}

