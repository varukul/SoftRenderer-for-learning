#include"sample.h"

filter::filter(float r)
	:_r(r) 
{

}

float filter::r() const{
	return _r;
}

boxfilter::boxfilter(float r)
	:filter(r)
{

}

float boxfilter::filte(float i) const{
	if (i >= -_r && i <= _r) {
		return 0.5f;
	}
	return 0;
}