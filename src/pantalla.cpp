#include "pantalla.hpp"

#include <utility>

Pantalla::Pantalla() : background{Texture{}} {}

Pantalla::Pantalla(Texture bg) : background(bg) {}

Pantalla::Pantalla(Pantalla&& p) : background(std::exchange(p.background, Texture{})){}

auto Pantalla::operator=(Pantalla&& p) -> Pantalla& {
    if (this != &p) {
		if (background.id > 0) {
			UnloadTexture(background);
		}

		background = std::exchange(p.background, Texture{});
	}

	return *this;
}

auto Pantalla::crear() -> std::expected<Pantalla, ValorError> {
	Texture tx = LoadTexture("assets/bg.png");
	if (tx.id <= 0) {
		return std::unexpected(ValorError::ERROR_EN_CREACION);
	}

	Pantalla p(tx);
	return p;
}

auto Pantalla::actualizar() -> void {}

auto Pantalla::dibujar() -> void {
	DrawTexture(background, 0, 0, WHITE);
}

auto Pantalla::reiniciar() -> void {}

Pantalla::~Pantalla() {
	if (background.id > 0) {
		UnloadTexture(background);
	}
} 
