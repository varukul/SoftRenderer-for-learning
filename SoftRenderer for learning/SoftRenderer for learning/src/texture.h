#pragma once
#include"color.h"
#include<vector>
class texture2d {
public:
	texture2d(){}
	texture2d(const std::vector<std::vector<color>>& texc, int w, int h);
	texture2d(const texture2d &t);
	std::vector<std::vector<color>> _texc;                    //´æ´¢ÌùÍ¼µÄÏñËØ¾ØÕó
	int _width, _height;
};

class textcoord {
public:
	textcoord(int u,int v);
	//textcoord(const textcoord &tc);          //bitwise copy is good
	textcoord operator*(float n)const;
	textcoord operator+(const textcoord &tc);
	textcoord operator/(float n)const;
	int _u, _v;
};