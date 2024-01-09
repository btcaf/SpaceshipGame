#include "util.h"

#include <wincodec.h>
#include <string>

void hr_check(HRESULT hr) {
	if (FAILED(hr)) {
		exit(1);
	}
}

float rand_float(float low, float high) {
	return low + static_cast<float> (rand()) / (static_cast<float> (RAND_MAX) / (high - low));
}

int rand_int(int low, int high) {
	return rand() % (high - low + 1) + low;
}

bool check_collision(D2D1_RECT_F rect1, D2D1_RECT_F rect2) {
	return rect1.left < rect2.right && rect1.right > rect2.left && rect1.top < rect2.bottom && rect1.bottom > rect2.top;
}

ID2D1Bitmap* load_bitmap(ID2D1RenderTarget* render_target, const std::wstring& path) {
	IWICImagingFactory* wic_factory = nullptr;
	hr_check(CoCreateInstance(
		CLSID_WICImagingFactory, 
		nullptr, 
		CLSCTX_INPROC_SERVER, 
		IID_PPV_ARGS(&wic_factory))
	);

	IWICBitmapDecoder* wic_decoder = nullptr;
	hr_check(wic_factory->CreateDecoderFromFilename(path.c_str(),
		nullptr, 
		GENERIC_READ, 
		WICDecodeMetadataCacheOnLoad, 
		&wic_decoder)
	);

	IWICBitmapFrameDecode* wic_frame = nullptr;
	hr_check(wic_decoder->GetFrame(0, &wic_frame));

	IWICFormatConverter* wic_converter = nullptr;
	hr_check(wic_factory->CreateFormatConverter(&wic_converter));

	hr_check(wic_converter->Initialize(wic_frame,
		GUID_WICPixelFormat32bppPBGRA, 
		WICBitmapDitherTypeNone, 
		nullptr, 
		0.0f, 
		WICBitmapPaletteTypeMedianCut)
	);

	ID2D1Bitmap* bitmap = nullptr;
	hr_check(render_target->CreateBitmapFromWicBitmap(
		wic_converter, 
		nullptr, 
		&bitmap)
	);

	wic_converter->Release();
	wic_frame->Release();
	wic_decoder->Release();
	wic_factory->Release();

	return bitmap;
}