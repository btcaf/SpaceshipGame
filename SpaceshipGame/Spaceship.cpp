#include "Spaceship.h"
#include "util.h"

#include <cmath>

Spaceship::Spaceship() {}

Spaceship::Spaceship(ID2D1HwndRenderTarget* _d2d_render_target, const std::wstring& path) {
	d2d_render_target = _d2d_render_target;
	spaceship_bitmap = load_bitmap(d2d_render_target, path);
	position.y = d2d_render_target->GetSize().height / 2;
}

Spaceship::Spaceship(const Spaceship& other) {
	d2d_render_target = other.d2d_render_target;
	spaceship_bitmap = other.spaceship_bitmap;
	position = other.position;
}

Spaceship::Spaceship(Spaceship&& other) noexcept {
	d2d_render_target = other.d2d_render_target;
	spaceship_bitmap = other.spaceship_bitmap;
	position = other.position;
	other.d2d_render_target = nullptr;
	other.spaceship_bitmap = nullptr;
}

Spaceship& Spaceship::operator=(const Spaceship& other) {
	d2d_render_target = other.d2d_render_target;
	spaceship_bitmap = other.spaceship_bitmap;
	position = other.position;
	return *this;
}

Spaceship& Spaceship::operator=(Spaceship&& other) noexcept {
	d2d_render_target = other.d2d_render_target;
	spaceship_bitmap = other.spaceship_bitmap;
	position = other.position;
	other.d2d_render_target = nullptr;
	other.spaceship_bitmap = nullptr;
	return *this;
}

Spaceship::~Spaceship() {
	if (spaceship_bitmap) spaceship_bitmap->Release();
}

D2D1_POINT_2F Spaceship::get_front() const {
	return D2D1::Point2F(
		position.x + spaceship_height * aspect_ratio,
		position.y - spaceship_height / 2 + front * spaceship_height
	);
}

void Spaceship::draw() {
	update();
	d2d_render_target->DrawBitmap(
		spaceship_bitmap,
		D2D1::RectF(
			position.x, 
			position.y - spaceship_height / 2, 
			position.x + spaceship_height * aspect_ratio,
			position.y + spaceship_height / 2
		),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR
	);
}

void Spaceship::update() {
	float x_change = 0.0f;
	float y_change = 0.0f;
	if (GetAsyncKeyState(VK_RIGHT) < 0)
		x_change += 1.0f;
	if (GetAsyncKeyState(VK_LEFT) < 0)
		x_change -= 1.0f;
	if (GetAsyncKeyState(VK_UP) < 0)
		y_change -= 1.0f;
	if (GetAsyncKeyState(VK_DOWN) < 0)
		y_change += 1.0f;

	if (x_change) {
		position.x += x_change / sqrt(x_change * x_change + y_change * y_change) * speed;
	}
	if (y_change) {
		position.y += y_change / sqrt(x_change * x_change + y_change * y_change) * speed;
	}
}