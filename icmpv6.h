#ifndef ICMPV6_H
#define ICMPV6_H

#define INICIOICMPV6 54
#define BITS1 1

#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class ICMPv6 {
public:
	ICMPv6();
	ICMPv6(const std::string& archivo);
	void abrirArchivo(const std::string&archivo);
	void setTipoCodigo(std::fstream& archivo);
	void setChecksum(std::fstream& archivo);
	std::string getTipo();
	std::string getCodigo();
	std::string getChecksum();

private:
	std::string tipo;
	std::string codigo;
	std::string checksum;
	std::string datos;
};

#endif // ICMPV6_H
