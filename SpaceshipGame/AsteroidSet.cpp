#include "AsteroidSet.h"
#include "AsteroidConfig.h"
#include "util.h"

AsteroidSet::AsteroidSet(ID2D1HwndRenderTarget* _d2d_render_target) {
	d2d_render_target = _d2d_render_target;
}

void AsteroidSet::getAsteroids(std::vector<std::shared_ptr<Asteroid>>& _asteroids) {
	_asteroids = asteroids;
}

void AsteroidSet::draw() {
	if (std::chrono::steady_clock::now() - last_asteroid > std::chrono::milliseconds(time_between_asteroids)) {
		last_asteroid = std::chrono::steady_clock::now();
		time_between_asteroids = rand_int(min_time_between_asteroids, max_time_between_asteroids);
		asteroids.push_back(std::make_shared<Asteroid>(d2d_render_target, rand_int(0, asteroid_type_count - 1)));
	}

	for (size_t i = 0; i < asteroids.size(); ++i) {
		asteroids[i]->draw();
	}

	std::erase_if(asteroids, [](const std::shared_ptr<Asteroid> asteroid) { return asteroid->is_out_of_bounds(); });
}