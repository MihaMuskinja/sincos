/*
  Copyright (C) 2002-2020 CERN for the benefit of the ATLAS collaboration
*/

/* Print out from Athena with a couple of values:
    sin params:[-1.011862e+00, 1.073536e-02, -2.757263e-05, 3.794167e-08, -2.662278e-11, 7.413205e-15]
    cos params:[1.076924e+00, 8.695955e-04, -1.200799e-05, 2.972425e-08, -3.196844e-11, 1.302089e-14]
    r sin cos
    290 0.534802 0.84478
    850 0.60863 0.793573
    1020 0.683036 0.730584
    1580 0.815663 0.578687
    2050 0.870747 0.491852
*/

#include "ATLASCxxUtils.h"
struct S1
{
    void parameterized_sincos(const double r, double &__restrict__ sin_a,
                              double &__restrict__ cos_a) const __restrict__;

    // s0 to s5
    double m_sin_parametrization[6] = {-1.011862e+00, 1.073536e-02,
                                       -2.757263e-05, 3.794167e-08,
                                       -2.662278e-11, 7.413205e-15};
    // c0 to c5
    double m_cos_parametrization[6] = {1.076924e+00, 8.695955e-04,
                                       -1.200799e-05, 2.972425e-08,
                                       -3.196844e-11, 1.302089e-14};
};

struct S2
{
    void parameterized_sincos(const double r, double &__restrict__ sin_a,
                              double &__restrict__ cos_a) const __restrict__;

    // s4, s5, c4, c5
    // s2, s3, c2, c3
    // s0, s1, c0, c1
    alignas(32) double m_sincos_parametrization[3][4] = {
        {-2.662278e-11, 7.413205e-15, -3.196844e-11, 1.302089e-14},
        {-2.757263e-05, 3.794167e-08, -1.200799e-05, 2.972425e-08},
        {-1.011862e+00, 1.073536e-02, 1.076924e+00, 8.695955e-04},
    };
};

struct S3
{
    void parameterized_sincos(const double r, double &__restrict__ sin_a,
                              double &__restrict__ cos_a) const __restrict__;

    // s4, s5, c4, c5
    // s2, s3, c2, c3
    // s0, s1, c0, c1
    CxxUtils::vec<double, 4> m_sincos_parametrization_0 = {
        -2.662278e-11, 7.413205e-15, -3.196844e-11, 1.302089e-14};
    CxxUtils::vec<double, 4> m_sincos_parametrization_1 = {
        -2.757263e-05, 3.794167e-08, -1.200799e-05, 2.972425e-08};
    CxxUtils::vec<double, 4> m_sincos_parametrization_2 = {
        -1.011862e+00, 1.073536e-02, 1.076924e+00, 8.695955e-04};
};

struct S4
{
    void parameterized_sincos(const double r, double &__restrict__ sin_a,
                              double &__restrict__ cos_a) const __restrict__;

    // s4, s5, c4, c5
    // s2, s3, c2, c3
    // s0, s1, c0, c1
    CxxUtils::vec<double, 4> m_sincos_parametrization_0 = {
        -2.662278e-11, 7.413205e-15, -3.196844e-11, 1.302089e-14};
    CxxUtils::vec<double, 4> m_sincos_parametrization_1 = {
        -2.757263e-05, 3.794167e-08, -1.200799e-05, 2.972425e-08};
    CxxUtils::vec<double, 4> m_sincos_parametrization_2 = {
        -1.011862e+00, 1.073536e-02, 1.076924e+00, 8.695955e-04};
};