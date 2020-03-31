#include "basicmath.hpp"

float getrand() {
    return (float)rand()/RAND_MAX;
}

float getdist2(float x, float y) {
    return x*x + y*y;
}

float getdist(float x, float y) {
    return sqrt(getdist2(x, y));
}

float Lpnorm(float x, float y, float p) {
    x = fabs(x);
    y = fabs(y);
    return pow(pow(x, p) + pow(y, p), 1/p);
}
