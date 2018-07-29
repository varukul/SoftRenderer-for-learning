#pragma once
#include<iostream>
const float INFINITY_FLOAT = 1e8;

class color {
public:
	color();
	color(float n);
	color(float r, float g, float b,float a = INFINITY_FLOAT);
	color(const color &c);

	color operator+(const color &c);
	color& operator=(const color &c);
	color operator*(float n) const;
	friend std::ostream& operator<<(std::ostream &os, const color &c);

	float _r, _g, _b ,_a;
};