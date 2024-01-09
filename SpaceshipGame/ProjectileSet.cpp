#include "ProjectileSet.h"

ProjectileSet::ProjectileSet(ID2D1HwndRenderTarget* _d2d_render_target, std::shared_ptr<Spaceship> _spaceship) {
	d2d_render_target = _d2d_render_target;
	spaceship = _spaceship;
}

void ProjectileSet::getProjectiles(std::vector<std::shared_ptr<Projectile>>& _projectiles) {
	_projectiles = projectiles;
}

void ProjectileSet::draw() {
	if (GetAsyncKeyState(VK_SPACE) < 0) {
		if (std::chrono::steady_clock::now() - last_shot > std::chrono::milliseconds(time_between_shots)) {
			last_shot = std::chrono::steady_clock::now();
			projectiles.push_back(std::make_shared<Projectile>(d2d_render_target, spaceship->get_front()));
		}
	}
	for (size_t i = 0; i < projectiles.size(); ++i) {
		projectiles[i]->draw();
	}

	std::erase_if(projectiles, [](const std::shared_ptr<Projectile> projectile) { return projectile->is_out_of_bounds(); });
}