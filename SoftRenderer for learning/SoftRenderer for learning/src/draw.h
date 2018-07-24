#pragma once
#include"vertex.h"
#include"color.h"

class Draw {

public:
	
	static void drawline(color **mat, int x0, int y0, int xe, int ye, int w, int h);              //   Bresenham
	static void drawline(color **mat, const vertex &v1, const vertex &v2, int w, int h, bool enable_depth_test = false);
	static void drawlines(color **mat, const vertex v[],const int length, int w, int h, bool enable_depth_test = false);              // a common function to draw several lines
	static void draw_triangle(color **mat, const vertex v[3], int w, int h, bool enable_depth_test = false);
	static void draw_triangles(color **mat, const vertex v[], const int length, int w, int h, bool enable_depth_test = false);
	static void draw_adjacent_triangles(color **mat, const vertex v[], const int length, int w, int h, bool enable_depth_test = false);

	static float interp_num(float n1,float n2,float p);
	static float interp_line(float x1, float y1, float x2, float y2, float tx, float ty);
};