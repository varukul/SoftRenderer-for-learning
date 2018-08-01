//#pragma once
//#include"vec3f.h"
//
//class ray {
//public:
//	vec3f _ori, _dir;
//};
//
//bool hitbox(float xmin ,float xmax,float ymin,float ymax,const ray &r) {
//	float xd = 1.0f / r._dir._x;
//	float tminx, tmaxx, tminy, tmaxy;
//	if (r._dir._x >= 0) {
//		tminx = (xmin - r._ori._x)*xd;
//		tmaxx = (xmax - r._ori._x)*xd;
//	}
//	else {
//		tminx = (xmax - r._ori._x)*xd;
//		tmaxx = (xmin - r._ori._x)*xd;
//	}
//	float yd = 1.0f / r._dir._y;
//	if (r._dir._y >= 0) {
//		tminy = (xmin - r._ori._y)*yd;
//		tmaxy = (xmax - r._ori._y)*yd;
//	}
//	else {
//		tminy = (xmax - r._ori._y)*yd;
//		tmaxy = (xmin - r._ori._y)*yd;
//	}
//
//	if (tminx > tmaxy || tminy < tmaxx) {
//		return false;
//	}
//	return true;
//}