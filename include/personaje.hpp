#ifndef PERSONAJE_HPP_WELP
#define PERSONAJE_HPP_WELP

#include "raylib.h"
#include "propiedades.hpp"
#include "pantalla.hpp"

#include <cstdint>
#include <expected>

class Personaje {
private:
	Texture textura;
	const Contexto* ctx;
	Vector2 posicion;
	bool ha_perdido;
	float velocidad;

	constexpr static Vector2 sprite_offsets[] = {{0, 0}, {72, 0}, {144, 0}};
	size_t sprite_actual;

	Personaje();
	Personaje(Texture tx, const Contexto* cx);

public:
	static constexpr std::int32_t velocidad_inicial = 0;
	static constexpr std::int32_t velocidad_salto = 400;
	static constexpr std::int32_t velocidad_absoluta_maxima = 400;
	static constexpr Vector2 posicion_inicial = {100.0f, Pantalla::alto / 2.0f};

	Personaje(const Personaje&) = delete;
	Personaje(Personaje&& p);
	auto operator=(const Personaje&) = delete;
	auto operator=(Personaje&& p) -> Personaje&;

	static auto crear(const Contexto* ctx) -> std::expected<Personaje, ValorError>;
	auto actualizar() -> void;
	auto dibujar() -> void;
	auto reiniciar() -> void;

	auto rect() -> Rectangle;
	auto indicar_que_perdio() -> void;
	auto perdio() -> bool;

	~Personaje();
};

#endif

