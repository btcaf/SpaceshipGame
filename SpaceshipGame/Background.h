#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")

class Background {
public:
	Background();
	Background(ID2D1HwndRenderTarget* d2d_render_target);
	Background(const Background& other);
	Background(Background&& other) noexcept;
	Background& operator=(const Background& other);
	Background& operator=(Background&& other) noexcept;
	~Background();
	void draw();
	
private:
	ID2D1GradientStopCollection* rad_stops = nullptr;
	ID2D1RadialGradientBrush* rad_brush = nullptr;
	ID2D1HwndRenderTarget* d2d_render_target = nullptr;

	const D2D1_COLOR_F inner_color = D2D1::ColorF(
		0.0f, 0.06f, 0.53f, 1.0f
	);
	const D2D1_COLOR_F outer_color = D2D1::ColorF(
		0.0f, 0.04f, 0.41f, 1.0f
	);

	const float gradient_radius = 400.0f;
};

#endif // BACKGROUND_H