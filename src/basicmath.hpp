#ifndef BASICMATH_HPP_INCLUDED
#define BASICMATH_HPP_INCLUDED

#include <cstdlib> // for rand()
#include <cmath>

const float PI = 3.14159265358979;
const float TWO_PI = PI*2;
const float HALF_PI = PI*0.5f;

const float SQRT2 = sqrt(2.0f);
const float HALF_SQRT2 = SQRT2*0.5f;

float getrand(); // returns a (poorly distributed) random float in [0,1)

float getdist2(float x, float y); // squared distance
float getdist(float x, float y); // distance
float Lpnorm(float x, float y, float p);

#endif // BASICMATH_HPP_INCLUDED
