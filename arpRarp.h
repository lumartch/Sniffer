#ifndef ARPRARP_H_INCLUDED
#define ARPRARP_H_INCLUDED

#define INICIOARPRARP 14
#define BYTE1   1
#define BITS0  0
#define BITS4  4
#define BITS3  3
#define BITS6  6
#define BITS8  8
#define DIRECCION 6

#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <bitset>
#include <cmath>

class ArpRarp {
public:
	ArpRarp();
	ArpRarp(const std::string&archivo);
	void abrirArchivo(const std::string&archivo);
	std::string getTipoHardware();
	std::string getTipoProtocolo();
	std::string getLongitudMac();
	std::string getLongitudIp();
	std::string getCodigoOperacion();
	std::string getMacEmisor();
	std::string getIpEmisor();
	std::string getMacReceptor();
	std::string getIpReceptor();
	std::string getDatos();

private:
	std::string tipoHardware;
	std::string tipoProtocolo;
	std::string longitudMac;
	std::string longitudIp;
	std::string codigoOperacion;
	std::string macEmisor;
	std::string ipEmisor;
	std::string macReceptor;
	std::string ipReceptor;
	std::string datos;
	int binarioToDecimal(const std::string&bin);
	std::string hexadecimalToBinario(std::fstream&archivo);
	std::string separarBinario(const std::string&bin, const int &limInf, const int &limSup);
	std::string getTipoHardwareCadena(const std::string& codigo);
	void setProtocolo(std::fstream&archivo);
	std::string getProtocoloCadena();
	std::string getCodigoOperacionCadena(const std::string& codigo);
	void setDireccion(std::fstream&archivo, std::string&dir);
	void formatoIp(std::string&ip, std::fstream& archivo);
};

#endif // ARPRARP_H_INCLUDED
