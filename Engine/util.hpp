#pragma once
#include <cmath>

class util
{
public:
    constexpr static float PI = 3.14159265;

    static float getAngle(int x1, int y1, int x2, int y2)
    {
        float angle = -90 + atan2(y1 - y2, x1 - x2) * (180 / PI);
        return angle >= 0 ? angle : 360 + angle;
    }
};