#include "BitmapConfig.h"
#include "util.h"

namespace {
	std::wstring spaceship_path = L"assets/spaceship.png";

	constexpr size_t asteroid_type_count = 4;

	std::wstring asteroid_paths[asteroid_type_count] = {
		L"assets/asteroid1.png",
		L"assets/asteroid2.png",
		L"assets/asteroid3.png",
		L"assets/asteroid4.png"
	};
}

std::wstring get_spaceship_path() {
	return spaceship_path;
}

std::wstring get_random_asteroid_path() {
	return asteroid_paths[rand_int(0, asteroid_type_count - 1)];
}