#include "raylib.h"
#include <cstdint>
#include <clocale>
#include <string_view>
#include <print>

#include "pantalla.hpp"
#include "rng.hpp"
#include "juego.hpp"

using std::int32_t, std::int16_t, std::int64_t;

#if defined(__MINGW64__) || defined(__MINGW32__)
    constexpr std::string_view peru_spanish = "Spanish_Peru.utf8";
#else
	constexpr std::string_view peru_spanish = "es_PE.utf8";
#endif

auto locale_error() -> void {
	using namespace std::string_view_literals;
    if constexpr (!peru_spanish.compare("es_PE.utf8"sv)) {
		std::println("{} locale not available, changing to system's default", "es_PE.utf8"sv);
	} else {
		std::println("{} locale not available, changing to system's default", peru_spanish);
	}
}


auto main() -> int {
	char* result = std::setlocale(LC_ALL, peru_spanish.data());
	if (result == nullptr) {
		locale_error();
		std::setlocale(LC_ALL, "");
    }

	init_rng();

	constexpr int32_t width = 800;
	constexpr int32_t height = 600;

	InitWindow(Pantalla::ancho, Pantalla::alto, "welp");

	{
		Juego juego;
	}

	CloseWindow();

	return 0;
}
