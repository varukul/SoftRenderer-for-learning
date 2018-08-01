#include"Draw.h"
#include<math.h>
#include<iostream>

float f01(vec3f v0, vec3f v1, vec3f v) {
	return (v0._y - v1._y)*v._x + (v1._x - v0._x)*v._y + v0._x*v1._y - v1._x*v0._y;
}

float f12(vec3f v1, vec3f v2, vec3f v) {
	return (v1._y - v2._y)*v._x + (v2._x - v1._x)*v._y + v1._x*v2._y - v2._x*v1._y;
}

float f20(vec3f v2, vec3f v0, vec3f v) {
	return (v2._y - v0._y)*v._x + (v0._x - v2._x)*v._y + v2._x*v0._y - v0._x*v2._y;
}

int get_min(int p1, int p2, int p3) {
	p1 = (p1 > p2) ? p2 : p1;
	p1 = (p1 > p3) ? p3 : p1;
	return p1;
}

int get_max(int p1, int p2, int p3) {
	p1 = (p1 < p2) ? p2 : p1;
	p1 = (p1 < p3) ? p3 : p1;
	return p1;
}

color Draw::interpTriangleColor(const vertex &v0, const vertex &v1, const vertex &v2,int x,int y) {
	float fa = f12(v1._pos, v2._pos, v0._pos);
	float fb = f20(v2._pos, v0._pos, v1._pos);
	float fc = f01(v0._pos, v1._pos, v2._pos);
	float a = f12(v1._pos, v2._pos, vec3f(x, y, 0)) / fa;
	float b = f20(v2._pos, v0._pos, vec3f(x, y, 0)) / fb;
	float c = f01(v0._pos, v1._pos, vec3f(x, y, 0)) / fc;
	if (a >= 0 && b >= 0 && c >= 0) {
		if (a > 0 && fa*f12(v1._pos, v2._pos, vec3f(-1, -1, 0)) &&
			b > 0 && fa*f20(v2._pos, v0._pos, vec3f(-1, -1, 0)) &&
			c > 0 && fa*f01(v0._pos, v1._pos, vec3f(-1, -1, 0))) {
			color col(v0._col*a + v1._col*b + v2._col*c);
			return col;
		}
	}
	return color(0, 0, 0);
}

color Draw::interpTriangleTexture(const vertex &v0, const vertex &v1, const vertex &v2, int x, int y,const texture2d &texture) {
	float fa = f12(v1._pos, v2._pos, v0._pos);
	float fb = f20(v2._pos, v0._pos, v1._pos);
	float fc = f01(v0._pos, v1._pos, v2._pos);
	float a = f12(v1._pos, v2._pos, vec3f(x, y, 0)) / fa;
	float b = f20(v2._pos, v0._pos, vec3f(x, y, 0)) / fb;
	float c = f01(v0._pos, v1._pos, vec3f(x, y, 0)) / fc;
	if (a >= 0 && b >= 0 && c >= 0) {
		if (a > 0 && fa*f12(v1._pos, v2._pos, vec3f(-1, -1, 0)) &&
			b > 0 && fa*f20(v2._pos, v0._pos, vec3f(-1, -1, 0)) &&
			c > 0 && fa*f01(v0._pos, v1._pos, vec3f(-1, -1, 0))) {
			textcoord tempt(v0._tc*a + v1._tc*b + v2._tc*c);
			color tcol(texture._texc[texture._height-tempt._v-1][tempt._u]);
			color col(v0._col*a + v1._col*b + v2._col*c + tcol);
			col._a = (v0._col*a + v1._col*b + v2._col*c)._a;
			return col;
		}
	}
	return color(0, 0, 0);
}

float Draw::interp_num(float n1, float n2, float p) {
	return abs(p) / abs(n2 - n1);
}

float Draw::interp_line(float x1, float y1, float x2, float y2, float tx,float ty) {
	float x = interp_num(x1, x2, tx);
	float y = interp_num(y1, y2, ty);
	return 1 - sqrt(x*x + y * y);
}

