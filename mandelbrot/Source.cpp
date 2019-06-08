#include "Image.h"
#include "Mandelbrot.h"

#define WIDTH 1920
#define HEIGHT 1080

// parallel loops require at least c++17

int main()
{
	double RS = -2, RE = 1, IS = -1, IE = 1; // real and imaginary bounds of complex plane from wikipedia 
	double CR = 0.16125, CI = 0.638438; // center coords
	//double CR = 0, CI = 0;
	double zoom = 10; // zoom factor

	Colour* pixels = new Colour[WIDTH * HEIGHT];
	
	MandelbrotColours.create();

	concurrency::parallel_for(0, HEIGHT, [&](int y) {
		concurrency::parallel_for(0, WIDTH, [&](int x) {

			// (x + 1)/WIDTH between 0 and 1
			std::complex<double> c(CR + ((double)(x + 1) / WIDTH - .5) * ((RE - RS) / zoom), CI + ((double)(y + 1) / HEIGHT - .5) * ((IE - IS) / zoom));

			double m = mandelbrot(c);

			Colour c1 = MandelbrotColours.get(floor(m));
			Colour c2 = MandelbrotColours.get(ceil(m));

			pixels[pointToIndex(x, y, WIDTH)] = Colour::lerp(c1, c2, fmod(m, 1)); // linear interpolation of 2 nearest colours (still has weird splotches but better than a fixed cutoff)

		});
	});

	writeImg(WIDTH, HEIGHT, pixels);

}
