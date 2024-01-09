#ifndef GAME_INFO_H
#define GAME_INFO_H

#include <string>
#include <d2d1_3.h>
#include <dwrite_3.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

class GameInfo {
public:
	GameInfo(ID2D1HwndRenderTarget* _d2d_render_target, ID2D1Factory7* d2d_factory);
	~GameInfo();
	void add_point();
	void lose_life();
	bool is_game_over() const;
	void draw();
	void draw_endscreen();
private:
	ID2D1RenderTarget* d2d_render_target = nullptr;
	IDWriteFactory* write_factory = nullptr;
	ID2D1SolidColorBrush* text_brush = nullptr;
	ID2D1SolidColorBrush* game_over_brush = nullptr;
	IDWriteTextFormat* text_format = nullptr;
	ID2D1PathGeometry* path = nullptr;
	ID2D1GeometrySink* path_sink = nullptr;
	int score = 0;
	int lives = 3;
	const std::wstring score_text = L"Score: ";
	const std::wstring endscreen_text1 = L"GAME OVER";
	const std::wstring endscreen_text2 = L"Final Score: ";
	const std::wstring endscreen_text3 = L"Press Enter to Play Again";
	const float font_size = 20.0f;

	const D2D1_COLOR_F text_color = {
		.r = 0.0f, .g = 1.0f, .b = 0.0f, .a = 1.0f
	};

	const D2D1_COLOR_F game_over_color = {
		.r = 1.0f, .g = 0.0f, .b = 0.0f, .a = 1.0f
	};

};

#endif // GAME_INFO_H