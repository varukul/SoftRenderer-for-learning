#include "vertex.h"

vertex::vertex(const vec4f &pos,const textcoord &tc)
	:_pos(pos), _posW(pos.x(), pos.y(), pos.z()),_tc(tc)
{
	
}

vertex::vertex(const vec4f &pos, const vec3f& normal, const textcoord &tc)
	: _pos(pos), _posW(pos.xyz()), _normal(normal), _tc(tc)
{

}

vertex::vertex(const vec4f &pos)
	: _pos(pos),_posW(pos.x(),pos.y(),pos.z()),_tc(textcoord(0,0))
{
	
}

vertex::~vertex()
{
}