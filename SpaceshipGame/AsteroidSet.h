#ifndef ASTEROID_SET_H
#define ASTEROID_SET_H

#include "Asteroid.h"

#include <chrono>
#include <vector>
#include <memory>

class AsteroidSet {
public:
	AsteroidSet(ID2D1HwndRenderTarget* _d2d_render_target);
	void getAsteroids(std::vector<std::shared_ptr<Asteroid>> &_asteroids);
	void draw();
private:
	ID2D1HwndRenderTarget* d2d_render_target = nullptr;
	const uint64_t min_time_between_asteroids = 300;
	const uint64_t max_time_between_asteroids = 1000;
	uint64_t time_between_asteroids = 1000;
	std::chrono::steady_clock::time_point last_asteroid = std::chrono::steady_clock::now();
	std::vector<std::shared_ptr<Asteroid>> asteroids;
};

#endif // ASTEROID_SET_H