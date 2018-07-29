#include"sample.h"
#include<iostream>
//base

filter::filter(float r)
	:_r(r)
{

}

float filter::r() const{
	return _r;
}

//box


boxfilter::boxfilter(float r)
	:filter(r)
{

}

float boxfilter::filte(float i) const{
	if (i >= -_r && i <= _r) {
		return 1.0f / (2 * _r + 1);
	}
	return 0;
}

//tent

tentfilter::tentfilter(float r)
	:filter(r)
{
}

float tentfilter::filte(float i) const {
	return (_r - abs(i)) > 0 ? (_r - abs(i)) : 0;
}

//gaussian

gaussianfilter::gaussianfilter(float r) 
	:filter(r)
{

}

float gaussianfilter::filte(float i) const{
	if (i <= _r || i >= _r)return 0;
	float t = 1.0f / (_r*sqrt(2 * 3.14f));
	float e = pow(2.71828, -(i*i)/(2*_r*_r));
	return t * e;
}

// b spline

B_splinefilter::B_splinefilter(float r)
	:filter(r)
{
}

float B_splinefilter::filte(float i)const {
	float x = abs(i);
	float deno = 1.0f / 6.0f;
	if (x <= 1) {
		return (-3 * pow(1 - x, 3) + 3 * pow(1 - x, 2) + 3 * (1 - x) + 1)*deno;
	}
	else if (x > 1 && x <= 2) {
		return pow(2 - x, 3)*deno;
	}
	else {
		return 0;
	}
}

//catmull_rom

catmull_romfilter::catmull_romfilter(float r)
	:filter(r)
{
}

float catmull_romfilter::filte(float i)const {
	float x = abs(i);
	float deno = 1.0f / 2.0f;
	if (x <= 1) {
		return (-3 * pow(1 - x, 3) + 4 * pow(1 - x, 2) + (1 - x))*deno;
	}
	else if (x > 1 && x <= 2) {
		return (pow(2 - x, 3) - pow(2 - x, 2))*deno;
	}
	else {
		return 0;
	}
}

//cubic

cubicfilter::cubicfilter(float r)
	:filter(r)
{
}

float cubicfilter::filte(float i)const {
	B_splinefilter fb(_r);
	catmull_romfilter fc(_r);
	return fb.filte(i) / 3.0f + fc.filte(i)*2.0f / 3.0f;
}


//sample

color sample::convolve(const color a[], const filter *b, int i) {                //discrete-discrete
	color s;
	float r = b->r();
	for (int j = i - r; j <= i + r; j++) {
		s = s + a[j] * b->filte(i - j);
	}
	return s;
}

color sample::convolve2d(const color **a, const filter *b, int x, int y) {
	color s;
	float r = b->r();
	for (int i = x - r; i <= x + r; i++) {
		for (int j = y - r; j <= y + r; j++) {
			s = s + a[j][i] * b->filte(i - x) * b->filte(j - y);
		}
	}
	return s;
}

color sample::reconstruct(const color a[], const filter *b, float x) {              //discrete-continunous
	color s;
	float r = b->r();
	for (int i = x - r; i < x + r; i++) {
		s = s + a[i] * b->filte(i);
	}
	return s;
}

color sample::reconstruct2d(const color **a, const filter *b, float x, float y) {
	color s;
	float r = b->r();
	for (int i = x - r; i < x + r; i++) {
		for (int j = y - r; j <= y + r; j++) {
			s = s + a[j][i] * b->filte(i - x) * b->filte(j - y);
		}
	}
	return s;
}

color** sample::filter_image(color **mat, filter *b, int w, int h) {
	color ** new_image = new color*[h];
	for (int i = 0; i < h; i++) {
		new_image[i] = new color[w];
	}

	color *s = new color[w];
	float r = b->r();
	int m = r;

	for (int j = r; j < h + r ; j++) {
		for (int ix = 0; ix < w; ix++) {
			s[ix] = 0;
			for (int jx = j - r; jx < j ; jx++) {
				s[ix] = s[ix] + mat[jx][ix] * b->filte(j - jx);
				//std::cout << s[ix] << " " << ix << std::endl;
			}
		}
		for (int i = r; i < w + r; i++) {
			for (int ix = i - r; ix < i + r - 1 ; ix++) {
				//std::cout << s[ix] << " " << b->filte(i - ix) << " " << ix << std::endl;
				new_image[j-m][i-m] = new_image[j-m][i-m] + s[ix] * b->filte(i - ix);
			}
		}
	}

	delete[]s;

	for (int i = 0; i < h; i++) {
		delete[]mat[i];
	}
	delete[]mat;
	return new_image;
}