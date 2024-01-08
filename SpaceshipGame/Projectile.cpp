#include "Projectile.h"
#include "util.h"

Projectile::Projectile() {}

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
				position, D2D1::Point2F(0, 0), gradient_radius_x, gradient_radius_y
			),
			rad_stops,
			&rad_brush
		));
	}

	position.x = _position.x;
	position.y = _position.y;
}

Projectile::Projectile(const Projectile& other) {
	d2d_render_target = other.d2d_render_target;
	position = other.position;
}

Projectile::Projectile(Projectile&& other) noexcept {
	d2d_render_target = other.d2d_render_target;
	position = other.position;
	other.d2d_render_target = nullptr;
}

Projectile& Projectile::operator=(const Projectile& other) {
	d2d_render_target = other.d2d_render_target;
	position = other.position;
	return *this;
}

Projectile& Projectile::operator=(Projectile&& other) noexcept {
	d2d_render_target = other.d2d_render_target;
	position = other.position;
	other.d2d_render_target = nullptr;
	return *this;
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

	d2d_render_target->FillEllipse(
		D2D1::Ellipse(
			D2D1::Point2F(0.0f, 0.0f),
			gradient_radius_x,
			gradient_radius_y
		),
		rad_brush
	);

	d2d_render_target->SetTransform(
		D2D1::Matrix3x2F::Identity()
	);
}

bool Projectile::isOutOfBounds() const {
	return position.x > d2d_render_target->GetSize().width + gradient_radius_x;
}

void Projectile::update() {
	position.x += speed;
}