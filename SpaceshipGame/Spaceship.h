#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <d2d1_3.h>
#include <string>
#pragma comment(lib, "d2d1.lib")

class Spaceship {
public:
	Spaceship(ID2D1HwndRenderTarget* d2d_render_target);
	~Spaceship();
	D2D1_POINT_2F get_front() const;
	D2D1_RECT_F get_hitbox() const;
	void draw();
private:
	void update();
	ID2D1HwndRenderTarget* d2d_render_target = nullptr;
	ID2D1Bitmap* spaceship_bitmap = nullptr;
	D2D1_POINT_2F position = { 0.0f, 0.0f };
	float width;
	const float height = 100.0f;
	const float speed = 5.0f;
	float front = 300.0f / 416.0f;
	const float hitbox_scale = 0.8f;
};

#endif // SPACESHIP_H