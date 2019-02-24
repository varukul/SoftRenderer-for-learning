#include"vec.h"


//vec3f
vec3f::vec3f() :_x(0), _y(0), _z(0) {}
vec3f::vec3f(float x, float y, float z) : _x(x), _y(y), _z(z) {}
vec3f::vec3f(float n) : _x(n), _y(n), _z(n) {}

vec3f::~vec3f() {}

vec3f vec3f::operator+(const vec3f &v) const {
	return vec3f(_x + v._x, _y + v._y, _z + v._z);
}

vec3f vec3f::operator-(const vec3f &v) const {
	return vec3f(_x - v._x, _y - v._y, _z - v._z);
}

vec3f operator-(const vec3f &v) {
	return vec3f(-v._x, -v._y, -v._z);
}

vec3f vec3f::operator*(const float num) const {
	return vec3f(_x*num, _y*num, _z*num);
}

vec3f vec3f::operator*(const vec3f& v)const {
	return vec3f(_x*v._x, _y*v._y, _z*v._z);
}

vec3f vec3f::operator/(const float num) const {
	return vec3f(_x / num, _y / num, _z / num);
}

vec3f vec3f::operator/(const vec3f& v)const {
	return vec3f(_x / v._x, _y / v._y, _z / v._z);
}

float dot(const vec3f &v1, const vec3f &v2) {
	return (v1._x*v2._x + v1._y*v2._y + v1._z*v2._z);
}

vec3f cross(const vec3f &v1, const vec3f &v2) {
	return vec3f(v1._y*v2._z - v2._y*v1._z, -(v1._x*v2._z - v2._x*v1._z), v1._x*v2._y - v2._x*v1._y);
}

std::ostream& operator<<(std::ostream &os, const vec3f &v) {
	os << "[" << v._x << "," << v._y << "," << v._z << "]";
	return os;
}

vec3f vec3f::normalize() const {
	float t = 1.0f / sqrt(_x*_x + _y * _y + _z * _z);
	return vec3f(t*_x, t*_y, t*_z);
}

float vec3f::squared_length() {
	return (_x * _x + _y * _y + _z * _z);
}

float vec3f::length() const {
	return sqrt(_x*_x + _y * _y + _z * _z);
}


//vec4f
vec4f::vec4f()
	:v3(), _w(1.0f) 
{

}

vec4f::vec4f(const vec3f& v,const float& w)
	:v3(v),_w(w)
{

}
vec4f::vec4f(float x, float y, float z, float w)
	:v3(x,y,z),_w(w)
{

}

float vec4f::x()const {
	return v3._x;
}
void vec4f::x(float x) {
	v3._x = x;
}
float vec4f::y()const {
	return v3._y;
}
void vec4f::y(float y) {
	v3._y = y;
}
float vec4f::z()const {
	return v3._z;
}
void vec4f::z(float z) {
	v3._z = z;
}
float vec4f::w()const {
	return _w;
}
void vec4f::w(float w) {
	_w = w;
}

vec3f vec4f::xyz()const {
	return v3;
}
void vec4f::xyz(const vec3f& v) {
	v3 = v;
}

vec4f vec4f::normalize()const {
	return vec4f(v3.normalize(), _w);
}

vec4f operator-(const vec4f &v) {
	return vec4f(-v.v3, v._w);
}

vec4f vec4f::operator-(const vec4f &v)const {
	return vec4f(-v.v3);
}

vec4f vec4f::operator*(const float num)const {
	return vec4f(v3*num, _w);
}

vec4f vec4f::operator/(const float num)const {
	return vec4f(v3 / num, _w);
}

float dot(const vec4f &v1, const vec4f &v2) {
	return dot(v1.v3, v2.v3);
}

vec4f cross(const vec4f &v1, const vec4f &v2) {
	return vec4f(cross(v1.v3, v2.v3));
}