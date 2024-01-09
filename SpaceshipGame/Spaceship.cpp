#include "Spaceship.h"
#include "util.h"

#include <cmath>

Spaceship::Spaceship(ID2D1HwndRenderTarget* _d2d_render_target, const std::wstring& path) {
	d2d_render_target = _d2d_render_target;
	spaceship_bitmap = load_bitmap(d2d_render_target, path);
	position.y = d2d_render_target->GetSize().height / 2 - height / 2;
	width = height * spaceship_bitmap->GetSize().width / spaceship_bitmap->GetSize().height;
}

Spaceship::~Spaceship() {
	if (spaceship_bitmap) spaceship_bitmap->Release();
}

D2D1_POINT_2F Spaceship::get_front() const {
	return D2D1::Point2F(
		position.x + width,
		position.y + front * height
	);
}

D2D1_RECT_F Spaceship::get_hitbox() const {
	return D2D1::RectF(
		0.9 * position.x + 0.1 * (position.x + width),
		0.9 * position.y + 0.1 * (position.y + height),
		0.9 * (position.x + width) + 0.1 * position.x,
		0.9 * (position.y + height) + 0.1 * position.y
	);
}

void Spaceship::draw() {
	update();
	d2d_render_target->DrawBitmap(
		spaceship_bitmap,
		D2D1::RectF(
			position.x,
			position.y,
			position.x + width,
			position.y + height
		),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR
	);
}

void Spaceship::update() {
	float x_change = 0.0f;
	float y_change = 0.0f;
	if (GetAsyncKeyState(VK_RIGHT) < 0 && position.x + width < d2d_render_target->GetSize().width)
		x_change += 1.0f;
	if (GetAsyncKeyState(VK_LEFT) < 0 && position.x > 0)
		x_change -= 1.0f;
	if (GetAsyncKeyState(VK_UP) < 0 && position.y > 0)
		y_change -= 1.0f;
	if (GetAsyncKeyState(VK_DOWN) < 0 && position.y + height < d2d_render_target->GetSize().height)
		y_change += 1.0f;

	if (x_change) {
		position.x += x_change / sqrt(x_change * x_change + y_change * y_change) * speed;
	}
	if (y_change) {
		position.y += y_change / sqrt(x_change * x_change + y_change * y_change) * speed;
	}
}