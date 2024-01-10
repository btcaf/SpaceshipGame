#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Star.h"

#include <vector>
#include <memory>
#include <d2d1_3.h>
#pragma comment(lib, "d2d1.lib")

class Background {
public:
	Background();
	Background(ID2D1HwndRenderTarget* d2d_render_target);
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

	const size_t star_count = 100;
	std::vector<std::shared_ptr<Star>> stars;
};

#endif // BACKGROUND_H