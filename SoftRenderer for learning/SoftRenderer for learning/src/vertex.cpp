#include "vertex.h"

vertex::vertex(const vec3f &pos, const color &col)
	:_pos(pos), _col(col)
{
	_col._a = _pos._z;
}

vertex::vertex(const vertex &vertex)
	: _pos(vertex._pos), _col(vertex._col)
{
	_col._a = _pos._z;
}

vertex::~vertex()
{
}
