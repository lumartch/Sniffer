#ifndef TCPV6_H_INCLUDED
#define TCPV6_H_INCLUDED

#define INICIOTCPV6 54
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

class TCPV6 {
public:
	TCPV6();
	TCPV6(const std::string& archivo);
	void abrirArchivo(const std::string& archivo);

	void setPuertoOrigen(std::fstream& archivo);
	void setPuertoDestino(std::fstream& archivo);
	void setNumeroSecuencia(std::fstream& archivo);
	void setNuemeroAcuseRecibido(std::fstream& archivo);
	void setLongitudDeCabecera(std::fstream& archivo);
	void setFlags(std::fstream& archivo);
	void setVentanaDeTransaccion(std::fstream& archivo);
	void setSumaDeVerificacion(std::fstream& archivo);
	void setPunteroUrgente(std::fstream& archivo);
	void setDatos(std::fstream& archivo);

	std::string getPuertoOrigen();
	std::string getPuertoDestino();
	unsigned long getNumeroSecuencia();
	unsigned long getNuemeroAcuseRecibido();
	std::string getLongitudDeCabecera();
	std::string getReservado();
	std::string getNs();
	std::string getCwr();
	std::string getEce();
	std::string getUrg();
	std::string getAck();
	std::string getPsh();
	std::string getRst();
	std::string getSyn();
	std::string getFin();
	std::string getVentanaDeTransaccion();
	std::string getSumaDeVerificacion();
	std::string getPunteroUrgente();
	std::string getDatos();

	int binarioToDecimal(const std::string& bin);
	std::string hexadecimalToBinario(std::fstream& archivo, int size);
	std::string separarBinario(const std::string&bin, const int &limInf, const int &limSup);

private:
	std::string puertoOrigen;
	std::string puertoDestino;
	unsigned long numeroSecuencia;
	unsigned long nuemeroAcuseRecibido;
	std::string longitudDeCabecera;
	std::string reservado;
	std::string ns;
	std::string cwr;
	std::string ece;
	std::string urg;
	std::string ack;
	std::string psh;
	std::string rst;
	std::string syn;
	std::string fin;
	std::string ventanaDeTransaccion;
	std::string sumaDeVerificacion;
	std::string punteroUrgente;
	std::string datos;

	std::string getActivadoDesactivado(std::string bandera);
};

#endif // TCPV6_H_INCLUDED
