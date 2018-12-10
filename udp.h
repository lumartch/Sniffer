#ifndef UDP_H_INCLUDED
#define UDP_H_INCLUDED

#define INICIOUDP 36
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

class UDP {
public:
	UDP();
	UDP(const std::string& archivo);
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

#endif // UDP_H_INCLUDED
