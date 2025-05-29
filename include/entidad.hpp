#ifndef ENTIDAD_HPP_WELP
#define ENTIDAD_HPP_WELP

#include <variant>
#include <concepts>

#include "personaje.hpp"
#include "pantalla.hpp"
#include "administrador_tuberia.hpp"

template <typename Derivado>
concept Renderizable = requires (const Derivado& D) {
	{ D.actualizar() } -> std::same_as<void>;
	{ D.dibujar() } -> std::same_as<void>;
	{ D.reiniciar() } -> std::same_as<void>;
};

using Entidad = std::variant<Personaje, Pantalla, AdministradorTuberia>;

auto actualizar(Entidad& ent) -> void;
auto dibujar(Entidad& ent) -> void;
auto reiniciar(Entidad& ent) -> void;

#endif
