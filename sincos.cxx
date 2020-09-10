/*
  Copyright (C) 2002-2020 CERN for the benefit of the ATLAS collaboration
*/

#include <iostream>

#include "sincos.h"

double m_sin_parametrization[6] = {-1.011862e+00, 1.073536e-02, -2.757263e-05, 3.794167e-08, -2.662278e-11, 7.413205e-15};
double m_cos_parametrization[6] = {1.076924e+00, 8.695955e-04, -1.200799e-05, 2.972425e-08, -3.196844e-11, 1.302089e-14};

// s0, s1, c0, c1
// s2, s3, c2, c3
// s4, s5, c4, c5
alignas(32) double m_sincos_parametrization[3][4] = {
    {-2.662278e-11, 7.413205e-15, -3.196844e-11, 1.302089e-14},
    {-2.757263e-05, 3.794167e-08, -1.200799e-05, 2.972425e-08},
    {-1.011862e+00, 1.073536e-02, 1.076924e+00, 8.695955e-04},
};

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

void parameterized_sincos_vec(const double r, double &__restrict__ sin_a, double &__restrict__ cos_a)
{
    // P0 = s4x^4 + s2x^2 + s0
    // P1 = s5x^4 + s3x^3 + s1
    // P2 = c4x^4 + c2x^2 + c0
    // P3 = c5x^4 + c3x^2 + c1

    // [s4, s5, c4, c5]
    double P[4];
    for (int ip = 0; ip < 4; ip++)
    {
        P[ip] = m_sincos_parametrization[0][ip];
    }
    const double r2 = r * r;
    for (int ic = 1; ic < 3; ic++)
    {
        for (int ip = 0; ip < 4; ip++)
        {
            P[ip] = r2 * P[ip] + m_sincos_parametrization[ic][ip];
        }
    }
    sin_a = r * P[1] + P[0];
    cos_a = r * P[3] + P[2];
}

int main()
{
    double r{290};
    double sin_a{0};
    double cos_a{0};

    parameterized_sincos(r, sin_a, cos_a);
    std::cout << "sine of " << r << " is " << sin_a << std::endl;
    std::cout << "cosine of " << r << " is " << cos_a << std::endl;

    parameterized_sincos_vec(r, sin_a, cos_a);
    std::cout << "sine of " << r << " is " << sin_a << std::endl;
    std::cout << "cosine of " << r << " is " << cos_a << std::endl;
}