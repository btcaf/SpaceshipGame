#include "util.h"

void hr_check(HRESULT hr) {
	if (FAILED(hr)) {
		exit(1);
	}
}