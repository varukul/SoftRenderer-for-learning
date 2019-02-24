#pragma once
#pragma once
#include<math.h>
#include<ostream>
class vec3f {
public:
	float _x, _y, _z;

	vec3f();
	vec3f(float x, float y, float z);

	vec3f(float n);

	~vec3f();

	vec3f operator+(const vec3f &v)const;

	vec3f operator-(const vec3f &v)const;

	friend vec3f operator-(const vec3f &v);

	vec3f operator*(const float num)const;

	vec3f operator*(const vec3f& v)const;

	vec3f operator/(const float num)const;

	vec3f operator/(const vec3f& v)const;

	friend float dot(const vec3f &v1, const vec3f &v2);

	friend vec3f cross(const vec3f &v1, const vec3f &v2);

	friend std::ostream& operator<<(std::ostream &os, const vec3f &v);

	vec3f normalize()const;

	float squared_length();

	float length() const;
};

class vec4f {
public:
	vec4f();
	vec4f(const vec3f& v,const float& w = 1.0f);
	vec4f(float x, float y, float z, float w = 1.0f);
	
	float x()const;
	void x(float x);
	float y()const;
	void y(float y);
	float z()const;
	void z(float z);
	float w()const;
	void w(float w);

	vec3f xyz()const;
	void xyz(const vec3f& v);
	
	vec4f normalize()const;

	friend float dot(const vec4f &v1, const vec4f &v2);

	friend vec4f cross(const vec4f &v1, const vec4f &v2);

	friend vec4f operator-(const vec4f &v);

	vec4f operator-(const vec4f &v)const;

	vec4f operator*(const float num)const;

	vec4f operator/(const float num)const;
private:
	float _w = 1.0f;
	vec3f v3;
};