#include "administrador_tuberia.hpp"
#include <algorithm>
#include <utility>
#include "raylib.h"
#include "rng.hpp"
#include <cstdint>

static std::uniform_int_distribution<std::int64_t> gap_distribution(100, 400);

static auto revisar_colision(const Rectangle& a, const Rectangle& b) -> bool {
    return (
        a.x < b.x + b.width &&
        a.x + a.width > b.x &&
        a.y < b.y + b.height &&
        a.y + a.height > b.y
    );
}

AdministradorTuberia::AdministradorTuberia(Contexto* ctx, Personaje& personaje)
    : ctx(ctx), personaje(&personaje), tiempo_ultimo_spawn(0.0f) {}

AdministradorTuberia::AdministradorTuberia(AdministradorTuberia&& at)
    : tuberias(std::move(at.tuberias)),
        ctx(std::exchange(at.ctx, nullptr)),
        personaje(std::exchange(at.personaje, nullptr)),
        tiempo_ultimo_spawn(at.tiempo_ultimo_spawn) {}

auto AdministradorTuberia::operator=(AdministradorTuberia&& at) -> AdministradorTuberia& {
    if (this != &at) {
        tuberias = std::move(at.tuberias);
        ctx = std::exchange(at.ctx, nullptr);
        personaje = std::exchange(at.personaje, nullptr);
        tiempo_ultimo_spawn = at.tiempo_ultimo_spawn;
    }
    return *this;
}

auto AdministradorTuberia::crear(Contexto* ctx, Personaje& personaje) -> std::expected<AdministradorTuberia, ValorError> {
    if (ctx == nullptr) return std::unexpected(ValorError::ARGUMENTO_INVALIDO);
    
    return AdministradorTuberia(ctx, personaje);
}

auto AdministradorTuberia::actualizar() -> void {
    if (!personaje->perdio()) {
        reanudar();
    }

    tiempo_ultimo_spawn += GetFrameTime();

    const auto personaje_x = personaje->rect().x;

    for (auto& t : tuberias){
        t.actualizar();
        if (!t.fue_pasada() && personaje_x > t.get_x() + Tuberia::ancho) {
            t.marcar_pasada();
            ctx->puntos++;
        }
    }

    tuberias.erase(
        std::remove_if(tuberias.begin(), tuberias.end(), [](const Tuberia& t){ return t.fuera_de_pantalla(); }),
        tuberias.end()
    );

    if (tiempo_ultimo_spawn > 2.0f && !personaje->perdio()) {
        generar_tuberia();
        tiempo_ultimo_spawn = 0.0f;
    }
    chequear_colisiones();
}

auto AdministradorTuberia::dibujar() -> void {
    for (auto& t : tuberias) t.dibujar();
}

auto AdministradorTuberia::reiniciar() -> void {
    tuberias.clear();
    tiempo_ultimo_spawn = 0.0f;
}

auto AdministradorTuberia::generar_tuberia() -> void {
    float gap_y = producir_numero_rnd(gap_distribution);
    float gap_altura = 200.0f;
    auto tuberia = Tuberia::crear(800, gap_y, gap_altura);
    if (tuberia) tuberias.push_back(*tuberia);
}

auto AdministradorTuberia::chequear_colisiones() -> void {
    Rectangle pj_rect = personaje->rect();
    for (auto& t : tuberias) {
        if (revisar_colision(pj_rect, t.rect_arriba()) || revisar_colision(pj_rect, t.rect_abajo())) {
            personaje->indicar_que_perdio();
            detener();
            break;
        }
    }
}

auto AdministradorTuberia::detener() -> void {
    for (auto& t : tuberias) {
        t.detener();
    }
}

auto AdministradorTuberia::reanudar() -> void {
    for (auto& t : tuberias) {
        t.reanudar();
    }
}