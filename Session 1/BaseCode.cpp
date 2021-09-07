// raycastingTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <fstream>      // std::ofstream
#include <math.h>
#include <glm/glm.hpp>
using namespace std;
using namespace glm;

#define PI 3.14159265

void step1()
{
	// Add two vectors together and output the result on the console window
	vec3 v1(1, 2, 3);
	vec3 v2(3, 4, 5);
	vec3 v3 = v1 + v2;
	cout << "v1 " << "[" << v1.x << " " << v1.y << " " << v1.z << "]" << endl;
	cout << "v2 " << "[" << v2.x << " " << v2.y << " " << v2.z << "]" << endl;
	cout << "v3 " << "[" << v3.x << " " << v3.y << " " << v3.z << "]" << endl;
}

int main()
{
	const int WIDTH = 640;
	const int HEIGHT = 480;
	float PixelNdx, PixelNdy, PixelRdx, PixelRdy, Iar, tanvalue, PCameraX,PCameraY;

	vec3 **image = new vec3*[WIDTH];
	for (int i=0; i < WIDTH; i++) image[i] = new vec3[HEIGHT];

	Iar = WIDTH / (float)HEIGHT;
	tanvalue = tanf(15.0 * PI / 180.0);
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			/*if (x < 320)
			{
				image[x][y].x = 255;
				image[x][y].y = 100;
				image[x][y].z = 0;
			}
			else
			{
				image[x][y].x = 0;
				image[x][y].y = 100;
				image[x][y].z = 255;
			}*/

			PixelNdx = (x + 0.5) / (float)WIDTH;
			PixelNdy = (y + 0.5) / (float)HEIGHT;
			PixelRdx = 2 * PixelNdx - 1.0;
			PixelRdy = 1.0 - 2 * PixelNdy;
			PixelRdx = PixelRdx * Iar;

			PCameraX = PixelRdx*tanvalue;
			PCameraY = PixelRdy*tanvalue;

			image[x][y].x = PCameraX;
			image[x][y].y = PCameraY;
			image[x][y].z = -1.0;
		}
	}


	// Save result to a PPM image
	ofstream ofs("./test.ppm", std::ios::out | std::ios::binary);
	ofs << "P6\n" << WIDTH << " " << HEIGHT << "\n255\n";
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			ofs << (unsigned char)(std::min((float)1, (float)image[x][y].x) * 255) <<
				(unsigned char)(std::min((float)1, (float)image[x][y].y) * 255) <<
				(unsigned char)(std::min((float)1, (float)image[x][y].z) * 255);
		}
	}
	ofs.close();
    return 0;
}

