#ifndef TUBERIA_HPP_WELP
#define TUBERIA_HPP_WELP

#include "raylib.h"
#include <expected>
#include <cstdint>
#include "propiedades.hpp"

class Tuberia {
private:
    float x;
    float gap_y;
    float gap_altura;
    float velocidad;
    bool pasada = false;

    constexpr static float velocidad_inicial = 200.0f;

    Tuberia(float x, float gap_y, float gap_altura);

public:
    constexpr static float ancho = 52.0f;

    Tuberia(const Tuberia&) = default;
    auto operator=(const Tuberia&) -> Tuberia& = default;
    Tuberia(Tuberia&&) = default;
    auto operator=(Tuberia&&) -> Tuberia& = default;

    static auto crear(float x, float gap_y, float gap_altura) -> std::expected<Tuberia, ValorError>;

    auto actualizar() -> void;
    auto dibujar() -> void;
    auto reiniciar() -> void;
    auto detener() -> void;
    auto reanudar() -> void { velocidad = velocidad_inicial; }

    auto fue_pasada() const -> bool { return pasada; }
    auto marcar_pasada() -> void { pasada = true; }

    auto rect_arriba() const -> Rectangle;
    auto rect_abajo() const -> Rectangle;
    auto fuera_de_pantalla() const -> bool;
    auto get_x() const -> float { return x; }
    auto get_gap_y() const -> float { return gap_y; }
};

#endif