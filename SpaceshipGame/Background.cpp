#include "Background.h"
#include "util.h"

Background::Background() {
    d2d_render_target = nullptr;
}

Background::Background(ID2D1HwndRenderTarget* _d2d_render_target) {
	d2d_render_target = _d2d_render_target;
    D2D1_GRADIENT_STOP rad_stops_data[2];
    ID2D1GradientStopCollection* rad_stops = nullptr;

    rad_stops_data[0] = {
        .position = 0.0f, .color = inner_color
    };
    rad_stops_data[1] = {
        .position = 1.0f, .color = outer_color
    };

    hr_check(d2d_render_target->CreateGradientStopCollection(
        rad_stops_data, 2, &rad_stops
    ));

    D2D1_POINT_2F center = D2D1::Point2F(
        d2d_render_target->GetSize().width / 2,
        d2d_render_target->GetSize().height / 2);

    if (rad_stops) {
        hr_check(d2d_render_target->CreateRadialGradientBrush(
            D2D1::RadialGradientBrushProperties(
                center, D2D1::Point2F(0, 0), 400, 450
            ),
            rad_stops,
            &rad_brush
        ));
    }
}

Background::Background(const Background& other) {
	d2d_render_target = other.d2d_render_target;
	rad_stops = other.rad_stops;
	rad_brush = other.rad_brush;
}

Background::Background(Background&& other) noexcept {
	d2d_render_target = other.d2d_render_target;
	rad_stops = other.rad_stops;
	rad_brush = other.rad_brush;
    other.d2d_render_target = nullptr;
    other.rad_stops = nullptr;
    other.rad_brush = nullptr;
}

Background& Background::operator=(const Background& other) {
	d2d_render_target = other.d2d_render_target;
	rad_stops = other.rad_stops;
	rad_brush = other.rad_brush;
	return *this;
}

Background& Background::operator=(Background&& other) noexcept {
	d2d_render_target = other.d2d_render_target;
	rad_stops = other.rad_stops;
	rad_brush = other.rad_brush;
	other.d2d_render_target = nullptr;
	other.rad_stops = nullptr;
	other.rad_brush = nullptr;
	return *this;
}

Background::~Background() {
    if (rad_stops) rad_stops->Release();
    if (rad_brush) rad_brush->Release();
}

void Background::draw() {
    d2d_render_target->FillRectangle(
		D2D1::RectF(
            0, 
            0, 
            d2d_render_target->GetSize().width, 
            d2d_render_target->GetSize().height),
		rad_brush
	);
}