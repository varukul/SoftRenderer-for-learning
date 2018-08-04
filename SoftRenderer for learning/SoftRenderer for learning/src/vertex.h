#pragma once
#pragma once
#include"vec3f.h"
#include"color.h"
#include"texture.h"
//#include"trianglemesh.h"

//the half-edge strcture

//class edge {
//public:
//	edge(vertex &v, face *f, edge *pair, edge *next);
//	vertex *_v;
//	face *_f;
//	edge *_pair, *_next;
//};
//
//
//class face{
//public:
//	face(edge *e);
//	edge *_e;
//};

class edge;
class vertex
{
public:
	vertex(const vec3f &pos, const color &col, const textcoord &tc, edge *e = NULL);
	vertex(const vec3f &pos, const color &col);
	vertex(const vertex &vertex);
	~vertex();

	vec3f _pos;
	color _col;
	textcoord _tc;
	edge *_e;
};

