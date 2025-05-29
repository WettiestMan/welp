set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_minimum_required(VERSION 3.30)

project(welp VERSION 0.1 LANGUAGES CXX)

set(welp_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(welp_HEADERS ${CMAKE_SOURCE_DIR}/include)

add_executable(welp
	${welp_SOURCE_DIR}/main.cpp
	${welp_SOURCE_DIR}/rng.cpp
	${welp_SOURCE_DIR}/juego.cpp
	${welp_SOURCE_DIR}/pantalla.cpp
	${welp_SOURCE_DIR}/personaje.cpp
	${welp_SOURCE_DIR}/propiedades.cpp
	${welp_SOURCE_DIR}/entidad.cpp
	${welp_SOURCE_DIR}/tuberia.cpp
	${welp_SOURCE_DIR}/administrador_tuberia.cpp
)

target_compile_features(welp PRIVATE cxx_std_23)

find_package(raylib REQUIRED)

target_include_directories(welp PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(welp PRIVATE ${welp_HEADERS})
target_include_directories(welp PRIVATE ${raylib_INCLUDE_DIRS})

target_link_libraries(welp PRIVATE ${raylib_LIBRARIES})

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	target_compile_options(welp PRIVATE -fsanitize=address)
endif()

if(MINGW)
	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		target_link_libraries(welp PRIVATE -lstdc++exp)
	elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
		target_link_libraries(welp PRIVATE -lc++ -fsanitize=address)
	endif()
endif()

add_custom_target(
	copy_assets ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/assets
		${CMAKE_BINARY_DIR}/assets
)
