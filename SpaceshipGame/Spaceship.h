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
	void draw();
private:
	ID2D1HwndRenderTarget* d2d_render_target = nullptr;
	ID2D1Bitmap* spaceship_bitmap = nullptr;
	D2D1_POINT_2F position = { 0.0f, 0.0f };
	const float aspect_ratio = 1920.0f / 1080.0f;
	const float spaceship_height = 200.0f;
};

#endif // SPACESHIP_H