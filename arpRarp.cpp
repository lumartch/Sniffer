#include "arpRarp.h"

#include <iostream>

ArpRarp::ArpRarp() {
	this->tipoHardware = "";
	this->tipoProtocolo = "";
	this->longitudMac = "";
	this->longitudIp = "";
	this->codigoOperacion = "";
	this->macEmisor = "";
	this->ipEmisor = "";
	this->macReceptor = "";
	this->ipReceptor = "";
}

ArpRarp::ArpRarp(const std::string& archivo) {
	ArpRarp();
	abrirArchivo(archivo);
}

void ArpRarp::abrirArchivo(const std::string& archivo) {
	std::fstream fin(archivo);
	if(fin.good()) {
		fin.seekg(INICIOARPRARP, std::ios::beg);
        std::string binario = hexadecimalToBinario(fin);
        binario += hexadecimalToBinario(fin);
        tipoHardware = getTipoHardwareCadena(std::to_string(binarioToDecimal(binario)));
        setProtocolo(fin);
        tipoProtocolo = getProtocoloCadena();
        int longitud(0);
        fin.read((char*)&longitud, BYTE);
        std::stringstream ss;
        ss << std::hex << longitud;
        longitudMac = ss.str();
        fin.read((char*)&longitud, BYTE);
        ss.str(""); /// Para limpiar ss
        ss << std::hex << longitud;
        longitudIp = ss.str();
        binario = hexadecimalToBinario(fin);
        binario += hexadecimalToBinario(fin);
        codigoOperacion = std::to_string(binarioToDecimal(binario));
        codigoOperacion = getCodigoOperacionCadena(codigoOperacion);
        setDireccion(fin, macEmisor);
        formatoIp(ipEmisor, fin);
        setDireccion(fin, macReceptor);
        formatoIp(ipReceptor,fin);
	}
	fin.close();
}

std::string ArpRarp::getTipoHardware() {
    return tipoHardware;
}

std::string ArpRarp::getTipoProtocolo() {
    return tipoProtocolo;
}

std::string ArpRarp::getLongitudMac() {
    return longitudMac;
}

std::string ArpRarp::getLongitudIp() {
    return longitudIp;
}

std::string ArpRarp::getCodigoOperacion() {
    return codigoOperacion;
}

std::string ArpRarp::getMacEmisor() {
    return macEmisor;
}

std::string ArpRarp::getIpEmisor() {
    return ipEmisor;
}

std::string ArpRarp::getMacReceptor() {
    return macReceptor;
}

std::string ArpRarp::getIpReceptor() {
    return ipReceptor;
}

int ArpRarp::binarioToDecimal(const std::string& bin) {
    int res = 0;
    for(unsigned int i = 0, j = bin.length() - 1; i < bin.length(); i++, j--) {
        if(bin[i] == '1') {
            res += pow(2, j);
        }
    }
    return res;
}

std::string ArpRarp::hexadecimalToBinario(std::fstream& archivo) {
    int res = 0;
    archivo.read((char*)&res, BYTE);
    std::string bin = std::bitset<8>(res).to_string(), myRes;
    return bin;
}

std::string ArpRarp::separarBinario(const std::string& bin, const int& limInf, const int& limSup) {
    std::string res = "";
    for(int i = limInf; i < limSup; i++) {
        res += bin[i];
    }
    return res;
}

