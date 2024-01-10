#include "Star.h"
#include "util.h"

Star::Star(ID2D1HwndRenderTarget* _d2d_render_target) {
	d2d_render_target = _d2d_render_target;
	D2D1_GRADIENT_STOP rad_stops_data[2];

	rad_stops_data[0] = {
		.position = 0.0f, .color = inner_color
	};
	rad_stops_data[1] = {
		.position = 1.0f, .color = outer_color
	};

	hr_check(d2d_render_target->CreateGradientStopCollection(
		rad_stops_data, 2, &rad_stops
	));

	if (rad_stops) {
		hr_check(d2d_render_target->CreateRadialGradientBrush(
			D2D1::RadialGradientBrushProperties(
				D2D1::Point2F(0, 0), D2D1::Point2F(0, 0), gradient_radius, gradient_radius
			),
			rad_stops,
			&rad_brush
		));
	}

	position.x = rand_float(0.0f, d2d_render_target->GetSize().width);
	position.y = rand_float(0.0f, d2d_render_target->GetSize().height);
}

Star::~Star() {
	if (rad_stops) rad_stops->Release();
	if (rad_brush) rad_brush->Release();
}

void Star::draw() {
	update();

	d2d_render_target->SetTransform(
		D2D1::Matrix3x2F::Translation(
			position.x,
			position.y
		)
	);
	d2d_render_target->FillEllipse(
		D2D1::Ellipse(
			D2D1::Point2F(0.0f, 0.0f), 
			gradient_radius, 
			gradient_radius
		),
		rad_brush
	);
	d2d_render_target->SetTransform(
		D2D1::Matrix3x2F::Identity()
	);

}

void Star::update() {
	position.x -= speed;
	if (position.x < -gradient_radius) {
		position.x = d2d_render_target->GetSize().width + gradient_radius;
		position.y = rand_float(0.0f, d2d_render_target->GetSize().height);
	}
}