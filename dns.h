#ifndef DNS_H_INCLUDED
#define DNS_H_INCLUDED

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
#include <stdlib.h>

class DNS {
public:
	DNS();
	DNS(const std::string& archivo, const int& inicio, const std::string longitudDNS);
	void abrirArchivo(const std::string& archivo);

	void setId(std::fstream& archivo);
	void setBanderas(std::fstream& archivo);
	void setPreguntas(std::fstream& archivo);
	void setRespuestas(std::fstream& archivo);
	void setAutoridades(std::fstream& archivo);
	void setAdiocionales(std::fstream& archivo);
	void setDominioQuery(std::fstream& archivo);
	void setTextoQuery(std::fstream& archivo);
	void setDominioResponse(std::fstream& archivo);
	void setTextoResponse(std::fstream& archivo);

	std::string getId();
	std::string getMessageType();
	std::string getOpcode();
	std::string getAutoritativo();
	std::string getTruncado();
	std::string getBuscaRecursion();
	std::string getRecursionDisponible();
	std::string getReservadosZ();
	std::string getCodigoRespueda();
	std::string getPreguntas();
	std::string getRespuestas();
	std::string getAutoridades();
	std::string getAdiocionales();
	std::string getDominio();
	std::string getTexto();
	std::string getTipo();
	std::string getClase();

	int binarioToDecimal(const std::string& bin);
	std::string hexadecimalToBinario(std::fstream& archivo, int size);
	std::string separarBinario(const std::string&bin, const int &limInf, const int &limSup);
	std::string hexadecimalToText(const std::string& hexText);

private:
	int bitInicio;
	std::string longitudDNS;
	std::string id;
	std::string messageType;
	std::string opcode;
	std::string autoritativo;
	std::string truncado;
	std::string buscaRecursion;
	std::string recursionDisponible;
	std::string reservadosZ;
	std::string codigoRespueda;
	std::string preguntas;
	std::string respuestas;
	std::string autoridades;
	std::string adiocionales;
	std::string dominio;
	std::string texto;
	std::string tipo;
	std::string clase;
};

#endif // DNS_H_INCLUDED
