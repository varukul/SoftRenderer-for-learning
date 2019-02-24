#include"Draw.h"
#include<math.h>
#include<vector>
#include<iostream>

float f01(const vec4f& v0, const vec4f& v1, const vec4f& v) {
	return (v0.y() - v1.y())*v.x() + (v1.x() - v0.x())*v.y() + v0.x()*v1.y() - v1.x()*v0.y();
}

float f12(const vec4f& v1, const vec4f& v2, const vec4f& v) {
	return (v1.y() - v2.y())*v.x() + (v2.x() - v1.x())*v.y() + v1.x()*v2.y() - v2.x()*v1.y();
}

float f20(const vec4f& v2, const vec4f& v0, const vec4f& v) {
	return (v2.y() - v0.y())*v.x() + (v0.x() - v2.x())*v.y() + v2.x()*v0.y() - v0.x()*v2.y();
}

float get_min(float p1, float p2, float p3) {
	p1 = (p1 > p2) ? p2 : p1;
	p1 = (p1 > p3) ? p3 : p1;
	return p1;
}

float get_max(float p1, float p2, float p3) {
	p1 = (p1 < p2) ? p2 : p1;
	p1 = (p1 < p3) ? p3 : p1;
	return p1;
}

color Draw::interpTriangleColor(const vertex &v0,
	const vertex &v1,
	const vertex &v2,
	float x,
	float y,
	const LightGroup& LG,
	const MaterialGroup& MG) {
	float fa = f12(v1._pos, v2._pos, v0._pos);
	float fb = f20(v2._pos, v0._pos, v1._pos);
	float fc = f01(v0._pos, v1._pos, v2._pos);
	float a = f12(v1._pos, v2._pos, vec4f(x, y, 0)) / fa;
	float b = f20(v2._pos, v0._pos, vec4f(x, y, 0)) / fb;
	float c = f01(v0._pos, v1._pos, vec4f(x, y, 0)) / fc;
	if (a >= 0 && b >= 0 && c >= 0) {
		if (a > 0 && fa*f12(v1._pos, v2._pos, vec4f(-1, -1, 0)) &&
			b > 0 && fa*f20(v2._pos, v0._pos, vec4f(-1, -1, 0)) &&
			c > 0 && fa*f01(v0._pos, v1._pos, vec4f(-1, -1, 0))) {
			float depthInterp = v0._pos.z()*a + v1._pos.z()*b + v2._pos.z()*c;
			vec3f pos = v0._posW*a + v1._posW*b + v2._posW*c;
			vec3f normal = v0._normal*a + v1._normal*b + v2._normal*c;
			vec3f toEye = (LG.Eye - pos).normalize();
			vec3f shadowFactor(1.0f);
			color col = ComputeLighting(LG, MG.materials[MG.useIdx], pos, normal, toEye, shadowFactor).xyz();       //光源
			vec3f ambientLight = LG.ambientLight*MG.materials[MG.useIdx].DiffuseAlbedo.xyz();                       //环境光
			col = col + ambientLight;
			col._a = depthInterp;
			return col;
		}
	}
	return color(0, 0, 0);
}

