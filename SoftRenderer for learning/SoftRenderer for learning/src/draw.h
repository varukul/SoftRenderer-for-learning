#pragma once
#include"vertex.h"
#include"color.h"

namespace Draw {
	 //   Bresenham
	void drawline(color **mat, const vertex &v1, const vertex &v2, int w, int h, bool enable_depth_test = false);
	void drawlines(color **mat, const vertex v[], const int length, int w, int h, bool enable_depth_test = false);   
	
	
	void draw_triangle(color **mat, const vertex v[3], int w, int h, bool enable_depth_test = false);
	void draw_triangles(color **mat, const vertex v[], const int length, int w, int h, bool enable_depth_test = false);
	void draw_adjacent_triangles(color **mat, const vertex v[], const int length, int w, int h, bool enable_depth_test = false);
	void draw_triangle_texture(color **mat, const vertex v[3], int nx, int ny, const texture2d &texture, bool enable_depth_test);

	float interp_num(float n1, float n2, float p);
	float interp_line(float x1, float y1, float x2, float y2, float tx, float ty);
	color interpTriangleColor(const vertex &v0, const vertex &v1, const vertex &v2, int x, int y);
	color interpTriangleTexture(const vertex &v0, const vertex &v1, const vertex &v2, int x, int y, const texture2d &texture);
	
}