#ifndef UTIL_H
#define UTIL_H

#include <windows.h>
#include <d2d1.h>
#include <string>

#pragma comment(lib, "d2d1.lib")

void hr_check(HRESULT hr);

ID2D1Bitmap* load_bitmap(ID2D1RenderTarget* target, const std::wstring& path);

#endif // UTIL_H