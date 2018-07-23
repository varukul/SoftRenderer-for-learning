#pragma once
#include"vertex.h"
#include"color.h"

class Draw {

public:
	Draw();
	~Draw();

	static void drawline(color **mat, int x0, int y0, int xe, int ye, int nx, int ny);              //   Bresenham
	static void drawline(color **mat, const vertex &v1, const vertex &v2, int nx, int ny);
	static void draw_triangles(color **mat, vertex v[], int nx, int ny);
};