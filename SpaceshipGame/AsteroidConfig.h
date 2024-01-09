#ifndef ASTEROID_CONFIG_H
#define ASTEROID_CONFIG_H

#include <string>

constexpr size_t asteroid_type_count = 3;

std::wstring get_asteroid_path(size_t asteroid_type);

#endif // ASTEROID_CONFIG_H