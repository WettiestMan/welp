#include "entidad.hpp"

auto actualizar(Entidad& ent) -> void {
	std::visit([](auto& e){
		    static_assert(Renderizable<decltype(e)>, "¡Hey, el tipo que pasaste requiere de tener un método actualizar() definido!");
			e.actualizar();
		}, ent);
}

auto dibujar(Entidad& ent) -> void {
	std::visit([](auto& e){
			static_assert(Renderizable<decltype(e)>, "¡Hey, el tipo que pasaste requiere de tener un método dibujar() definido!");
			e.dibujar();
		}, ent);
}

auto reiniciar(Entidad& ent) -> void {
	std::visit([](auto& e){
			static_assert(Renderizable<decltype(e)>, "¡Hey, el tipo que pasaste requiere de tener un método reiniciar() definido!");
			e.reiniciar();
		}, ent);
}