color Draw::interpTriangleTexture(const vertex &v0, const vertex &v1, const vertex &v2, float x, float y,const texture2d &texture) {
	float fa = f12(v1._pos, v2._pos, v0._pos);
	float fb = f20(v2._pos, v0._pos, v1._pos);
	float fc = f01(v0._pos, v1._pos, v2._pos);
	float a = f12(v1._pos, v2._pos, vec4f(x, y, 0)) / fa;
	float b = f20(v2._pos, v0._pos, vec4f(x, y, 0)) / fb;
	float c = f01(v0._pos, v1._pos, vec4f(x, y, 0)) / fc;
	if (a >= 0 && b >= 0 && c >= 0) {
		if (a > 0 && fa*f12(v1._pos, v2._pos, vec4f(-1, -1, 0)) &&
			b > 0 && fa*f20(v2._pos, v0._pos, vec4f(-1, -1, 0)) &&
			c > 0 && fa*f01(v0._pos, v1._pos, vec4f(-1, -1, 0))) {
			//透视纹理矫正
			float iz = (a / v0._pos.w()) + (b / v1._pos.w()) + (c / v2._pos.w());
			int u = ((v0._tc._u *a / v0._pos.w() + v1._tc._u *b / v1._pos.w() + v2._tc._u *c / v2._pos.w())* (texture._width - 1) / iz + 0.5f) ;
			int v = ((v0._tc._v *a / v0._pos.w() + v1._tc._v *b / v1._pos.w() + v2._tc._v *c / v2._pos.w())* (texture._height - 1) / iz + 0.5f) ;
			u = u >= texture._width ? texture._width - 1 : u;
			v = v >= texture._height ? texture._height - 1 : v;
			textcoord texcord(u, v);
			//textcoord texcord((v0._tc*a + v1._tc*b + v2._tc*c));     //普通线性插值
			return color(texture._texc[texture._height - texcord._v - 1][texcord._u]);
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

//void Draw::drawline(std::vector<std::vector<color>>& mat, const vertex &vb, const vertex &ve, int nx, int ny, bool enable_depth_test) {
//	int dx = (int)abs(ve._pos.x() - vb._pos.x()), dy = (int)abs(ve._pos.y() - vb._pos.y());
//	int sx = (ve._pos.x() > vb._pos.x()) ? 1 : -1;
//	int sy = (ve._pos.y() > vb._pos.y()) ? -1 : 1;
//
//	int x = vb._pos.x(), y = ny - vb._pos.y() - 1;
//	bool isup = false;
//	int k = dx - 1;
//
//	int dy2 = 2 * dy;
//	int dx2 = 2 * dx;
//	int miuns = dy2 - dx2;
//	int p = dy2 - dx;
//
//
//	if (x >= 0 && x < nx && y >= 0 && y < ny) {
//		mat[y][x] = vb._col;
//	}
//	if (dx < dy) {
//		isup = true, k = dy - 1, p = dx2 - dy;
//	}
//	while (k > 0) {
//		float t = interp_line(vb._pos.x(), vb._pos.y(), ve._pos.x(), ve._pos.y(), x, y);
//		color c(vb._col*t + ve._col*(1 - t));
//
//		if (x >= 0 && x < nx &&y >= 0 && y < ny) {
//			if (enable_depth_test) {
//				if (mat[y][x]._a >= c._a) {
//					mat[y][x] = c;
//				}
//			}
//			else {
//				mat[y][x] = c;
//			}
//		}
//
//		if (!isup) {
//			if (p < 0) {
//				x += sx;
//				p = p + dy2;
//			}
//			else {
//				x += sx;
//				y += sy;
//				p = p + miuns;
//			}
//		}
//		else {
//			if (p < 0) {
//				y += sy;
//				p = p + dx2;
//			}
//			else {
//				y += sy;
//				x += sx;
//				p = p - miuns;
//			}
//		}
//		k--;
//	}
//}
//
//void Draw::drawlines(std::vector<std::vector<color>>& mat, const vertex v[], const int length, int w, int h, bool enable_depth_test) {
//	for (int i = 0; i < length - 1; i++) {
//		drawline(mat, v[i], v[i + 1], w, h, enable_depth_test);
//	}
//}

void Draw::draw_triangle(std::vector<std::vector<color>>& mat,
	const std::vector<vertex>& vertices,
	const std::vector<uint16_t>& indices,
	const texture2d *texture,
	const LightGroup& LG,
	const MaterialGroup& MG,
	bool enable_depth_test) {
	int nx = mat[0].size();
	int ny = mat.size();
	float xmin = get_min(vertices[indices[0]]._pos.x(), vertices[indices[1]]._pos.x(), vertices[indices[2]]._pos.x());
	float xmax = get_max(vertices[indices[0]]._pos.x(), vertices[indices[1]]._pos.x(), vertices[indices[2]]._pos.x());
	float ymin = get_min(vertices[indices[0]]._pos.y(), vertices[indices[1]]._pos.y(), vertices[indices[2]]._pos.y());
	float ymax = get_max(vertices[indices[0]]._pos.y(), vertices[indices[1]]._pos.y(), vertices[indices[2]]._pos.y());
	for (int i = (xmin>0?xmin:0); i < (xmax>nx?nx:xmax); i++) {
		for (int j = (ymin>0?ymin:0); j < (ymax>ny?ny:ymax); j++) {
			color texC;
			if (texture) {
				texC = interpTriangleTexture(vertices[indices[0]], vertices[indices[1]], vertices[indices[2]], i, j, *texture);
			}
			color c = interpTriangleColor(vertices[indices[0]], vertices[indices[1]], vertices[indices[2]], i, j, LG, MG);  //do lighting calculation
			int temp = ny - j - 1;
			if (enable_depth_test) {
				if (mat[temp][i]._a > c._a) {
					mat[temp][i] = c + texC;
					mat[temp][i]._a = c._a;
				}
			}
			else {
				mat[temp][i] = c + texC;
			}
		}
	}
}
//
//void Draw::draw_triangles(std::vector<std::vector<color>>& mat,
//	const std::vector<vertex>& vertices,
//	const texture2d *texture,
//	bool enable_depth_test) {
//	for (uint32_t i = 0; i < vertices.size(); i += 3) {
//		draw_triangle(mat, vertices, std::vector<uint16_t>{uint16_t(i), uint16_t(i + 1), uint16_t(i + 2)},texture ,enable_depth_test);
//	}
//}
//
//void Draw::draw_adjacent_triangles(std::vector<std::vector<color>>& mat,
//	const std::vector<vertex>& vertices,
//	const texture2d *texture,
//	bool enable_depth_test) {
//	for (uint32_t i = 0; i < vertices.size(); i++) {
//		draw_triangle(mat, vertices, std::vector<uint16_t>{uint16_t(i),uint16_t(i + 1), uint16_t(i + 2)}, texture, enable_depth_test);
//	}
//}

void Draw::draw_index(std::vector<std::vector<color>>& mat, 
	const std::vector<vertex>& vertices,
	const std::vector<uint16_t>& indices,
	const texture2d *texture,
	const LightGroup& LG,
	const MaterialGroup& MG,
	bool enable_depth_test) {
	for (uint32_t i = 0; i < indices.size(); i+=3) {
		draw_triangle(mat, vertices, std::vector<uint16_t>{indices[i], indices[i + 1], indices[i + 2]}, texture, LG, MG, enable_depth_test);
	}
}

void Draw::rasterization(std::vector<vertex>& vertices,
	const std::vector<uint16_t>& indices,
	const matrix44& M,
	const LightGroup& LG,
	const MaterialGroup& MG,
	texture2d* texture,
	int height,
	int width,
	const char* outputFileName,
	bool enableDepthTest) {
	for (auto& iv : vertices) {
		iv._pos = M * iv._pos;
	}
	std::vector<std::vector<color>> mat(height, std::vector<color>(width, color(0)));
	draw_index(mat, vertices, indices, texture, LG, MG,enableDepthTest);
	generate_color_PPM(outputFileName, width, height, mat);
}