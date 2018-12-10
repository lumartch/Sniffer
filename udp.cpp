#include "udp.h"

UDP::UDP() {
	puertoOrigen = "";
	puertoDestino = "";
	longitud = "";
	sumaDeVerificacion = "";
	datos = "";
}

UDP::UDP(const std::string& archivo) {
	UDP();
	abrirArchivo(archivo);
}

void UDP::abrirArchivo(const std::string& archivo) {
	std::fstream fin(archivo);
	if(fin.good()) {
		fin.seekg(INICIOUDP, std::ios::beg);
		setPuertoOrigen(fin);
		setPuertoDestino(fin);
		setLongitud(fin);
		setSumaVerificacion(fin);
		setDatos(fin);
	}
	fin.close();
}

void UDP::setPuertoOrigen(std::fstream& archivo) {
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

void UDP::setPuertoDestino(std::fstream& archivo) {
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

void UDP::setLongitud(std::fstream& archivo) {
	std::string port = "";
	port = port + hexadecimalToBinario(archivo,1);
	port = port + hexadecimalToBinario(archivo,1);
	longitud = std::to_string(binarioToDecimal(port));
}

void UDP::setSumaVerificacion(std::fstream& archivo) {
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

void UDP::setDatos(std::fstream& archivo) {
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

std::string UDP::getPuertoOrigen() {
	return puertoOrigen;
}

std::string UDP::getPuertoDestino() {
	return puertoDestino;
}

std::string UDP::getLongitud() {
	return longitud;
}

std::string UDP::getSumaCabecera() {
	return sumaDeVerificacion;
}

std::string UDP::getDatos() {
	return datos;
}

int UDP::binarioToDecimal(const std::string& bin) {
	int res = 0;
	for(unsigned int i = 0, j = bin.length() - 1; i < bin.length(); i++, j--) {
		if(bin[i] == '1') {
			res += pow(2, j);
		}
	}
	return res;
}

std::string UDP::hexadecimalToBinario(std::fstream& archivo, int size) {
	int res = 0;
	archivo.read((char*)&res, size);
	std::string bin = std::bitset<8>(res).to_string(), myRes;
	return bin;
}

std::string UDP::separarBinario(const std::string& bin, const int& limInf, const int& limSup) {
	std::string res = "";
	for(int i = limInf; i < limSup; i++) {
		res += bin[i];
	}
	return res;
}

