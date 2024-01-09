#include "AsteroidConfig.h"

struct AsteroidConfig {
	std::wstring path;
};

struct AsteroidConfig asteroid_config[asteroid_type_count] = {
	{ L"assets/asteroid1.png" },
	{ L"assets/asteroid2.png" },
	{ L"assets/asteroid3.png" }
};

std::wstring get_asteroid_path(size_t asteroid_type) {
	return asteroid_config[asteroid_type].path;
}