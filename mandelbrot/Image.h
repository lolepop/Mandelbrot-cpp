#pragma once

#include <iostream>
#include <fstream>
#include <ppl.h>

struct Colour
{
	static const int SIZE = 3;
	double r, g, b;

	static Colour set(double r, double g, double b)
	{
		Colour c;
		c.r = r;
		c.g = g;
		c.b = b;
		return c;
	}

	static Colour lerp(Colour a, Colour b, double t) // linear interpolation of 2 colours
	{
		return (b - a) * t + a;
	}

	Colour operator +(Colour o)
	{
		Colour c;
		c.r = r + o.r;
		c.g = g + o.g;
		c.b = b + o.b;
		return c;
	}

	Colour operator -(Colour o)
	{
		Colour c;
		c.r = r - o.r;
		c.g = g - o.g;
		c.b = b - o.b;
		return c;
	}

	Colour operator *(double o)
	{
		return Colour::set(r*o, g*o, b*o);
	}

};

int pointToIndex(int x, int y, int width)
{
	return y * width + x;
}

void writeImg(int width, int height, Colour arr[]) // p6 ppm format. might want a png library for large resolution renders
{
	std::ofstream image("image.ppm", std::ios_base::binary);
	image << "P6\n" << width << " " << height << "\n255\n";

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Colour p = arr[pointToIndex(x, y, width)];

			image << (char)p.r << (char)p.g << (char)p.b;
		}
	}

	image.close();

}
