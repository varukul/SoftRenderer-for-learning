#include"texture.h"
#include<fstream>

texture2d::texture2d(const std::vector<std::vector<color>>& texc, int w, int h){
	_texc = std::move(texc);
	_width = w;
	_height = h;
}
texture2d::texture2d(const texture2d &t):_texc(t._height,std::vector<color>(t._width,color())) {
	_width = t._width;
	_height = t._height;
	memcpy(&_texc, &t._texc, sizeof(color)*_width*_height);
}

textcoord::textcoord(int u, int v)
{
	_u = u;
	_v = v;
}

textcoord textcoord::operator*(float n)const {
	return textcoord(_u*n, _v*n);
}

textcoord textcoord::operator+(const textcoord &tc) {
	return textcoord(_u + tc._u, _v + tc._v);
}

textcoord textcoord::operator/(float n)const {
	return textcoord(_u / n, _v / n);
}