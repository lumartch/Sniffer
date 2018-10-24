#ifndef IPV4_H
#define IPV4_H

#define INICIOIPV4 14
#define BYTE1 1
#define BITS0 0
#define BITS4 4
#define BITS3 3
#define BITS6 6
#define BITS8 8

#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <bitset>
#include <cmath>

class Ipv4 {
public:
	Ipv4();
	Ipv4(const std::string&archivo);
	void abrirArchivo(const std::string&archivo);
	std::string getVersion();
	std::string getLongitudCabecera();
	std::string getServicio();
	std::string getDesgloseDeBits();
	std::string getLongitudTotal();
	std::string getIdentificador();
	std::string getFlags();
	std::string getPosicionFragmento();
	std::string getTiempoDeVida();
	std::string getTipoProtocolo();
	std::string getSumaCabecera();
	std::string getIpOrigen();
	std::string getIpDestino();
	std::string getDatos();

private:
	std::string version;
	std::string longitudCabecera;
	std::string servicio;
	std::string desgloseDeBits;
	std::string longitudTotal;
	std::string identificador;
	std::string flags;
	std::string posicionFragmento;
	std::string tiempoDeVida;
	std::string tipoProtocolo;
	std::string sumaCabecera;
	std::string ipOrigen;
	std::string ipDestino;
	std::string datos;
	int binarioToDecimal(const std::string&bin);
	std::string hexadecimalToBinario(std::fstream&archivo);
	std::string separarBinario(const std::string&bin, const int &limInf, const int &limSup);
	std::string tipoServicio(const std::string&bin);
	std::string desglozandoBits(const std::string&bin);
	std::string banderasActivadas(const std::string&bin);
	std::string determinarProtocolo(const std::string&bin);
	void formatoIp(std::string&ip, std::fstream& archivo);
};

#endif // IPV4_H
