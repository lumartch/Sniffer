#include "ipv4.h"

Ipv4::Ipv4() {
    this->version = "";
    this->longitudCabecera = "";
    this->servicio = "";
    this->desgloseDeBits = "";
    this->longitudTotal = "";
    this->identificador = "";
    this->flags = "";
    this->posicionFragmento = "";
    this->tiempoDeVida = "";
    this->tipoProtocolo = "";
    this->sumaCabecera = "";
    this->ipOrigen = "";
    this->ipDestino = "";
}

Ipv4::Ipv4(const std::string& archivo) {
    Ipv4();
    abrirArchivo(archivo);
}

void Ipv4::abrirArchivo(const std::string& archivo) {
    std::fstream fin(archivo);
    if(fin.good()) {
        fin.seekg(INICIOIPV4, std::ios::beg);
        // Versión y longitud de cabecera
        std::string binario = hexadecimalToBinario(fin);
        version = std::to_string(binarioToDecimal(separarBinario(binario, BITS0, BITS4)));
        longitudCabecera = std::to_string(binarioToDecimal(separarBinario(binario, BITS4, BITS8)) * 32);
        // Servicios y desgloce de bits
        binario = hexadecimalToBinario(fin);
        servicio = tipoServicio(separarBinario(binario, BITS0, BITS3));
        desgloseDeBits = desglozandoBits(separarBinario(binario, BITS3, BITS6));
        //  Longitud total
        binario = hexadecimalToBinario(fin);
        binario += hexadecimalToBinario(fin);
        longitudTotal = std::to_string(binarioToDecimal(binario));
        // Identificador
        binario = hexadecimalToBinario(fin);
        identificador = std::to_string(binarioToDecimal(binario));
        binario = hexadecimalToBinario(fin);
        identificador += std::to_string(binarioToDecimal(binario));
        // Flags y posición de fragmento
        binario = hexadecimalToBinario(fin);
        flags = banderasActivadas(separarBinario(binario, BITS0, BITS3));
        posicionFragmento = separarBinario(binario, BITS3, BITS8);
        binario = hexadecimalToBinario(fin);
        posicionFragmento += binario;
        posicionFragmento = std::to_string(binarioToDecimal(posicionFragmento));
        // Tiempo de vida
        binario = hexadecimalToBinario(fin);
        tiempoDeVida = std::to_string(binarioToDecimal(binario));
        // Protocolo
        binario = hexadecimalToBinario(fin);
        tipoProtocolo = determinarProtocolo(binario);
        // Suma de cabecera
        for(int i = 0; i < 2; i++) {
            int dato = 0;
            std::stringstream stream;
            fin.read((char*)&dato, 1);
            if(dato < 10) {
                stream << "0" << std::hex << dato;
            } else {
                stream << std::hex << dato;
            }
            sumaCabecera += stream.str();
        }
        // IP Origen y destino
        formatoIp(ipOrigen, fin);
        formatoIp(ipDestino, fin);
        //Datos opcionales
    }
    fin.close();
}

int Ipv4::binarioToDecimal(const std::string& bin) {
    int res = 0;
    for(unsigned int i = 0, j = bin.length() - 1; i < bin.length(); i++, j--) {
        if(bin[i] == '1') {
            res += pow(2, j);
        }
    }
    return res;
}
std::string Ipv4::hexadecimalToBinario(std::fstream&archivo) {
    int res = 0;
    archivo.read((char*)&res, BYTE);
    std::string bin = std::bitset<8>(res).to_string(), myRes;
    return bin;
}

std::string Ipv4::separarBinario(const std::string& bin, const int &limInf, const int &limSup) {
    std::string res = "";
    for(int i = limInf; i < limSup; i++) {
        res += bin[i];
    }
    return res;
}

std::string Ipv4::tipoServicio(const std::string& bin) {
    if(bin == "000") {
        return "De rutina";
    } else if(bin == "001") {
        return "Prioritario";
    } else if(bin == "010") {
        return "Inmediato";
    } else if(bin == "011") {
        return "Relámpago";
    } else if(bin == "100") {
        return "Invalidación  relámpago";
    } else if(bin == "101") {
        return "Procesando llamada crítica y de emergencia";
    } else if(bin == "110") {
        return "Control de trabajo de internet";
    } else {
        return "Control de red";
    }
}

std::string Ipv4::desglozandoBits(const std::string& bin) {
    std::string res = "Retraso: ";
    if(bin[0] == '1') {
        res += "Normal. | ";
    } else {
        res += "Bajo. | ";
    }
    res += "Rendimiento: ";
    if(bin[1] == '1') {
        res += "Normal. | ";
    } else {
        res += "Alto. | ";
    }
    res += "Fiabilidad: ";
    if(bin[2] == '1') {
        res += "Normal.";
    } else {
        res += "Alta.";
    }
    return res;
}

std::string Ipv4::banderasActivadas(const std::string& bin) {
    std::string res = "Se activo la bandera: ";
    if(bin[0] == '0') {
        res += "Reservado. | ";
    } else {
        res += "No Reservado. | ";
    }
    if(bin[1] == '0') {
        res += "Divisible. | ";
    } else {
        res += "No divisible. |";
    }
    if(bin[2] == '0') {
        res += "Ultimo fragmento.";
    } else {
        res += "Fragmento intermedio.";
    }
    return res;
}

std::string Ipv4::determinarProtocolo(const std::string& bin) {
    int protocol = binarioToDecimal(bin);
    std::string res = "";
    if(protocol == 1) {
        res += "ICMP";
    } else if(protocol == 4) {
        res += "IP";
    } else if(protocol == 6) {
        res += "TCP";
    } else if(protocol == 3) {
        res += "GGP";
    } else if(protocol == 17) {
        res += "UDP";
    }
    return res;
}

void Ipv4::formatoIp(std::string& ip, std::fstream& archivo) {
    for(int i = 0; i < 4; i++) {
        std::string binario = hexadecimalToBinario(archivo);
        ip += std::to_string(binarioToDecimal(binario));
        if(i != 3) {
            ip += ".";
        }
    }
}


std::string Ipv4::getVersion() {
    return this->version;
}

std::string Ipv4::getLongitudCabecera() {
    return this->longitudCabecera;
}

std::string Ipv4::getServicio() {
    return this->servicio;
}

std::string Ipv4::getDesgloseDeBits() {
    return this->desgloseDeBits;
}

std::string Ipv4::getLongitudTotal() {
    return this->longitudTotal;
}

std::string Ipv4::getIdentificador() {
    return this->identificador;
}

std::string Ipv4::getFlags() {
    return this->flags;
}

std::string Ipv4::getPosicionFragmento() {
    return this->posicionFragmento;
}

std::string Ipv4::getTiempoDeVida() {
    return this->tiempoDeVida;
}

std::string Ipv4::getTipoProtocolo() {
    return this->tipoProtocolo;
}

std::string Ipv4::getSumaCabecera() {
    return this->sumaCabecera;
}

std::string Ipv4::getIpOrigen() {
    return this->ipOrigen;
}

std::string Ipv4::getIpDestino() {
    return this->ipDestino;
}
