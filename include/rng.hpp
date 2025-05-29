#ifndef RNG_HPP_WELP
#define RNG_HPP_WELP

#include <random>
#include <cstdint>

/**
 * @brief Inicializa un generador de números aleatorios alimentado con
 * el tiempo actual.
 * 
 * La inicialización es por hilo, cada vez que se desee usar las funciones
 * de este encabezado en un hilo, es necesario llamar init_rng dentro de ese hilo
 */
auto init_rng() -> void;
auto producir_numero_rnd(std::uniform_int_distribution<std::int64_t>& range) -> std::int64_t;
auto producir_numero_rnd_default() -> std::int64_t;

#endif