std::string ArpRarp::getTipoHardwareCadena(const std::string& codigo) {
    if (codigo == "0") {
        return "Reserved";
    }
    else if (codigo == "1") {
        return "Ethernet (10Mb)";
    }
    else if (codigo == "2") {
        return "Experimental Ethernet (3Mb)";
    }
    else if (codigo == "3") {
        return "Amateur Radio AX.25";
    }
    else if (codigo == "4") {
        return "Proteon ProNET Token Ring";
    }
    else if (codigo == "5") {
        return "Chaos";
    }
    else if (codigo == "6") {
        return "IEEE 802 Networks";
    }
    else if (codigo == "7") {
        return "ARCNET";
    }
    else if (codigo == "8") {
        return "Hyperchannel";
    }
    else if (codigo == "9") {
        return "Lanstar";
    }
    else if (codigo == "10") {
        return "Autonet Short Address";
    }
    else if (codigo == "11") {
        return "LocalTalk";
    }
    else if (codigo == "12") {
        return "LocalNet (IBM PCNet or SYTEK LocalNET)";
    }
    else if (codigo == "13") {
        return "Ultra link";
    }
    else if (codigo == "14") {
        return "SMDS";
    }
    else if (codigo == "15") {
        return "Frame Relay";
    }
    else if (codigo == "16") {
        return "Asynchronous Transmission Mode (ATM)";
    }
    else if (codigo == "17") {
        return "HDLC";
    }
    else if (codigo == "18") {
        return "Fibre Channel";
    }
    else if (codigo == "19") {
        return "Asynchronous Transmission Mode (ATM)";
    }
    else if (codigo == "20") {
        return "Serial Line";
    }
    else if (codigo == "21") {
        return "Asynchronous Transmission Mode (ATM)";
    }
    else if (codigo == "22") {
        return "MIL-STD-188-220";
    }
    else if (codigo == "23") {
        return "Metricom";
    }
    else if (codigo == "24") {
        return "IEEE 1394.1995";
    }
    else if (codigo == "25") {
        return "MAPOS";
    }
    else if (codigo == "26") {
        return "Twinaxial";
    }
    else if (codigo == "27") {
        return "EUI-64";
    }
    else if (codigo == "28") {
        return "HIPARP";
    }
    else if (codigo == "29") {
        return "IP and ARP over ISO 7816-3";
    }
    else if (codigo == "30") {
        return "ARPSec";
    }
    else if (codigo == "31") {
        return "IPsec tunnel";
    }
    else if (codigo == "32") {
        return "InfiniBand (TM)";
    }
    else if (codigo == "33") {
        return "TIA-102 Project 25 Common Air Interface (CAI)";
    }
    else if (codigo == "34") {
        return "Wiegand Interface";
    }
    else if (codigo == "35") {
        return "Pure IP";
    }
    else if (codigo == "36") {
        return "HW_EXP1";
    }
    else if (codigo == "37") {
        return "HFI";
    }
    else  if (codigo == "256") {
        return "HW_EXP2";
    }
    else  if (codigo == "257") {
        return "AEthernet";
    }
    else  if (codigo == "65535") {
        return "Reserved";
    }
    std::stringstream strCode(codigo);
    int numCode = 0;
    strCode >> numCode;
    if (numCode >= 38 and numCode <= 255) {
        return "Unassigned";
    }
    else if (numCode >= 258 and numCode <= 65534) {
        return "Unassigned";
    }
    else{
        return "Hardware no encontrado.";
    }
}

void ArpRarp::setProtocolo(std::fstream& archivo) {
	int dato = 0;
	for(int i = 0; i < 2; i++) {
		std::stringstream stream;
		archivo.read((char*)&dato, 1);
		if(dato < 10) {
			stream << "0" << std::hex << dato;
		} else {
			stream << std::hex << dato;
		}
		if(i < 2 - 1) {
			stream << ":";
		}
		tipoProtocolo += stream.str();
	}
}

std::string ArpRarp::getProtocoloCadena() {
    if (tipoProtocolo == "08:00"){
        return "0800 - IPv4";
    }else if (tipoProtocolo == "08:06"){
        return "0806 - ARP";
    }else if (tipoProtocolo == "80:35"){
        return "8035 - RARP";
    }else if (tipoProtocolo == "80:dd"){
        return "80DD - Ipv6";
    }else{
        return "Tipo no encontrado.";
    }
}

std::string ArpRarp::getCodigoOperacionCadena(const std::string& codigo) {
    if (codigo == "1"){
        return "Solicitud ARP";
    }else if(codigo == "2"){
        return "Respuesta de ARP";
    }else if(codigo == "3"){
        return "Solicitud RARP";
    }else if(codigo == "4"){
        return "Respuesta de RARP";
    }else{
        return "Codigo de operacion no encontrado.";
    }
}

void ArpRarp::setDireccion(std::fstream& archivo, std::string& dir) {
	int dato = 0;
	for(int i = 0; i < DIRECCION; i++) {
		std::stringstream stream;
		archivo.read((char*)&dato, 1);
		if(dato < 10) {
			stream << "0" << std::hex << dato;
		} else {
			stream << std::hex << dato;
		}
		if(i < DIRECCION - 1) {
			stream << ":";
		}
		dir += stream.str();
	}
}

void ArpRarp::formatoIp(std::string& ip, std::fstream& archivo) {
	for(int i = 0; i < 4; i++) {
		std::string binario = hexadecimalToBinario(archivo);
		ip += std::to_string(binarioToDecimal(binario));
		if(i != 3) {
			ip += ".";
		}
	}
}
