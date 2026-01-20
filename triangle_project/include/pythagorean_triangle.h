#pragma once
#include <cmath>

template <typename T>
class PythagoreanTriangle
{
private:
    T a;   // base
    T b;   // height

public:
    PythagoreanTriangle(T x, T y) : a(x), b(y) {}

    T get_base() const { return a; }
    T get_height() const { return b; }

    double get_hypotenuse() const
    {
        return std::sqrt(static_cast<double>(a) * a +
                         static_cast<double>(b) * b);
    }

    double get_area() const
    {
        return 0.5 * static_cast<double>(a) * b;
    }

    bool is_valid() const
    {
        // fix negative side test
        if (a <= 0 || b <= 0)
            return false;
        double lhs = static_cast<double>(a) * a +
                     static_cast<double>(b) * b;
        double rhs = get_hypotenuse() * get_hypotenuse();
        return std::abs(lhs - rhs) < 1e-9;
    }
};

