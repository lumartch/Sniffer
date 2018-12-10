#ifndef ETHERNET_H
#define ETHERNET_H

#define DIRECCION 6
#define PROTOCOLO 2
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>

class Ethernet {
public:
	Ethernet();
	std::string getDireccionDestino();
	std::string getDireccionOrigen();
	std::string getTipoProtocolo();
	bool abrirArchivo(const std::string&archivo);

private:
	std::string direccionDestino;
	std::string direccionOrigen;
	std::string tipoProtocolo;
	void setDireccion(std::fstream&archivo, std::string&dir);
	void setProtocolo(std::fstream&archivo);
};

#endif // ETHERNET_H
