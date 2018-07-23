#include"Draw.h"
#include<math.h>


Draw::Draw() {

}



Draw::~Draw() {

}

void Draw::drawline(color **mat, int x0, int y0, int xe, int ye, int nx, int ny) {
	int dx = abs(xe - x0), dy = abs(ye - y0);
	int sx = (xe > x0) ? 1 : -1;
	int sy = (ye > y0) ? -1 : 1;
	/*y0 = (y0 > 0) ? y0 : 0;
	x0 = (x0 > 0) ? x0 : 0;
	y0 = (y0 < ny) ? y0 : ny - 1;
	x0 = (x0 < nx) ? x0 : nx - 1;*/

	int x = x0, y = ny - y0 - 1;
	bool isup = false;
	int k = dx - 1;

	int dy2 = 2 * dy;
	int dx2 = 2 * dx;
	int miuns = dy2 - dx2;
	int p = dy2 - dx;


	if (x >= 0 && x < nx && y >= 0 && y < ny) {
		mat[y][x] = 1;
	}
	if (dx < dy) {
		isup = true, k = dy - 1, p = dx2 - dy;
	}
	while (k > 0) {
		if (!isup) {
			if (p < 0) {
				if (x >= 0 && x < nx &&y >= 0 && y < ny) {
					mat[y][x] = 1;
				}
				x += sx;
				p = p + dy2;
			}
			else {
				if (x >= 0 && x < nx &&y >= 0 && y < ny) {
					mat[y][x] = 1;
				}
				x += sx;
				y += sy;
				p = p + miuns;
			}
		}
		else {
			if (p < 0) {
				if (x >= 0 && x < nx &&y >= 0 && y < ny) {
					mat[y][x] = 1;
				}
				y += sy;
				p = p + dx2;
			}
			else {
				if (x >= 0 && x < nx &&y >= 0 && y < ny) {
					mat[y][x] = 1;
				}
				y += sy;
				x += sx;
				p = p - miuns;
			}
		}
		k--;
	}

}

void Draw::drawline(color **mat, const vertex &vb, const vertex &ve, int nx, int ny) {
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
		mat[y][x] = 1;
	}
	if (dx < dy) {
		isup = true, k = dy - 1, p = dx2 - dy;
	}
	while (k > 0) {
		if (!isup) {
			if (p < 0) {
				if (x >= 0 && x < nx &&y >= 0 && y < ny) {
					mat[y][x] = 1;
				}
				x += sx;
				p = p + dy2;
			}
			else {
				if (x >= 0 && x < nx &&y >= 0 && y < ny) {
					mat[y][x] = 1;
				}
				x += sx;
				y += sy;
				p = p + miuns;
			}
		}
		else {
			if (p < 0) {
				if (x >= 0 && x < nx &&y >= 0 && y < ny) {
					mat[y][x] = 1;
				}
				y += sy;
				p = p + dx2;
			}
			else {
				if (x >= 0 && x < nx &&y >= 0 && y < ny) {
					mat[y][x] = 1;
				}
				y += sy;
				x += sx;
				p = p - miuns;
			}
		}
		k--;
	}

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

float f01(vec3f v0, vec3f v1, vec3f v) {
	return (v0._y - v1._y)*v._x + (v1._x - v0._x)*v._y + v0._x*v1._y - v1._x*v0._y;
}

float f12(vec3f v1, vec3f v2, vec3f v) {
	return (v1._y - v2._y)*v._x + (v2._x - v1._x)*v._y + v1._x*v2._y - v2._x*v1._y;
}

float f20(vec3f v2, vec3f v0, vec3f v) {
	return (v2._y - v0._y)*v._x + (v0._x - v2._x)*v._y + v2._x*v0._y - v0._x*v2._y;
}

void Draw::draw_triangles(color **mat, vertex v[], int nx, int ny) {
	int xmin = get_min(v[0]._pos._x, v[1]._pos._x, v[2]._pos._x);
	int xmax = get_max(v[0]._pos._x, v[1]._pos._x, v[2]._pos._x);
	int ymin = get_min(v[0]._pos._y, v[1]._pos._y, v[2]._pos._y);
	int ymax = get_max(v[0]._pos._y, v[1]._pos._y, v[2]._pos._y);
	float fa = f12(v[1]._pos, v[2]._pos, v[0]._pos);
	float fb = f20(v[2]._pos, v[0]._pos, v[1]._pos);
	float fc = f01(v[0]._pos, v[1]._pos, v[2]._pos);
	for (int y = ymin; y < ymax && y < ny && y >= 0; y++) {
		for (int x = xmin; x < xmax && x < nx && x >= 0; x++) {
			float a = f12(v[1]._pos, v[2]._pos, vec3f(x, y, 0)) / fa;
			float b = f20(v[2]._pos, v[0]._pos, vec3f(x, y, 0)) / fb;
			float c = f01(v[0]._pos, v[1]._pos, vec3f(x, y, 0)) / fc;
			if (a >= 0 && b >= 0 && c >= 0) {
				if (a > 0 && fa*f12(v[1]._pos, v[2]._pos, vec3f(-1, -1, 0)) &&
					b > 0 && fa*f20(v[2]._pos, v[0]._pos, vec3f(-1, -1, 0)) &&
					c > 0 && fa*f01(v[0]._pos, v[1]._pos, vec3f(-1, -1, 0))) {
					color c(v[0]._col*a + v[1]._col*b + v[2]._col*c);
					int temp = ny - y - 1;
					mat[temp][x] = c;
				}
			}
		}
	}
}