#ifndef PROPIEDADES_HPP_WELP
#define PROPIEDADES_HPP_WELP

#include <string_view>

namespace entorno {
	constexpr float gravedad = 15;
}

struct Contexto {
	double puntos;
	double record;
};

enum class ValorError {
	OK,
	ERROR_DESCONOCIDO,
	ARCHIVO_NO_ENCONTRADO,
	ERROR_EN_CREACION,
	ARGUMENTO_INVALIDO
};

auto error_str(ValorError err) -> std::string_view; 
#endif
