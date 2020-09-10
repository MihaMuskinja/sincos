/*
  Copyright (C) 2002-2020 CERN for the benefit of the ATLAS collaboration
*/

#include <iostream>

#include "sincos.h"

double m_sin_parametrization[6] = {-1.011862e+00, 1.073536e-02, -2.757263e-05, 3.794167e-08, -2.662278e-11, 7.413205e-15};
double m_cos_parametrization[6] = {1.076924e+00, 8.695955e-04, -1.200799e-05, 2.972425e-08, -3.196844e-11, 1.302089e-14};

void parameterized_sincos(const double r, double &sin_a, double &cos_a)
{
    const double r2 = r * r;
    const double r3 = r2 * r;
    const double r4 = r2 * r2;
    const double r5 = r4 * r;

    sin_a = m_sin_parametrization[0] +
            m_sin_parametrization[1] * r +
            m_sin_parametrization[2] * r2 +
            m_sin_parametrization[3] * r3 +
            m_sin_parametrization[4] * r4 +
            m_sin_parametrization[5] * r5;

    cos_a = m_cos_parametrization[0] +
            m_cos_parametrization[1] * r +
            m_cos_parametrization[2] * r2 +
            m_cos_parametrization[3] * r3 +
            m_cos_parametrization[4] * r4 +
            m_cos_parametrization[5] * r5;
}

int main()
{
    double r{290};
    double sin_a{0};
    double cos_a{0};

    parameterized_sincos(r, sin_a, cos_a);

    std::cout << "sine of " << r << " is " << sin_a << std::endl;
    std::cout << "cosine of " << r << " is " << cos_a << std::endl;
}