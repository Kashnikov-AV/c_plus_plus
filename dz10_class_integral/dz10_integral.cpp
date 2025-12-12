#include <iostream>
#include "integral.h"
#define _USE_MATH_DEFINES // for C++
#include <math.h>

int main()
{
    std::cout << "calc_integrals" << std::endl;
    integral_cos c(-1 * M_PI / 2, M_PI / 2, 100000);
    std::cout << "cos(-Pi/2, PI/2) = " << c.calc() << std::endl;
    integral_sin si(0, M_PI, 100000);
    std::cout << "sin(0, PI) = " << si.calc() << std::endl;
    integral_exp ex(-9999, 1, 100000);
    std::cout << "exp(1) = " << ex.calc() << std::endl;

    system("PAUSE");
    return 0;
}
