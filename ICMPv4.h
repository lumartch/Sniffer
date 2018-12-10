#ifndef ICMPV4_H
#define ICMPV4_H

#define INICIOICMPV4 34
#define BITS1 1

#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class ICMPv4 {
public:
	ICMPv4();
	ICMPv4(const std::string& archivo);
	void abrirArchivo(const std::string&archivo);
	void setMensajeInformativo(std::fstream& archivo);
	void setMensajeError(std::fstream& archivo);
	void setChecksum(std::fstream& archivo);
	std::string getMensajeInformativo();
	std::string getMensajeError();
	std::string getChecksum();

private:
	std::string mensajeInformativo;
	std::string mensajeError;
	std::string checksum;
};

#endif // ICMPV4_H
