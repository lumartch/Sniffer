#ifndef IPV6_H
#define IPV6_H

#define INICIOIPV6 14
#define BYTE1 1
#define BITS0 0
#define BITS4 4
#define BITS3 3
#define BITS6 6
#define BITS8 8
#define BITS12 12
#define BITS16 16

#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <bitset>
#include <cmath>

class IpV6 {
public:
	IpV6();
	IpV6(const std::string& archivo);
	void abrirArchivo(const std::string& archivo);
	std::string getVersion();
	std::string getTrafico();
	std::string getEtiqueta();
	std::string getTamanioDatos();
	std::string getSigCabecera();
	std::string getLimSalto();
	std::string getDirOrigen();
	std::string getDirDestino();
	std::string getDatos();

private:
	std::string version;
	std::string trafico;
	std::string etiqueta;
	std::string tamanioDatos;
	std::string sigCabecera;
	std::string limSalto;
	std::string dirOrigen;
	std::string dirDestino;
	std::string datos;
	int binarioToDecimal(const std::string&bin);
	std::string hexadecimalToBinario(std::fstream&archivo);
	std::string separarBinario(const std::string&bin, const int &limInf, const int &limSup);
	std::string tipoTrafico(const std::string&bin);
	std::string determinarCabecera(const std::string&bin);
	void formatoOcteto(std::string&var, std::fstream& archivo);
};

#endif // IPV6_H
