#pragma once
#include"color.h"
#include<vector>
#include"vertex.h"

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

namespace sample {
	color convolve(const color a[], const filter *b, int i) {                //discrete-discrete
		color s;
		float r = b->r();
		for (int j = i - r; j <= i + r; j++) {
			s = s + a[j]*b->filte(i - j);
		}
		return s;
	}

	color convolve2d(const color **a, const filter *b, int x, int y) {
		color s;
		float r = b->r();
		for (int i = x - r; i <= x + r; i++) {
			for (int j = y - r; j <= y + r; j++) {
				s = s + a[j][i] * b->filte(i - x) * b->filte(j - y);
			}
		}
		return s;
	}

	color reconstruct(const color a[], const filter *b, float x) {              //discrete-continunous
		color s;
		float r = b->r();
		for (int i = x - r; i < x + r; i++) {
			s = s + a[i]*b->filte(i);
		}
		return s;
	}

	color reconstruct2d(const color **a, const filter *b, float x) {
		color s;
		float r = b->r();
		for (int i = x - r; i < x + r; i++) {
			for (int j = y - r; j <= y + r; j++) {
				s = s + a[j][i] * b->filte(i - x) * b->filte(j - y);
			}
		}
		return s;
	}
}