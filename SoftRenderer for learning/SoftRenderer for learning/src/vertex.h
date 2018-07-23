#pragma once
#pragma once
#include"vec3f.h"
#include"color.h"

class vertex
{
public:
	vertex(const vec3f &pos, const color &col);
	vertex(const vertex &vertex);
	~vertex();

	vec3f _pos;
	color _col;
};

