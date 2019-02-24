#include"color.h"



color::color()
	:_r(0), _g(0), _b(0),_a(INFINITY_FLOAT)
{

}

color::color(float n)
	: _r(n), _g(n), _b(n),_a(INFINITY_FLOAT)
{

}

color::color(float r, float g, float b,float a)
	: _r(r), _g(g), _b(b),_a(a)
{

}

//color::color(const color &c)
//	: _r(c._r), _g(c._g), _b(c._b),_a(c._a)
//{
//
//}

color color::operator+(const color &c) {
	return color(_r + c._r, _g + c._g, _b + c._b, _a + c._a);
}

color::color(const vec3f& v) {
	_r = v._x;
	_g = v._y;
	_b = v._z;
}
color::color(const vec4f& v) {
	_r = v.x();
	_g = v.y();
	_b = v.z();
	_a = v.w();
}
//color& color::operator=(const color &c) {
//	_r = c._r;
//	_g = c._g;
//	_b = c._b;
//	_a = c._a;
//	return *this;
//}
color color::operator*(float n) const{
	return color(_r*n, _g*n, _b*n ,_a*n);
}

std::ostream& operator<<(std::ostream &os, const color &c) {
	os << c._r << " " << c._g << " " << c._b << " " << c._a;
	return os;
}