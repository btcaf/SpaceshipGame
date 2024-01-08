#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <d2d1.h>
#include <string>
#pragma comment(lib, "d2d1.lib")

class Spaceship {
public:
	Spaceship();
	Spaceship(ID2D1HwndRenderTarget* d2d_render_target, const std::wstring &path);
	Spaceship(const Spaceship& other);
	Spaceship(Spaceship&& other) noexcept;
	Spaceship& operator=(const Spaceship& other);
	Spaceship& operator=(Spaceship&& other) noexcept;
	~Spaceship();
	D2D1_POINT_2F get_front() const;
	void draw();
private:
	void update();
	ID2D1HwndRenderTarget* d2d_render_target = nullptr;
	ID2D1Bitmap* spaceship_bitmap = nullptr;
	D2D1_POINT_2F position = { 0.0f, 0.0f };
	const float aspect_ratio = 717.0f / 416.0f;
	const float spaceship_height = 100.0f;
	const float speed = 5.0f;
	float front = 300.0f / 416.0f;
};

#endif // SPACESHIP_H