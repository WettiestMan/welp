#include "tuberia.hpp"
#include "raylib.h"
#include <expected>
#include "propiedades.hpp"
#include "pantalla.hpp"

Tuberia::Tuberia(float x, float gap_y, float gap_altura)
    : x(x), gap_y(gap_y), gap_altura(gap_altura), velocidad(velocidad_inicial) {}

auto Tuberia::crear(float x, float gap_y, float gap_altura) -> std::expected<Tuberia, ValorError> {
    return Tuberia(x, gap_y, gap_altura);
}

auto Tuberia::actualizar() -> void {
    x -= velocidad * GetFrameTime();
}

auto Tuberia::dibujar() -> void {
    DrawRectangle(x, 0, ancho, gap_y, GREEN); // Dibujar parte superior
    DrawRectangleLinesEx({x, 0, ancho, gap_y}, 2.0f, DARKGREEN); // Dibujar borde superior
    
    // Abajo
    float abajo_y = gap_y + gap_altura;
    float abajo_altura = Pantalla::alto - abajo_y;
    DrawRectangle(x, abajo_y, ancho, abajo_altura, GREEN); // Dibujar parte inferior
    DrawRectangleLinesEx({x, abajo_y, ancho, abajo_altura}, 2.0f, DARKGREEN); // Dibujar borde inferior

}

auto Tuberia::reiniciar() -> void {

}

auto Tuberia::rect_arriba() const -> Rectangle {
    return Rectangle{x, 0, ancho, gap_y};
}

auto Tuberia::rect_abajo() const -> Rectangle {
    float abajo_y = gap_y + gap_altura;
    float abajo_altura = Pantalla::alto - abajo_y;
    return Rectangle{x, abajo_y, ancho, abajo_altura};
}

auto Tuberia::fuera_de_pantalla() const -> bool {
    return x + ancho < 0;
}

auto Tuberia::detener() -> void {
    velocidad = 0.0f;
}