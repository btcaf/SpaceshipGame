#include "util.h"

#include <wincodec.h>
#include <string>

void hr_check(HRESULT hr) {
	if (FAILED(hr)) {
		exit(1);
	}
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