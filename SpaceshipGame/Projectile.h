#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")

class Projectile {
public:
	Projectile();
	Projectile(ID2D1HwndRenderTarget* d2d_render_target, D2D1_POINT_2F position);
	Projectile(const Projectile& other);
	Projectile(Projectile&& other) noexcept;
	Projectile& operator=(const Projectile& other);
	Projectile& operator=(Projectile&& other) noexcept;
	~Projectile();
	void draw();
	bool isOutOfBounds() const;
private:
	void update();
	ID2D1GradientStopCollection* rad_stops = nullptr;
	ID2D1RadialGradientBrush* rad_brush = nullptr;
	ID2D1HwndRenderTarget* d2d_render_target = nullptr;
	D2D1_POINT_2F position = { 0.0f, 0.0f };
	const float speed = 20.0f;

	const D2D1_COLOR_F inner_color = D2D1::ColorF(
		0.0f, 1.0f, 1.0f, 1.0f
	);
	const D2D1_COLOR_F outer_color = D2D1::ColorF(
		0.0f, 1.0f, 1.0f, 0.0f
	);

	const float gradient_radius_x = 50.0f;
	const float gradient_radius_y = 5.0f;
};

#endif // PROJECTILE_H