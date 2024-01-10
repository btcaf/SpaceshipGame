#include "Animation.h"
#include "Background.h"
#include "Spaceship.h"
#include "ProjectileSet.h"
#include "AsteroidSet.h"
#include "GameInfo.h"
#include "util.h"

#include <ctime>
#include <cstdlib>
#include <d2d1_3.h>
#include <memory>
#pragma comment(lib, "d2d1.lib")

namespace {
    ID2D1Factory7* d2d_factory = nullptr;
    ID2D1HwndRenderTarget* d2d_render_target = nullptr;
    std::shared_ptr<Background> background = nullptr;
    std::shared_ptr<GameInfo> game_info = nullptr;
    std::shared_ptr<Spaceship> spaceship = nullptr;
    std::shared_ptr<ProjectileSet> projectile_set = nullptr;
    std::shared_ptr<AsteroidSet> asteroid_set = nullptr;
    bool new_game = true;

    D2D1_COLOR_F const clear_color = {
        .r = 0.0f, .g = 0.0f, .b = 0.0f, .a = 1.0f
    };

    void init_d2d(HWND hwnd) {
        hr_check(D2D1CreateFactory(
            D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2d_factory
        ));

        RECT rc;
        GetClientRect(hwnd, &rc);

        hr_check(d2d_factory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(
                hwnd,
                D2D1::SizeU(
                    static_cast<UINT32>(rc.right) -
                    static_cast<UINT32>(rc.left),
                    static_cast<UINT32>(rc.bottom) -
                    static_cast<UINT32>(rc.top)
                )
            ),
            &d2d_render_target
        ));
    }

    void check_collisions() {
        std::vector<std::shared_ptr<Projectile>> projectiles;
		projectile_set->getProjectiles(projectiles);
		std::vector<std::shared_ptr<Asteroid>> asteroids;
		asteroid_set->getAsteroids(asteroids);

        for (size_t i = 0; i < projectiles.size(); ++i) {
            for (size_t j = 0; j < asteroids.size(); ++j) {
                if (projectiles[i]->is_exploding() || 
                        asteroids[j]->is_exploding()) {
                    continue;
                }
                if (check_collision(projectiles[i]->get_hitbox(),
                        asteroids[j]->get_hitbox())) {
					game_info->add_point();
                    asteroids[j]->explode();
                    projectiles[i]->explode();
				}
			}
		}

        for (size_t i = 0; i < asteroids.size(); ++i) {
            if (asteroids[i]->is_exploding()) {
                continue;
            }
            if (check_collision(asteroids[i]->get_hitbox(),
                    spaceship->get_hitbox())) {
                asteroids[i]->explode();
				game_info->lose_life();
			}
		}
    }
}


void paint(HWND hwnd) {
    PAINTSTRUCT ps;
    if (BeginPaint(hwnd, &ps) == nullptr) {
        exit(1);
    }

    if (!d2d_render_target) {
        srand(static_cast<unsigned> (time(0)));
        init_d2d(hwnd);
        hr_check(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED));
    }

    if (new_game) {
        background = std::make_shared<Background>(d2d_render_target);
        spaceship = std::make_shared<Spaceship>(d2d_render_target);
        projectile_set = std::make_shared<ProjectileSet>(d2d_render_target, 
            spaceship);
        asteroid_set = std::make_shared<AsteroidSet>(d2d_render_target);
        game_info = std::make_shared<GameInfo>(d2d_render_target, d2d_factory);
        new_game = false;
    }

    d2d_render_target->BeginDraw();
    d2d_render_target->Clear(clear_color);

    if (!game_info->is_game_over()) {
        background->draw();
        asteroid_set->draw();
        projectile_set->draw();
        spaceship->draw();
        game_info->draw();
        check_collisions();
    } else {
        game_info->draw_endscreen();
        if (GetAsyncKeyState(VK_RETURN) < 0) {
			new_game = true;
		}
    }

    hr_check(d2d_render_target->EndDraw());

    EndPaint(hwnd, &ps);
}

void destroy() {
    if (d2d_render_target) d2d_render_target->Release();
    if (d2d_factory) d2d_factory->Release();
}