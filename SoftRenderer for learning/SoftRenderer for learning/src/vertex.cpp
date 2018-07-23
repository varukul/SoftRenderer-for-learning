#include "vertex.h"

vertex::vertex(const vec3f &pos, const color &col)
	:_pos(pos), _col(col)
{
}

vertex::vertex(const vertex &vertex)
	: _pos(vertex._pos), _col(vertex._col)
{

}

vertex::~vertex()
{
}
