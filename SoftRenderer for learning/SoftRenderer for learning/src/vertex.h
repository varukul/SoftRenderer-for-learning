#pragma once
#pragma once
#include"vec3f.h"
#include"color.h"
#include"texture.h"
//#include"trianglemesh.h"

class vertex
{
public:
	vertex(const vec3f &pos, const color &col,const textcoord &tc);
	vertex(const vec3f &pos, const color &col);
	vertex(const vertex &vertex);
	~vertex();

	vec3f _pos;
	color _col;
	textcoord _tc;
	//edge e;
};

