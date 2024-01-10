#ifndef UTIL_H
#define UTIL_H

#include <windows.h>
#include <d2d1_3.h>
#include <string>

#pragma comment(lib, "d2d1.lib")

void hr_check(HRESULT hr);

float rand_float(float low, float high);

unsigned int rand_int(unsigned int low, unsigned int high);

bool check_collision(D2D1_RECT_F rect1, D2D1_RECT_F rect2);

ID2D1Bitmap* load_bitmap(ID2D1RenderTarget* target, const std::wstring& path);

#endif // UTIL_H