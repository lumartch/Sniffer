#include "Ethernet.h"

Ethernet::Ethernet() {
    this->direccionDestino = "";
    this->direccionOrigen = "";
    this->tipoProtocolo = "";
}

std::string Ethernet::getDireccionDestino() {
    return this->direccionDestino;
}

std::string Ethernet::getDireccionOrigen() {
    return this->direccionOrigen;
}

std::string Ethernet::getTipoProtocolo() {
    return this->tipoProtocolo;
}

bool Ethernet::abrirArchivo(const std::string& archivo) {
    std::fstream fin(archivo);
    if(fin.good()) {
        setDireccion(fin, direccionDestino);
        setDireccion(fin, direccionOrigen);
        setProtocolo(fin);
        fin.close();
        return true;
    } else {
        fin.close();
        return false;
    }
}

void Ethernet::setDireccion(std::fstream& fin, std::string& dir) {
    int dato = 0;
    for(int i = 0; i < DIRECCION; i++) {
        std::stringstream stream;
        fin.read((char*)&dato, 1);
        if(dato < 10){
            stream << "0" << std::hex << dato;
        }
        else{
            stream << std::hex << dato;
        }
        if(i < DIRECCION - 1){
            stream << ":";
        }
        dir += stream.str();
    }
}

void Ethernet::setProtocolo(std::fstream& fin) {
    int dato = 0;
    for(int i = 0; i < PROTOCOLO; i++) {
        std::stringstream stream;
        fin.read((char*)&dato, 1);
        if(dato < 10){
            stream << "0" << std::hex << dato;
        }
        else{
            stream << std::hex << dato;
        }
        if(i < PROTOCOLO - 1){
            stream << ":";
        }
        tipoProtocolo += stream.str();
    }
}



