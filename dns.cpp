#include "dns.h"

DNS::DNS() {
	longitudDNS = "";
	id = "";
	messageType = "";
	opcode = "";
	autoritativo = "";
	truncado = "";
	buscaRecursion = "";
	recursionDisponible = "";
	reservadosZ = "";
	codigoRespueda = "";
	preguntas = "";
	respuestas = "";
	autoridades = "";
	adiocionales = "";
	dominio = "";
	texto = "";
}

DNS::DNS(const std::string& archivo, const int& inicio, const std::string longitudes) {
	DNS();
	longitudDNS = longitudes;
	bitInicio = inicio;
	abrirArchivo(archivo);
}

void DNS::abrirArchivo(const std::string& archivo) {
	std::fstream fin(archivo);
	if(fin.good()) {
		fin.seekg(bitInicio, std::ios::beg);
		setId(fin);
		setBanderas(fin);
		setPreguntas(fin);
		setRespuestas(fin);
		setAutoridades(fin);
		setAdiocionales(fin);
		if(messageType == "0: Consulta"){
			setDominioQuery(fin);
			setTextoQuery(fin);
		}else{
			setDominioResponse(fin);
			setTextoResponse(fin);
		}
	}
	fin.close();
}

void DNS::setId(std::fstream& archivo) {
	int dato = 0;
	std::stringstream stream;
	archivo.read((char*)&dato, 1);
	stream << std::hex << dato;
	archivo.read((char*)&dato, 1);
	stream << std::hex << dato;
	id = stream.str();
}

void DNS::setBanderas(std::fstream& archivo) {
	std::string binario = hexadecimalToBinario(archivo,1);
	binario = binario + hexadecimalToBinario(archivo,1);
	messageType = separarBinario(binario,0,1);
	if(messageType == "0"){/// response
		messageType = "0: Consulta";
        opcode = separarBinario(binario, 1,5);
        truncado = separarBinario(binario,6,7);
        buscaRecursion = separarBinario(binario,7,8);
        reservadosZ = separarBinario(binario,9,11);
        autoritativo = "";
        recursionDisponible = "";
        codigoRespueda = "";
	}else{ /// query
		messageType = "1: Respuesta";
        opcode = separarBinario(binario, 1,5);
        autoritativo = separarBinario(binario,5,6);
        truncado = separarBinario(binario,6,7);
        buscaRecursion = separarBinario(binario,7,8);
        recursionDisponible = separarBinario(binario,8,9);
        reservadosZ = separarBinario(binario,9,12);
        codigoRespueda = separarBinario(binario,12,16);
        if(autoritativo == "0"){
			autoritativo = "0: El servidor no tiene dominio del nombre";
        }else if(autoritativo == "1"){
			autoritativo = "1: El servidor tiene dominio del nombre";
        }else{
			autoritativo = "No encontrado";
        }
        if(recursionDisponible == "0"){
			recursionDisponible = "0: El servidor no soporta resoluciones recursivas";
        }else if(recursionDisponible == "1"){
			recursionDisponible = "1: El servidor soporta resoluciones recursivas";
        }else{
			recursionDisponible = "No encontrado";
        }
        int codigoNum = binarioToDecimal(codigoRespueda);
        if(codigoNum == 0){
			codigoRespueda = "0: Ningun error";
        }else if(codigoNum == 1){
			codigoRespueda = "1: Error de formato";
        }else if(codigoNum == 2){
			codigoRespueda = "2: Fallo en el servicio";
        }else if(codigoNum == 3){
			codigoRespueda = "3: Error en nombre";
        }else if(codigoNum == 4){
			codigoRespueda = "4: No implementado";
        }else if(codigoNum == 5){
			codigoRespueda = "5: Rechazado";
        }else{
			codigoRespueda = "No encontrado";
        }
	}
    int opcodeNum = binarioToDecimal(opcode);
    if(opcodeNum == 0){
		opcode = "0: Consulta estandar";
    }else if(opcodeNum == 1){
		opcode = "1: Consulta inversa";
    }else if(opcodeNum == 2){
		opcode = "2: Solicitud del estado del servidor";
    }else{
		opcode = "No encontrado";
    }
    if(truncado == "0"){
		truncado = "0: No esta truncado";
    }else if(truncado == "1"){
		truncado = "1: Mensaje mas largo de lo que permite la linea";
    }else{
		truncado = "No encontrado";
    }
	if(buscaRecursion == "0"){
		buscaRecursion = "0: No busca resolucion recursiva";
	}else if(buscaRecursion == "1"){
		buscaRecursion = "1: Busca resolucion recursiva";
	}else{
		buscaRecursion = "No encontrado";
	}
}

void DNS::setPreguntas(std::fstream& archivo) {
    std::string texto;
	texto = texto + hexadecimalToBinario(archivo,1);
	texto = texto + hexadecimalToBinario(archivo,1);
	preguntas = std::to_string(binarioToDecimal(texto));
}

void DNS::setRespuestas(std::fstream& archivo) {
    std::string texto;
	texto = texto + hexadecimalToBinario(archivo,1);
	texto = texto + hexadecimalToBinario(archivo,1);
	respuestas = std::to_string(binarioToDecimal(texto));
}

void DNS::setAutoridades(std::fstream& archivo) {
    std::string texto;
	texto = texto + hexadecimalToBinario(archivo,1);
	texto = texto + hexadecimalToBinario(archivo,1);
	autoridades = std::to_string(binarioToDecimal(texto));
}

