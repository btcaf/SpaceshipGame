#include "Spaceship.h"
#include "util.h"

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

void Spaceship::draw() {
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