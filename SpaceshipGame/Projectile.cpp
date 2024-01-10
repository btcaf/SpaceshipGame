#include "Projectile.h"
#include "util.h"

Projectile::Projectile(ID2D1HwndRenderTarget* _d2d_render_target, D2D1_POINT_2F _position) {
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
				D2D1::Point2F(0, 0), D2D1::Point2F(0, 0), gradient_radius_x, gradient_radius_y
			),
			rad_stops,
			&rad_brush
		));
	}

	position.x = _position.x;
	position.y = _position.y;
}

Projectile::~Projectile() {
	if (rad_stops) rad_stops->Release();
	if (rad_brush) rad_brush->Release();
}

void Projectile::draw() {
	update();

	d2d_render_target->SetTransform(
		D2D1::Matrix3x2F::Translation(
			position.x,
			position.y
		)
	);
	if (!exploding) {
		d2d_render_target->FillEllipse(
			D2D1::Ellipse(
				D2D1::Point2F(0.0f, 0.0f),
				gradient_radius_x,
				gradient_radius_y
			),
			rad_brush
		);
	}
	else {
		d2d_render_target->FillEllipse(
			D2D1::Ellipse(
				D2D1::Point2F(0.0f, 0.0f),
				explosion_radius,
				explosion_radius
			),
			rad_brush
		);
	}
	

	d2d_render_target->SetTransform(
		D2D1::Matrix3x2F::Identity()
	);
}

// the hitbox is the circumscribed rectangle
D2D1_RECT_F Projectile::get_hitbox() const {
	return D2D1::RectF(
		position.x - gradient_radius_x,
		position.y - gradient_radius_y,
		position.x + gradient_radius_x,
		position.y + gradient_radius_y
	);
}

void Projectile::explode() {
	exploding = true;
	if (rad_brush) rad_brush->Release();
	rad_brush = nullptr;
	if (rad_stops) {
		hr_check(d2d_render_target->CreateRadialGradientBrush(
			D2D1::RadialGradientBrushProperties(
				D2D1::Point2F(0, 0), 
				D2D1::Point2F(0, 0),
				max_explosion_radius,
				max_explosion_radius
			),
			rad_stops,
			&rad_brush
		));
	}
}

bool Projectile::is_exploding() const {
	return exploding;
}

bool Projectile::is_out_of_bounds() const {
	return (position.x > d2d_render_target->GetSize().width + gradient_radius_x) ||
		explosion_finished;
}

void Projectile::update() {
	if (!exploding) {
		position.x += speed;
	}
	else {
		explosion_radius += explosion_speed;
		if (explosion_radius > max_explosion_radius) {
			explosion_finished = true;
		}
	}
}