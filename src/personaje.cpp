#include "personaje.hpp"
#include "propiedades.hpp"
#include <cstring>
#include <utility>
#include <algorithm>

Personaje::Personaje() : textura{},
   	ctx{nullptr},
   	posicion{posicion_inicial},
   	ha_perdido{false},
    velocidad{(float)velocidad_inicial},
    sprite_actual(0) {}

Personaje::Personaje(Texture tx, const Contexto* cx) : textura{tx},
	ctx{cx},
	posicion{posicion_inicial},
	ha_perdido{false},
    velocidad{(float)velocidad_inicial},
    sprite_actual(0) {}

Personaje::Personaje(Personaje&& p) : 
	textura{std::exchange(p.textura, Texture{})},
    ctx{std::exchange(p.ctx, nullptr)},
	posicion{p.posicion},
	ha_perdido{p.ha_perdido},
	velocidad{p.velocidad},
	sprite_actual(p.sprite_actual)
{}

auto Personaje::operator=(Personaje&& p) -> Personaje& {
	if (this != &p) {
		if (textura.id > 0) {
			UnloadTexture(textura);
		}

		textura = std::exchange(p.textura, Texture{});
		ctx = std::exchange(p.ctx, nullptr);
		posicion = p.posicion;
		ha_perdido = p.ha_perdido;
		velocidad = p.velocidad;
		sprite_actual = p.sprite_actual;
	}

	return *this;
}

auto Personaje::crear(const Contexto* ctx) -> std::expected<Personaje, ValorError> {
	if (ctx == nullptr) {
		return std::unexpected(ValorError::ARGUMENTO_INVALIDO);
	}
	
	Texture tx = LoadTexture("assets/character_sprites.png");
	if (tx.id <= 0) {
		return std::unexpected(ValorError::ERROR_EN_CREACION);
	}

	Personaje p(tx, ctx);
	return p;
}

auto Personaje::actualizar() -> void {
	const auto delta = GetFrameTime();

	velocidad += entorno::gravedad;

	if (!ha_perdido && IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		velocidad = -velocidad_salto;
	}

	velocidad = std::clamp(velocidad, (float)-velocidad_absoluta_maxima, (float)velocidad_absoluta_maxima);

	sprite_actual = (velocidad < 0) ? 0 : 1;
	if (ha_perdido)
		sprite_actual = 2;
	
	posicion.y += velocidad * delta;

	if (posicion.y < 0) {
		posicion.y = 0;
		velocidad = 0;
	} else if (posicion.y + 72 > Pantalla::alto) {
		indicar_que_perdio();
		posicion.y = Pantalla::alto - 72;
		velocidad = 0;
	}
}

auto Personaje::dibujar() -> void {
	const auto& offset = sprite_offsets[sprite_actual];
    const float ancho = 72.0f;
    const float alto = ha_perdido ? -72.0f : 72.0f;

    const auto fuente = Rectangle{
        offset.x,
        ha_perdido ? offset.y + textura.height : offset.y,
        ancho,
        alto
    };

	DrawTexturePro(textura, fuente, rect(), {0, 0}, 0, WHITE); 
	DrawRectangleLinesEx(rect(), 2, BLACK); // Dibujar borde del personaje
}

auto Personaje::reiniciar() -> void {
	this->ha_perdido = false;
	this->posicion = posicion_inicial;
	this->velocidad = velocidad_inicial;
	this->sprite_actual = 0;
}

auto Personaje::rect() -> Rectangle {
    return {posicion.x, posicion.y, 72, 72};
}

auto Personaje::indicar_que_perdio() -> void {
	ha_perdido = true;
}

auto Personaje::perdio() -> bool {
	return ha_perdido;
}

Personaje::~Personaje() {
	if (textura.id > 0) {
		UnloadTexture(textura);
	}
}
