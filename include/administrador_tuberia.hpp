#ifndef ADMINISTRADOR_TUBERIA_HPP_WELP
#define ADMINISTRADOR_TUBERIA_HPP_WELP

#include <list>
#include <expected>
#include "tuberia.hpp"
#include "personaje.hpp"
#include "propiedades.hpp"

class AdministradorTuberia {
private:
    std::list<Tuberia> tuberias;
    Contexto* ctx;
    Personaje* personaje;
    float tiempo_ultimo_spawn;

    AdministradorTuberia(Contexto* ctx, Personaje& personaje);

public:
    AdministradorTuberia(const AdministradorTuberia&) = delete;
    auto operator=(const AdministradorTuberia&) = delete;
    AdministradorTuberia(AdministradorTuberia&&);
    auto operator=(AdministradorTuberia&&) -> AdministradorTuberia&;

    static auto crear(Contexto* ctx, Personaje& personaje) -> std::expected<AdministradorTuberia, ValorError>;

    auto actualizar() -> void;
	auto dibujar() -> void;
	auto reiniciar() -> void;

    auto detener() -> void;
    auto reanudar() -> void;

private:
    auto generar_tuberia() -> void;
    auto chequear_colisiones() -> void;
};

#endif