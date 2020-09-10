/*
  Copyright (C) 2002-2020 CERN for the benefit of the ATLAS collaboration
*/

#include "sincos.h"

void S1::parameterized_sincos(const double r, double &__restrict__ sin_a,
                              double &__restrict__ cos_a) const __restrict__
{
    const double r2 = r * r;
    const double r3 = r2 * r;
    const double r4 = r2 * r2;
    const double r5 = r4 * r;

    //  s0 + s1* x1 + s2x^2 + s3x^2+ s4x^4  + s5x^5
    sin_a = m_sin_parametrization[0] + m_sin_parametrization[1] * r +
            m_sin_parametrization[2] * r2 + m_sin_parametrization[3] * r3 +
            m_sin_parametrization[4] * r4 + m_sin_parametrization[5] * r5;

    //  c0 + c1* x1 + c2x^2 + c3x^2+ c4x^4  + c5x^5
    cos_a = m_cos_parametrization[0] + m_cos_parametrization[1] * r +
            m_cos_parametrization[2] * r2 + m_cos_parametrization[3] * r3 +
            m_cos_parametrization[4] * r4 + m_cos_parametrization[5] * r5;
}

void S2::parameterized_sincos(const double r, double &__restrict__ sin_a,
                              double &__restrict__ cos_a) const __restrict__
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
    // [s4, s5, c4, c5] * r2 * r2
    // +
    // [s2, s3, c3, c3] * r2
    // +
    // s0, s1, c0, c1
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

void S3::parameterized_sincos(const double r, double &__restrict__ sin_a,
                              double &__restrict__ cos_a) const __restrict__
{
    // P0 = s4x^4 + s2x^2 + s0
    // P1 = s5x^4 + s3x^3 + s1
    // P2 = c4x^4 + c2x^2 + c0
    // P3 = c5x^4 + c3x^2 + c1

    const double r2 = r * r;
    CxxUtils::vec<double, 4> P = m_sincos_parametrization_0;
    P = r2 * P + m_sincos_parametrization_1;
    P = r2 * P + m_sincos_parametrization_2;
    sin_a = r * P[1] + P[0];
    cos_a = r * P[3] + P[2];
}

void S4::parameterized_sincos(const double r, double &__restrict__ sin_a,
                              double &__restrict__ cos_a) const __restrict__
{
    // P0 = s4x^4 + s2x^2 + s0
    // P1 = s5x^4 + s3x^3 + s1
    // P2 = c4x^4 + c2x^2 + c0
    // P3 = c5x^4 + c3x^2 + c1

    const double r2 = r * r;
    CxxUtils::vec<double, 4> P = m_sincos_parametrization_0;
    P = r2 * P + m_sincos_parametrization_1;
    P = r2 * P + m_sincos_parametrization_2;
    CxxUtils::vec<double, 4> P2;
    CxxUtils::vpermute<1, 0, 3, 2>(P2, P);
    CxxUtils::vec<double, 4> res = r * P2 + P;
    sin_a = res[0];
    cos_a = res[2];
}

int main()
{
    double r{290};
    double sin_a{0};
    double cos_a{0};
    const S1 s1{};
    s1.parameterized_sincos(r, sin_a, cos_a);
    std::cout << "1 sine for r " << r << " is " << sin_a << std::endl;
    std::cout << "1 cosine for r " << r << " is " << cos_a << std::endl;

    const S2 s2{};
    s2.parameterized_sincos(r, sin_a, cos_a);
    std::cout << "2 sine for r " << r << " is " << sin_a << std::endl;
    std::cout << "2 cosine for r " << r << " is " << cos_a << std::endl;

    const S3 s3{};
    s3.parameterized_sincos(r, sin_a, cos_a);
    std::cout << "3 sine for r " << r << " is " << sin_a << std::endl;
    std::cout << "3 cosine for r " << r << " is " << cos_a << std::endl;

    const S4 s4{};
    s4.parameterized_sincos(r, sin_a, cos_a);
    std::cout << "4 sine for r " << r << " is " << sin_a << std::endl;
    std::cout << "4 cosine for r " << r << " is " << cos_a << std::endl;
}