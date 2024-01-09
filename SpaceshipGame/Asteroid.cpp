#include "Asteroid.h"
#include "AsteroidConfig.h"
#include "util.h"

#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Asteroid::Asteroid(ID2D1HwndRenderTarget* _d2d_render_target, size_t type) {
	d2d_render_target = _d2d_render_target;
	asteroid_bitmap = load_bitmap(d2d_render_target, get_asteroid_path(type));
	height = rand_float(min_height, max_height);
	width = height * asteroid_bitmap->GetSize().width / asteroid_bitmap->GetSize().height;
	position.x = d2d_render_target->GetSize().width;
	position.y = rand_float(0.0f, d2d_render_target->GetSize().height - height);
	speed = rand_float(min_speed, max_speed);
}

Asteroid::~Asteroid() {
	if (asteroid_bitmap) asteroid_bitmap->Release();
}

void Asteroid::draw() {
	update();
	if (!exploding) {
		d2d_render_target->DrawBitmap(
			asteroid_bitmap,
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
	else {
		for (int i = 0; i < explosion_pieces; ++i) {
			d2d_render_target->SetTransform(
				D2D1::Matrix3x2F::Rotation(
					piece_angles[i]
				)
			);

			d2d_render_target->DrawBitmap(
				asteroid_bitmap,
				D2D1::RectF(
					explosion_positions[i].x,
					explosion_positions[i].y,
					explosion_positions[i].x + explosion_width,
					explosion_positions[i].y + explosion_height
				),
				opacity,
				D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR
			);

			d2d_render_target->SetTransform(
				D2D1::Matrix3x2F::Identity()
			);
		}
	}
	
}

D2D1_RECT_F Asteroid::get_hitbox() const {
	return D2D1::RectF(
		0.9 * position.x + 0.1 * (position.x + width),
		0.9 * position.y + 0.1 * (position.y + height),
		0.9 * (position.x + width) + 0.1 * position.x,
		0.9 * (position.y + height) + 0.1 * position.y
	);
}

void Asteroid::explode() {
	exploding = true;
	explosion_height = height / 2;
	explosion_width = width / 2;
	for (size_t i = 0; i < explosion_pieces; ++i) {
		explosion_angles[i] = rand_float(0.0f, 2 * M_PI);
		explosion_positions[i].x = position.x + width / 4;
		explosion_positions[i].y = position.y + height / 4;
		piece_angles[i] = rand_float(0.0f, 2 * M_PI);
	}
}

bool Asteroid::is_exploding() const {
	return exploding;
}

bool Asteroid::is_out_of_bounds() const {
	return position.x < -width;
}

void Asteroid::update() {
	if (!exploding) {
		position.x -= speed;
	} else {
		for (size_t i = 0; i < explosion_pieces; ++i) {
			piece_angles[i] += explosion_rotation_speed;
		}
		if (explosion_frames > 0) {
			opacity -= 0.5f / explosion_frames;
			explosion_width -=  0.5f * width / explosion_frames;
			explosion_height -= 0.5f * height / explosion_frames;
			for (int i = 0; i < explosion_pieces; ++i) {
				explosion_positions[i].x += explosion_move_speed * cos(explosion_angles[i]);
				explosion_positions[i].y += explosion_move_speed * sin(explosion_angles[i]);
			}
		}
		else {
			position.x = -width * 2.0f;
		}
	}
}