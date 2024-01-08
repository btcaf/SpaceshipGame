#ifndef PROJECTILE_SET_H
#define PROJECTILE_SET_H

#include "Projectile.h"
#include "Spaceship.h"

#include <vector>
#include <chrono>
#include <memory>

class ProjectileSet {
public:
	ProjectileSet(ID2D1HwndRenderTarget* _d2d_render_target, std::shared_ptr<Spaceship> _spaceship);
	void draw();
private:
	ID2D1HwndRenderTarget* d2d_render_target = nullptr;
	uint64_t time_between_shots = 500;
	std::shared_ptr<Spaceship> spaceship = nullptr;
	std::chrono::steady_clock::time_point last_shot = std::chrono::steady_clock::now();
	std::vector<std::shared_ptr<Projectile>> projectiles;
};

#endif // PROJECTILE_SET_H