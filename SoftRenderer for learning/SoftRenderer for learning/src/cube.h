#pragma once
#include"vertex.h"
#include"matrix44.h"
class cube {
public:
	cube(vertex v[8], matrix44 *p, texture2d *texture);
	void init();
	matrix44 * _p;
	texture2d * _texture;
	vertex * _v;
};