#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")

class Spaceship {
public:
	Spaceship();
	Spaceship(ID2D1HwndRenderTarget* d2d_render_target);
	Spaceship(const Spaceship& other);
	Spaceship(Spaceship&& other);
	Spaceship& operator=(const Spaceship& other);
	Spaceship& operator=(Spaceship&& other);
	~Spaceship();
	void draw();
private:
	ID2D1HwndRenderTarget* d2d_render_target;
};

#endif // SPACESHIP_H