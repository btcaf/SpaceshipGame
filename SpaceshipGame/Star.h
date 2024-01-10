#ifndef STAR_H
#define STAR_H

#include <d2d1_3.h>
#pragma comment(lib, "d2d1.lib")

class Star {
public:
	Star(ID2D1HwndRenderTarget* _d2d_render_target);
	~Star();
	void draw();
private:
	void update();
	ID2D1GradientStopCollection* rad_stops = nullptr;
	ID2D1RadialGradientBrush* rad_brush = nullptr;
	ID2D1HwndRenderTarget* d2d_render_target = nullptr;
	D2D1_POINT_2F position;
	const float speed = 0.2f;

	const float gradient_radius = 2.0f;
	const D2D1_COLOR_F inner_color = D2D1::ColorF(
		1.0f, 1.0f, 1.0f, 1.0f
	);
	const D2D1_COLOR_F outer_color = D2D1::ColorF(
		1.0f, 1.0f, 1.0f, 0.0f
	);
};

#endif // STAR_H