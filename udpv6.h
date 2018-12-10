#ifndef UDPV6_H_INCLUDED
#define UDPV6_H_INCLUDED

#define INICIOUDPV6 54
#define BYTE1 1
#define BITS1 1
#define BITS16 16

#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <bitset>
#include <cmath>

class UDPV6 {
public:
	UDPV6();
	UDPV6(const std::string& archivo);
	void abrirArchivo(const std::string& archivo);

	void setPuertoOrigen(std::fstream& archivo);
	void setPuertoDestino(std::fstream& archivo);
	void setLongitud(std::fstream& archivo);
	void setSumaVerificacion(std::fstream& archivo);
	void setDatos(std::fstream& archivo);

	std::string getPuertoOrigen();
	std::string getPuertoDestino();
	std::string getLongitud();
	std::string getSumaCabecera();
	std::string getDatos();

	int binarioToDecimal(const std::string& bin);
	std::string hexadecimalToBinario(std::fstream& archivo, int size);
	std::string separarBinario(const std::string&bin, const int &limInf, const int &limSup);
private:
	std::string puertoOrigen;
	std::string puertoDestino;
	std::string longitud;
	std::string sumaDeVerificacion;
	std::string datos;
};

#endif // UDPV6_H_INCLUDED
