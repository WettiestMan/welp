#ifndef PANTALLA_HPP_WELP
#define PANTALLA_HPP_WELP

#include "raylib.h"

#include <cstdint>
#include <expected>

#include "propiedades.hpp"

class Pantalla {
public:
	constexpr static std::int32_t ancho = 800;
	constexpr static std::int32_t alto = 600;

private:
	Texture background;	
	Pantalla();
	Pantalla(Texture tx);

public:
	Pantalla(const Pantalla&) = delete;
	auto operator=(const Pantalla&) = delete;
	Pantalla(Pantalla&& p);
	auto operator=(Pantalla&& p) -> Pantalla&;

	static auto crear() -> std::expected<Pantalla, ValorError>;
	auto actualizar() -> void;
	auto dibujar() -> void;
	auto reiniciar() -> void;

	~Pantalla();
};

#endif //PANTALLA_HPP_WELP
