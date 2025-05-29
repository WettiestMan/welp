#ifndef JUEGO_HPP_WELP
#define JUEGO_HPP_WELP

#include "entidad.hpp"

#include <list>

class Juego {
private:
	Contexto ctx;
	std::list<Entidad> entidades;
	auto reiniciar_todo() -> void;
	auto juego_terminado() -> int;
	auto game_loop() -> void;
	Personaje* personaje_ptr;

public:
	Juego();
};

#endif
