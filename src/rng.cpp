#include "rng.hpp"

#include <random>
#include <cstdint>
#include <chrono>

using wall_clock = std::chrono::system_clock;

thread_local std::mt19937_64 rng;

auto init_rng() -> void {
	rng.seed(wall_clock::to_time_t(wall_clock::now()));
}

auto producir_numero_rnd_default() -> std::int64_t {
	thread_local auto rango = std::uniform_int_distribution<std::int64_t>{0};
	return rango(rng);
}

auto producir_numero_rnd(std::uniform_int_distribution<std::int64_t>& rango) -> std::int64_t {
	return rango(rng);
}

