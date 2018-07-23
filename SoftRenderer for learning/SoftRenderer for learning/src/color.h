#pragma once


class color {
public:
	color();
	color(float n);
	color(float r, float g, float b);
	color(const color &c);

	color operator+(const color &c);
	color& operator=(const color &c);
	color operator*(float n);

	float _r, _g, _b;
};