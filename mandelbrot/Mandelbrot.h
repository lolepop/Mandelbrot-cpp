#pragma once
#include <complex>

#define MAXITER 1000

double mandelbrot(std::complex<double> c, std::complex<double> z=0, int depth=0) // recursively get number of iterations
{
	if (depth < MAXITER && abs(z) <= 2)
		return mandelbrot(c, z*z+c, depth + 1);

	return depth + 1 - log2(log(abs(z))); // https://en.wikipedia.org/wiki/Mandelbrot_set#Continuous_(smooth)_coloring
}

struct // colour palette stolen from https://stackoverflow.com/questions/16500656/which-color-gradient-is-used-to-color-mandelbrot-in-wikipedia
{
	Colour colourMap[16];

	void create()
	{
		colourMap[0] = Colour::set(66, 30, 15);
		colourMap[1] = Colour::set(25, 7, 26);
		colourMap[2] = Colour::set(9, 1, 47);
		colourMap[3] = Colour::set(4, 4, 73);
		colourMap[4] = Colour::set(0, 7, 100);
		colourMap[5] = Colour::set(12, 44, 138);
		colourMap[6] = Colour::set(24, 82, 177);
		colourMap[7] = Colour::set(57, 125, 209);
		colourMap[8] = Colour::set(134, 181, 229);
		colourMap[9] = Colour::set(211, 236, 248);
		colourMap[10] = Colour::set(241, 233, 191);
		colourMap[11] = Colour::set(248, 201, 95);
		colourMap[12] = Colour::set(255, 170, 0);
		colourMap[13] = Colour::set(204, 128, 0);
		colourMap[14] = Colour::set(153, 87, 0);
		colourMap[15] = Colour::set(106, 52, 3);
	}

	Colour get(int m)
	{
		return colourMap[m % 16];
	}

} MandelbrotColours;