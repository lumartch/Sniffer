#include "ipv6.h"

IpV6::IpV6() {
    this->version = "";
    this->trafico = "";
    this->etiqueta = "";
    this->tamanioDatos = "";
    this->sigCabecera = "";
    this->limSalto = "";
    this->dirOrigen = "";
    this->dirDestino = "";
    this->datos = "";
}

IpV6::IpV6(const std::string& archivo) {
    IpV6();
    abrirArchivo(archivo);
}

void IpV6::abrirArchivo(const std::string& archivo) {
    std::fstream fin(archivo);
    if(fin.good()) {
        fin.seekg(INICIOIPV6, std::ios::beg);
        // Lee version y clase
        std::string binario = hexadecimalToBinario(fin);
        this->version = std::to_string(binarioToDecimal(separarBinario(binario, BITS0, BITS4)));

        binario += hexadecimalToBinario(fin);
        this->trafico = tipoTrafico(separarBinario(binario, BITS4, BITS8));

        //Lee Etiqueta
        int num = binarioToDecimal(separarBinario(binario, BITS12, BITS16));
        std::stringstream stream;
        stream << std::hex << num;
        for(int i = 0; i < 2; i++) {
            fin.read((char*)&num, BYTE);
            if(num < 10) {
                stream << "0" << std::hex << num;
            } else {
                stream << std::hex << num;
            }
        }
        this->etiqueta = stream.str();

        // Lee el tamaño de datos
        binario = hexadecimalToBinario(fin);
        binario += hexadecimalToBinario(fin);
        this->tamanioDatos = std::to_string(binarioToDecimal(separarBinario(binario, BITS0, BITS16)));

        // Lee siguiente cabecera -
        binario = hexadecimalToBinario(fin);
        this->sigCabecera = determinarCabecera(binario);
        std::cout  << std::endl << binario;

        // Lee limite de salto
        binario = hexadecimalToBinario(fin);
        this->limSalto = std::to_string(binarioToDecimal(separarBinario(binario, BITS0, BITS8)));

        // Lee Direccion de origen 128
        for(int i = 1; i <= 16; i++) {
            int dato = 0;
            std::stringstream stream;
            fin.read((char*)&dato, 1);
            if(dato < 10) {
                stream << "0" << std::hex << dato;
            } else {
                stream << std::hex << dato;
            }
            if(i%2 == 0 and i != 16) {
                stream << ":";
            }
            this->dirOrigen += stream.str();
        }

        // Lee Direccion destino
        for(int i = 1; i <= 16; i++) {
            int dato = 0;
            std::stringstream stream;
            fin.read((char*)&dato, 1);
            if(dato < 10) {
                stream << "0" << std::hex << dato;
            } else {
                stream << std::hex << dato;
            }
            if(i%2 == 0 and i != 16) {
                stream << ":";
            }
            this->dirDestino += stream.str();
        }


        //Lee datos
        int cont = 1;
        while(!fin.eof()) {
            if(fin.eof()) {
                break;
            }
            int dato = 0;
            std::stringstream stream;
            fin.read((char*)&dato, 1);
            if(dato < 10) {
                stream << "0" << std::hex << dato;
            } else {
                stream << std::hex << dato;
            }
            if(cont%2 == 0) {
                stream << ":";
            }
            this->datos += stream.str();
            cont++;
        }
    }
    fin.close();
}

std::string IpV6::getVersion() {
    return version;
}

std::string IpV6::getTrafico() {
    return trafico;
}

std::string IpV6::getEtiqueta() {
    return etiqueta;
}

std::string IpV6::getTamanioDatos() {
    return tamanioDatos;
}

std::string IpV6::getSigCabecera() {
    return sigCabecera;
}

std::string IpV6::getLimSalto() {
    return limSalto;
}

std::string IpV6::getDirOrigen() {
    return dirOrigen;
}

std::string IpV6::getDirDestino() {
    return dirDestino;
}

std::string IpV6::getDatos() {
    return datos;
}

int IpV6::binarioToDecimal(const std::string& bin) {
    int res = 0;
    for(unsigned int i = 0, j = bin.length() - 1; i < bin.length(); i++, j--) {
        if(bin[i] == '1') {
            res += pow(2, j);
        }
    }
    return res;
}

std::string IpV6::hexadecimalToBinario(std::fstream& archivo) {
    int res = 0;
    archivo.read((char*)&res, BYTE);
    std::string bin = std::bitset<8>(res).to_string(), myRes;
    return bin;
}

std::string IpV6::separarBinario(const std::string& bin, const int& limInf, const int& limSup) {
    std::string res = "";
    for(int i = limInf; i < limSup; i++) {
        res += bin[i];
    }
    return res;
}

std::string IpV6::tipoTrafico(const std::string& bin) {
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


std::string IpV6::determinarCabecera(const std::string& bin) {
    int protocol = binarioToDecimal(bin);
    std::string res = "";
    if(protocol == 58) {
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
