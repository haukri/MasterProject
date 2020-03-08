#ifndef helperFunctions_H
#define helperFunctions_H

namespace helperFunctions {
    double static clamp(double value, double lo, double hi) {
        if(value < lo)
            return lo;
        if(value > hi)
            return hi;
        return value;
    }
}

#endif