void DNS::setAdiocionales(std::fstream& archivo) {
    std::string texto;
	texto = texto + hexadecimalToBinario(archivo,1);
	texto = texto + hexadecimalToBinario(archivo,1);
	adiocionales = std::to_string(binarioToDecimal(texto));
}

void DNS::setDominioQuery(std::fstream& archivo) {
    int sizeDominio = 0;
	std::stringstream number(longitudDNS);
    number >> sizeDominio;
    sizeDominio = sizeDominio - 8; /// tamaño udp
    sizeDominio = sizeDominio - 12; /// cabecera dns
    sizeDominio = sizeDominio - 4; /// tipo y clase
    std::cout << "Size: " << sizeDominio << std::endl;
    int dato;
    std::stringstream stream;
    for(int i=0; i < sizeDominio; i++){
		archivo.read((char*)&dato,1);
		stream << char(dato);
		//stream << std::hex << dato;
    }
    std::cout << std::endl;
	dominio = stream.str();
	std::string texto;
	texto = texto + hexadecimalToBinario(archivo,1);
	texto = texto + hexadecimalToBinario(archivo,1);
	tipo = std::to_string(binarioToDecimal(texto));
	if(tipo == "1"){
		tipo = "1 - A";
	}else if(tipo == "5"){
		tipo = "5 - CNAME";
	}else if(tipo == "13"){
		tipo = "13 - HINFO";
	}else if(tipo == "15"){
		tipo = "15 - MX";
	}else if(tipo == "22" || tipo == "23"){
		tipo = "23 - NS";
	}else{
        tipo = tipo + " - No encontrado.";
	}
	texto = "";
	texto = texto + hexadecimalToBinario(archivo,1);
	texto = texto + hexadecimalToBinario(archivo,1);
	clase = std::to_string(binarioToDecimal(texto));
	if(clase == "1"){
        clase = "1 - IN";
	}else if(clase == "3"){
		clase = "3 - CH";
	}else{
		clase = clase + " - No encontrada";
	}
}

void DNS::setTextoQuery(std::fstream& archivo) {
	int cont = 1;
	while(!archivo.eof()) {
		if(archivo.eof()) {
			break;
		}
		int dato = 0;
		std::stringstream stream;
		archivo.read((char*)&dato, 1);
		if(dato < 10) {
			stream << "0" << std::hex << dato;
		} else {
			stream << std::hex << dato;
		}
		texto += stream.str();
		cont++;
	}
	texto = hexadecimalToText(texto);
}

void DNS::setDominioResponse(std::fstream& archivo) {

}

void DNS::setTextoResponse(std::fstream& archivo) {
	texto = "";
	int cont = 1;
	while(!archivo.eof()) {
		if(archivo.eof()) {
			break;
		}
		int dato = 0;
		std::stringstream stream;
		archivo.read((char*)&dato, 1);
		if(dato < 10) {
			stream << char(dato);
		} else {
			stream << char(dato);
		}
		texto += stream.str();
		cont++;
	}
	//texto = hexadecimalToText(texto);
}

std::string DNS::getId() {
	return id;
}

std::string DNS::getMessageType() {
	return messageType;
}

std::string DNS::getOpcode() {
	return opcode;
}

std::string DNS::getAutoritativo() {
	return autoritativo;
}

std::string DNS::getTruncado() {
	return truncado;
}

std::string DNS::getBuscaRecursion() {
	return buscaRecursion;
}

std::string DNS::getRecursionDisponible() {
	return recursionDisponible;
}

std::string DNS::getReservadosZ() {
	return reservadosZ;
}

std::string DNS::getCodigoRespueda() {
	return codigoRespueda;
}

std::string DNS::getPreguntas() {
	return preguntas;
}

std::string DNS::getRespuestas() {
	return respuestas;
}

std::string DNS::getAutoridades() {
	return autoridades;
}

std::string DNS::getAdiocionales() {
	return adiocionales;
}

std::string DNS::getDominio() {
	return dominio;
}

std::string DNS::getTexto() {
	return texto;
}

std::string DNS::getTipo() {
	return tipo;
}

std::string DNS::getClase() {
	return clase;
}

int DNS::binarioToDecimal(const std::string& bin) {
	int res = 0;
	for(unsigned int i = 0, j = bin.length() - 1; i < bin.length(); i++, j--) {
		if(bin[i] == '1') {
			res += pow(2, j);
		}
	}
	return res;
}

std::string DNS::hexadecimalToBinario(std::fstream& archivo, int size) {
	int res = 0;
	archivo.read((char*)&res, size);
	std::string bin = std::bitset<8>(res).to_string(), myRes;
	return bin;
}

std::string DNS::separarBinario(const std::string& bin, const int& limInf, const int& limSup) {
	std::string res = "";
	for(int i = limInf; i < limSup; i++) {
		res += bin[i];
	}
	return res;
}

std::string DNS::hexadecimalToText(const std::string& hexText) {
	int len = hexText.length();
	std::string newString;
	for(int i=0; i< len; i+=2)
	{
		std::string byte = hexText.substr(i,2);
		char chr = (char)(int)strtol(byte.c_str(), nullptr, 16);
		newString.push_back(chr);
	}
	return newString;
}

