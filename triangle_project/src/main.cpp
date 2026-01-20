#include <iostream>
#include "pythagorean_triangle.h"

int main()
{
    PythagoreanTriangle<int> t(3, 4);

    std::cout << "Hypotenuse: " << t.get_hypotenuse() << "\n";
    std::cout << "Area: " << t.get_area() << "\n";

    return 0;
}
