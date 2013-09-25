#ifndef _COLOR_HPP_
#define _COLOR_HPP_

namespace fixie
{
    struct color
    {
        float r, g, b, a;

        color();
        color(float red, float green, float blue, float alpha);
        color(const float data[4]);
    };
}

#endif // _COLOR_HPP_
