#include "Animation.h"
#include "Background.h"
#include "Spaceship.h"
#include "util.h"

#include <ctime>
#include <cstdlib>
#include <d2d1_3.h>
#pragma comment(lib, "d2d1.lib")

namespace {
    ID2D1Factory7* d2d_factory = nullptr;
    ID2D1HwndRenderTarget* d2d_render_target = nullptr;
    Background background;
    Spaceship spaceship;

    D2D1_COLOR_F const clear_color = {
        .r = 0.0f, .g = 0.0f, .b = 0.0f, .a = 1.0f
    };

    void init_d2d(HWND hwnd) {
        hr_check(D2D1CreateFactory(
            D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2d_factory
        ));

        RECT rc;
        GetClientRect(hwnd, &rc);

        hr_check(d2d_factory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(
                hwnd,
                D2D1::SizeU(
                    static_cast<UINT32>(rc.right) -
                    static_cast<UINT32>(rc.left),
                    static_cast<UINT32>(rc.bottom) -
                    static_cast<UINT32>(rc.top)
                )
            ),
            &d2d_render_target
        ));
    }
}


void paint(HWND hwnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    if (!d2d_render_target) {
        srand(static_cast<unsigned> (time(0)));
        init_d2d(hwnd);
        hr_check(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED));
        background = Background(d2d_render_target);
        spaceship = Spaceship(d2d_render_target, L"assets/spaceship.png");
    }

    d2d_render_target->BeginDraw();
    d2d_render_target->Clear(clear_color);

    background.draw();
    spaceship.draw();

    hr_check(d2d_render_target->EndDraw());

    EndPaint(hwnd, &ps);
}

void timer() {

}

void destroy() {
    if (d2d_render_target) d2d_render_target->Release();
    if (d2d_factory) d2d_factory->Release();
}