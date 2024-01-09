#ifndef ASTEROID_H
#define ASTEROID_H

#include <d2d1_3.h>
#pragma comment(lib, "d2d1.lib")

constexpr unsigned int explosion_pieces = 5;

class Asteroid {
public:
	Asteroid(ID2D1HwndRenderTarget* d2d_render_target, size_t type);
	~Asteroid();
	void draw();
	D2D1_RECT_F get_hitbox() const;
	void explode();
	bool is_exploding() const;
	bool is_out_of_bounds() const;
private:
	void update();
	ID2D1HwndRenderTarget* d2d_render_target = nullptr;
	ID2D1Bitmap* asteroid_bitmap = nullptr;
	D2D1_POINT_2F position = { 0.0f, 0.0f };
	float angle = 0.0f;
	const float min_height = 50.0f;
	const float max_height = 200.0f;
	float width;
	float height;
	const float min_speed = 4.0f;
	const float max_speed = 10.0f;
	float speed;

	bool exploding = false;
	float explosion_angles[explosion_pieces];
	D2D1_POINT_2F explosion_positions[explosion_pieces];
	float piece_angles[explosion_pieces];
	float opacity = 0.5f;
	float explosion_height;
	float explosion_width;
	const float explosion_move_speed = 8.0f;
	const float explosion_rotation_speed = 0.1f;
	const unsigned int explosion_frames = 30;
};

#endif // ASTEROID_H