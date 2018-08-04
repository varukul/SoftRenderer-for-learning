#include "vertex.h"

vertex::vertex(const vec3f &pos, const color &col,const textcoord &tc,edge *e)
	:_pos(pos), _col(col),_tc(tc),_e(e)
{
	_col._a = _pos._z;
}

vertex::vertex(const vec3f &pos, const color &col)
	: _pos(pos), _col(col),_tc(textcoord(0,0))
{
	_col._a = _pos._z;
}

vertex::vertex(const vertex &vertex)
	: _pos(vertex._pos), _col(vertex._col),_tc(vertex._tc)
{
	_col._a = _pos._z;
}

vertex::~vertex()
{
}

//edge::edge(vertex &v, face *f, edge *pair, edge *next) 
//	:_v(&v),_f(f),_pair(pair),_next(next)
//{
//
//}
//
//face::face(edge *e)
//	: _e(e)
//{
//
//}