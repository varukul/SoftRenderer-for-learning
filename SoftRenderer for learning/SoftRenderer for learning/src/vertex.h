#pragma once
#pragma once
#include"vec.h"
#include"color.h"
#include"texture.h"

class vertex
{
public:
	vertex(const vec4f &pos, const textcoord &tc);
	vertex(const vec4f &pos, const vec3f& normal, const textcoord &tc);
	vertex(const vec4f &pos);
	~vertex();

	vec4f _pos;
	vec3f _posW;          //存储顶点的世界坐标用于光照计算
	vec3f _normal;
	textcoord _tc;
};

