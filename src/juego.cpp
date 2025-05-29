#include "raylib.h"

#include "juego.hpp"
#include "personaje.hpp"

#include <utility>
#include <cmath>

Juego::Juego() : ctx{0,0} {
	auto pantalla = Pantalla::crear();
	if (!pantalla) {
		TraceLog(LOG_ERROR, "Error al inicializar la pantalla (%s)", error_str(pantalla.error()).data());
		return;
	}

	auto personaje = Personaje::crear(&ctx);
	if (!personaje) {
		TraceLog(LOG_ERROR, "Error al inicializar el personaje (%s)", error_str(personaje.error()).data());
		return;
	}

	entidades.push_back(std::move(pantalla.value()));
	entidades.push_back(std::move(personaje.value()));
	
	auto* pptr = std::get_if<Personaje>(&*(++entidades.begin()));
	if (!pptr) {
		TraceLog(LOG_ERROR, "No se pudo obtener el personaje desde entidades");
		return;
	}

	personaje_ptr = pptr;

	auto admin = AdministradorTuberia::crear(&ctx, *personaje_ptr);
	if (!personaje) {
		TraceLog(LOG_ERROR, "Error al inicializar el administrador de tuberías (%s)", error_str(personaje.error()).data());
		return;
	}

	entidades.push_back(std::move(admin.value()));

	SetTargetFPS(60);

	game_loop();
}

auto Juego::game_loop() -> void {
	while(!WindowShouldClose()) {
		BeginDrawing();

		if (!personaje_ptr->perdio()) {
			for (auto&& entidad: entidades) {
				actualizar(entidad);
				dibujar(entidad);
			}

			if (personaje_ptr->perdio()) {
				EndDrawing();
			    continue;
		    }
		} else {
			int continuar = juego_terminado();
			EndDrawing();
			if (continuar == 1) {
				reiniciar_todo();
				continue;
			}
			else if (continuar == 2) {
				continue;
			}
			else {
				return;
			}
			
		}

		EndDrawing();
	}
}

auto Juego::juego_terminado() -> int {

	for (auto&& entidad: entidades) {
		actualizar(entidad);
		dibujar(entidad);
	}

	DrawText("Juego Terminado", 350, 250, 20, RED);
	DrawText(TextFormat("Puntos: %.0f", ctx.puntos), 350, 300, 20, WHITE);
	DrawText(TextFormat("Record: %.0f", ctx.record), 350, 330, 20, WHITE);
	DrawText("Presiona R para reiniciar o X para salir", 300, 370, 20, WHITE);

	if (IsKeyPressed(KEY_R)) {
		return 1;
	} else if (IsKeyPressed(KEY_X)) {
		return 0;
	}

	return 2;
}

auto Juego::reiniciar_todo() -> void {
	for (auto&& entidad: entidades) {
		reiniciar(entidad);
	}
	ctx.record = std::fmax(ctx.record, ctx.puntos);
	ctx.puntos = 0;
}