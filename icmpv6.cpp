#include "icmpv6.h"

ICMPv6::ICMPv6() {
    this->codigo = "";
    this->tipo = "";
    this->checksum = "";
}


ICMPv6::ICMPv6(const std::string& archivo) {
    ICMPv6();
    abrirArchivo(archivo);
}

void ICMPv6::abrirArchivo(const std::string& archivo) {
    std::fstream fin(archivo);
    if(fin.good()) {
        fin.seekg(INICIOICMPV6, std::ios::beg);
        setTipoCodigo(fin);
    }
    fin.close();
}

void ICMPv6::setTipoCodigo(std::fstream& archivo) {
    int type = 0, code = 0;
    archivo.read((char*)&type, BITS1);
    archivo.read((char*)&code, BITS1);
    if(type == 1){
        this->tipo = "Destino inaccesible";
        if(code == 0){
            this->codigo = "No existe ruta destino";
        }
        else if(code == 1){
            this->codigo = "Comunicación con el destino administrativamente prohibida";
        }
        else if(code == 2){

            this->codigo = "No asignado";
        }
        else if(code == 3){
            this->codigo = "Dirección inalcanzable";

        }
        else if(code == 4){
            this->codigo = "Puerto inalcanzable";

        }
    }
    else if(type == 2){
        this->tipo = "Paquete demasiado grande";
    }
    else if(type == 3){
        this->tipo = "Tiempo excedido";
        if(code == 0){
            this->codigo = "Limite de saltos excedido";
        }
        else {
            this->codigo = "Tiempo excedido en el reensable del paquete";
        }
    }
    else if(type == 4){
        this->tipo = "Problema de parametros";

    }
    else if(type == 128){
        this->tipo = "Solicitud eco";
        if(code == 0){
            this->codigo = "Error en el campo de encabezado";
        }
        else if(code == 1){
            this->codigo = "Tipo de siguiente encabezado desconocido";
        }
        else if(code == 2){

            this->codigo = "Opción IPv6 desconocida";
        }
    }
    else if(type == 129){
        this->tipo = "Respuesta eco";

    }
}

void ICMPv6::setChecksum(std::fstream& archivo) {
    for(int i = 0; i < 2; i++) {
        int dato = 0;
        std::stringstream stream;
        archivo.read((char*)&dato, BITS1);
        if(dato < 10) {
            stream << "0" << std::hex << dato;
        } else {
            stream << std::hex << dato;
        }
        checksum += stream.str();
    }
}

std::string ICMPv6::getTipo() {
    return tipo;
}

std::string ICMPv6::getCodigo() {
    return codigo;
}

std::string ICMPv6::getChecksum() {
    return checksum;
}


