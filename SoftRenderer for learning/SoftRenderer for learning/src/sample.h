#pragma once
#include"color.h"
#include<vector>
#include"vertex.h"

/*
not success at all

*/



class filter {
public:
	float r()const;
	virtual float filte(float i)const = 0;
protected:
	filter(float r);
	float _r;
};

class boxfilter :public filter{
public:
	boxfilter(float r);
	virtual float filte(float i)const override;
};

class tentfilter :public filter {
public:
	tentfilter(float r);

	virtual float filte(float i)const override;
};

class gaussianfilter:public filter{
public:
	gaussianfilter(float r);
	virtual float filte(float i)const override;
};

class B_splinefilter :public filter {
public:
	B_splinefilter(float r);
	virtual float filte(float i)const override;
};

class catmull_romfilter :public filter {
public:
	catmull_romfilter(float r);
	virtual float filte(float i)const override;
};

class cubicfilter:public filter{
public:
	cubicfilter(float r);
	virtual float filte(float i)const override;
};

namespace sample {
	color convolve(const color a[], const filter *b, int i);

	color convolve2d(const color **a, const filter *b, int x, int y);

	color reconstruct(const color a[], const filter *b, float x);

	color reconstruct2d(const color **a, const filter *b, float x, float y);

	color** filter_image(color **mat, filter *b, int w, int h);
}