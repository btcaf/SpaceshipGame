#include "GameInfo.h"
#include "util.h"

GameInfo::GameInfo(ID2D1HwndRenderTarget* _d2d_render_target, ID2D1Factory7* d2d_factory) {
    d2d_render_target = _d2d_render_target;
    hr_check(DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(IDWriteFactory),
        reinterpret_cast<IUnknown**>(&write_factory)
    ));

    hr_check(write_factory->CreateTextFormat(
        L"Times New Roman",
        nullptr,
        DWRITE_FONT_WEIGHT_BOLD,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        font_size,
        L"en-us",
        &text_format
    ));

	text_format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);

    hr_check(d2d_render_target->CreateSolidColorBrush(text_color,
        &text_brush));

	hr_check(d2d_render_target->CreateSolidColorBrush(game_over_color,
		&game_over_brush));

	hr_check(d2d_factory->CreatePathGeometry(&path));

	hr_check(path->Open(&path_sink));

	path_sink->BeginFigure(
		D2D1::Point2F(200.0f, 300.0f),
		D2D1_FIGURE_BEGIN_FILLED
	);

	path_sink->AddLine(
		D2D1::Point2F(100.0f, 180.0f)
	);

	path_sink->AddBezier(
		D2D1::BezierSegment(
			D2D1::Point2F(30.0f, 105.0f),
			D2D1::Point2F(200.0f, 15.0f),
			D2D1::Point2F(200.0f, 155.0f)
		)
	);

	path_sink->AddBezier(
		D2D1::BezierSegment(
			D2D1::Point2F(200.0f, 15.0f),
			D2D1::Point2F(370.0f, 105.0f),
			D2D1::Point2F(300.0f, 180.0f)
		)
	);

	path_sink->AddLine(
		D2D1::Point2F(200.0f, 300.0f)
	);

	path_sink->EndFigure(D2D1_FIGURE_END_CLOSED);

	hr_check(path_sink->Close());
}

GameInfo::~GameInfo() {
    if (text_brush) text_brush->Release();
	if (game_over_brush) game_over_brush->Release();
    if (text_format) text_format->Release();
    if (write_factory) write_factory->Release();
	if (path_sink) path_sink->Release();
	if (path) path->Release();
}

void GameInfo::add_point() {
	++score;
}

void GameInfo::lose_life() {
	--lives;
}

bool GameInfo::is_game_over() const {
	return lives <= 0;
}

void GameInfo::draw() {
	std::wstring score_str = score_text + std::to_wstring(score);
    float screen_width = d2d_render_target->GetSize().width;

    d2d_render_target->DrawText(
		score_str.c_str(),
		score_str.length(),
		text_format,
		D2D1::RectF(0.0f, font_size, screen_width, 0.0f),
		text_brush
	);

	for (int i = 0; i < lives; ++i) {
		D2D1::Matrix3x2F transformation = D2D1::Matrix3x2F::Translation(
			screen_width - 320.0f - 1.2f * i * font_size,
			font_size
		);

		transformation.SetProduct(
			transformation,
			D2D1::Matrix3x2F::Scale(
				D2D1::Size(font_size / 200.0f, font_size / 200.0f),
				D2D1::Point2F(screen_width - 1.2f * i * font_size, font_size)
			)
		);

		d2d_render_target->SetTransform(transformation);

		d2d_render_target->DrawGeometry(
			path,
			text_brush,
			10.0f
		);

		d2d_render_target->FillGeometry(
			path,
			game_over_brush
		);

		d2d_render_target->SetTransform(D2D1::Matrix3x2F::Identity());
	}
}

void GameInfo::draw_endscreen() {
	text_format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	std::wstring score_str = endscreen_text2 + std::to_wstring(score);
	float screen_width = d2d_render_target->GetSize().width;
	float screen_height = d2d_render_target->GetSize().height;

    d2d_render_target->DrawText(
		endscreen_text1.c_str(),
		endscreen_text1.length(),
		text_format,
		D2D1::RectF(0.0f, screen_height / 2 - font_size, screen_width, screen_height),
		game_over_brush
	);

	d2d_render_target->DrawText(
		score_str.c_str(),
		score_str.length(),
		text_format,
		D2D1::RectF(0.0f, screen_height / 2, screen_width, screen_height / 2 + font_size),
		text_brush
	);

	d2d_render_target->DrawText(
		endscreen_text3.c_str(),
		endscreen_text3.length(),
		text_format,
		D2D1::RectF(0.0f, screen_height / 2 + font_size, screen_width, screen_height / 2 + 2 * font_size),
		text_brush
	);
}