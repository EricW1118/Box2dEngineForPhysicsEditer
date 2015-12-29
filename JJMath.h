//
//  JJMath.h
//  SmartTV
//
//  Created by lemon.Wang on 15/3/6.
//
//

#ifndef SmartTV_JJMath_h
#define SmartTV_JJMath_h


#pragma once

#include <stdlib.h>

/**
 * Swap two values
 * @param x first value
 * @param y second value
 */
template <class T>
inline void swap(T& x, T& y)
{
    T t = x;
    x = y;
    y = t;
}

/**
 * Clamp a value between 2 values
 * @param v the value to clamp
 * @param min lower limit
 * @param max upper limit
 */
template <class T>
inline float clamp(T v, T min, T max)
{
    if(v < min)
    {
        return min;
    }
    if(v > max)
    {
        return max;
    }
    return v;
}

/**
 * Floating point ranged random
 * @param min minimum
 * @param max maximum
 * @result random number between min and max
 */
inline float gFloatRand(float min, float max)
{
    if(min > max)
    {
        swap(min, max);
    }
    float r = (float)rand() / (float)RAND_MAX;
    return (max-min) * r + min;
}

/**
 * Ranged random value
 * @param min minimum
 * @param max maximum
 * @result random number between min and max
 */
inline int gRangeRand(float min, float max)
{
    if(min > max)
    {
        swap(min, max);
    }
    float r = (float)rand() / (float)RAND_MAX;
    return (max-min) * r + min;
}

#endif