void Draw::drawline(color **mat, const vertex &vb, const vertex &ve, int nx, int ny, bool enable_depth_test) {
	int dx = abs(ve._pos._x - vb._pos._x), dy = abs(ve._pos._y - vb._pos._y);
	int sx = (ve._pos._x > vb._pos._x) ? 1 : -1;
	int sy = (ve._pos._y > vb._pos._y) ? -1 : 1;

	int x = vb._pos._x, y = ny - vb._pos._y - 1;
	bool isup = false;
	int k = dx - 1;

	int dy2 = 2 * dy;
	int dx2 = 2 * dx;
	int miuns = dy2 - dx2;
	int p = dy2 - dx;


	if (x >= 0 && x < nx && y >= 0 && y < ny) {
		mat[y][x] = vb._col;
	}
	if (dx < dy) {
		isup = true, k = dy - 1, p = dx2 - dy;
	}
	while (k > 0) {
		float t = interp_line(vb._pos._x, vb._pos._y, ve._pos._x, ve._pos._y, x, y);
		color c(vb._col*t + ve._col*(1 - t));

		if (x >= 0 && x < nx &&y >= 0 && y < ny) {
			if (enable_depth_test) {
				if (mat[y][x]._a >= c._a) {
					mat[y][x] = c;
				}
			}
			else {
				mat[y][x] = c;
			}
		}

		if (!isup) {
			if (p < 0) {
				x += sx;
				p = p + dy2;
			}
			else {
				x += sx;
				y += sy;
				p = p + miuns;
			}
		}
		else {
			if (p < 0) {
				y += sy;
				p = p + dx2;
			}
			else {
				y += sy;
				x += sx;
				p = p - miuns;
			}
		}
		k--;
	}
}

void Draw::drawlines(color **mat, const vertex v[], const int length, int w, int h, bool enable_depth_test) {
	for (int i = 0; i < length - 1; i++) {
		drawline(mat, v[i], v[i + 1], w, h, enable_depth_test);
	}
}

void Draw::draw_triangle(color **mat, const vertex v[3], int nx, int ny, bool enable_depth_test) {
	int xmin = get_min(v[0]._pos._x, v[1]._pos._x, v[2]._pos._x);
	int xmax = get_max(v[0]._pos._x, v[1]._pos._x, v[2]._pos._x);
	int ymin = get_min(v[0]._pos._y, v[1]._pos._y, v[2]._pos._y);
	int ymax = get_max(v[0]._pos._y, v[1]._pos._y, v[2]._pos._y);
	for (int i = xmin; i <= xmax; i++) {
		for (int j = ymin; j <= ymax; j++) {
			color c = interpTriangleColor(v[0], v[1], v[2], i, j);
			int temp = ny - j - 1;
			if (enable_depth_test) {
				if (mat[temp][i]._a >= c._a) {
					mat[temp][i] = c;
				}
			}
			else {
				mat[temp][i] = c;
			}
		}
	}
}

void Draw::draw_triangle_texture(color **mat, const vertex v[3], int nx, int ny, const texture2d &texture, bool enable_depth_test) {
	int xmin = get_min(v[0]._pos._x, v[1]._pos._x, v[2]._pos._x);
	int xmax = get_max(v[0]._pos._x, v[1]._pos._x, v[2]._pos._x);
	int ymin = get_min(v[0]._pos._y, v[1]._pos._y, v[2]._pos._y);
	int ymax = get_max(v[0]._pos._y, v[1]._pos._y, v[2]._pos._y);
	for (int i = xmin; i <= xmax; i++) {
		for (int j = ymin; j <= ymax; j++) {
			color c = interpTriangleTexture(v[0], v[1], v[2], i, j, texture);
			int temp = ny - j - 1;
			if (enable_depth_test) {
				if (mat[temp][i]._a >= c._a) {
					mat[temp][i] = c;
				}
			}
			else {
				mat[temp][i] = c;
			}
		}
	}
}

void Draw::draw_triangles(color **mat, const vertex v[], const int length, int w, int h, bool enable_depth_test) {
	if (length % 3 != 0) {
		std::cerr << "vertexs of triangles is not enough" << std::endl;
		return;
	}
	for (int i = 0; i < length - 2; i += 3) {
		vertex temp[3] = { v[i],v[i + 1],v[i + 2] };
		draw_triangle(mat, temp, w, h, enable_depth_test);
	}
}

void Draw::draw_adjacent_triangles(color **mat, const vertex v[], const int length, int nx, int ny, bool enable_depth_test) {
	if (length <= 2) {
		std::cerr << "vertexs of triangles is not enough" << std::endl;
		return;
	}
	for (int i = 0; i < length - 2; i++) {
		vertex temp[3] = { v[i],v[i + 1],v[2] };
		draw_triangle(mat, temp, nx, ny,enable_depth_test);
	}
}