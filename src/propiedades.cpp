#include "propiedades.hpp"

auto error_str(ValorError err) -> std::string_view {
	static const std::string_view strs[]= {
		"No error",
		"Error desconocido",
		"Archivo no encontrado",
		"Error en creación",
		"Argumento inválido",
	};

	static const std::string_view str_def = "Error desconocido";

	if (static_cast<std::size_t>(err) < sizeof(strs) / sizeof(strs[0]))
	    return strs[static_cast<std::size_t>(err)];
	else
		return str_def;
}

