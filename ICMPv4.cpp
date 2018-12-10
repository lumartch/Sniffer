#include "ICMPv4.h"

ICMPv4::ICMPv4() {
	this->mensajeError = "";
	this->mensajeInformativo = "";
}

ICMPv4::ICMPv4(const std::string& archivo) {
	ICMPv4();
	abrirArchivo(archivo);
}

void ICMPv4::abrirArchivo(const std::string& archivo) {
	std::fstream fin(archivo);
	if(fin.good()) {
		fin.seekg(INICIOICMPV4, std::ios::beg);
		setMensajeInformativo(fin);
		setMensajeError(fin);
		setChecksum(fin);
	}
	fin.close();
}

void ICMPv4::setMensajeInformativo(std::fstream& archivo) {
	int type = 0;
	archivo.read((char*)&type, BITS1);
	if (type == 0) {
		this->mensajeInformativo = "Respuesta de eco";
	} else if(type == 3) {
		this->mensajeInformativo = "Destino inaccesible";
	} else if(type == 4) {
		this->mensajeInformativo = "Disminución del tráfico desde el origen";
	} else if(type == 5) {
		this->mensajeInformativo = "Redireccionar - Cambio de ruta";
	} else if(type == 8) {
		this->mensajeInformativo = "Solicitud de eco";
	} else if(type == 11) {
		this->mensajeInformativo = "Tiempo excedido para un datagrama";
	} else if(type == 12) {
		this->mensajeInformativo = "Problema de parámetros";
	} else if(type == 13) {
		this->mensajeInformativo = "Solicitud de marca de tiempo";
	} else if(type == 14) {
		this->mensajeInformativo = "Respuesta de marca de tiempo";
	} else if(type == 15) {
		this->mensajeInformativo = "Solicitud de información";
	} else if(type == 16) {
		this->mensajeInformativo = "Respuesta de información";
	} else if(type == 17) {
		this->mensajeInformativo = "Solicitud de máscara de dirección";
	} else if(type == 18) {
		this->mensajeInformativo = "Repuesta de máscara de dirección";
	}
}

void ICMPv4::setMensajeError(std::fstream& archivo) {
	int code = 0;
	archivo.read((char*)&code, BITS1);
	if (code == 0) {
		this->mensajeError = "No se puede llegar a la red ";
	} else if(code == 1) {
		this->mensajeError = "No se puede llegar al host o aplicación de destino ";
	} else if(code == 2) {
		this->mensajeError = "El destino no dispone del protocolo solicitado ";
	} else if(code == 3) {
		this->mensajeError = "No se puede llegar al puerto destino o la aplicación destino no está libre ";
	} else if(code == 4) {
		this->mensajeError = "Se necesita aplicar fragmentación, pero el flag correspondiente indica lo contrario";
	} else if(code == 5) {
		this->mensajeError = "La ruta de origen no es correcta ";
	} else if(code == 6) {
		this->mensajeError = "No se conoce la red destino ";
	} else if(code == 7) {
		this->mensajeError = "No se conoce el host destino ";
	} else if(code == 8) {
		this->mensajeError = "El host origen está aislado ";
	} else if(code == 9) {
		this->mensajeError = "La comunicación con la red destino está prohibida por razones administrativas ";
	} else if(code == 10) {
		this->mensajeError = "La comunicación con el host destino está prohibida por razones administrativas ";
	} else if(code == 11) {
		this->mensajeError = "No se puede llegar a la red destino debido al Tipo de servicio";
	} else if(code == 12) {
		this->mensajeError = "No se puede llegar al host destino debido al Tipo de servicio ";
	}
}

void ICMPv4::setChecksum(std::fstream& archivo) {
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

std::string ICMPv4::getMensajeInformativo() {
	return mensajeInformativo;
}

std::string ICMPv4::getMensajeError() {
	return mensajeError;
}

std::string ICMPv4::getChecksum() {
	return checksum;
}

