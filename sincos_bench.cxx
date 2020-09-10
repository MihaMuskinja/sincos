/*
  Copyright (C) 2002-2020 CERN for the benefit of the ATLAS collaboration
*/

#include <iostream>

#include "benchmark/benchmark.h"
#include "sincos.h"

//
// S1
//
static void parameterized_sincos_1_bench(benchmark::State &state)
{
    for (auto _ : state)
    {
        double sin_a{0};
        double cos_a{0};
        const S1 s{};
        for (double r = 300; r < 2000; r += 1./state.range(0))
        {
            s.parameterized_sincos(r, sin_a, cos_a);
        }
    }
}
BENCHMARK(parameterized_sincos_1_bench)->Arg(1)->Arg(10)->Arg(100);

//
// S2
//
static void parameterized_sincos_2_bench(benchmark::State &state)
{
    for (auto _ : state)
    {
        double sin_a{0};
        double cos_a{0};
        const S2 s{};
        for (double r = 300; r < 2000; r += 1./state.range(0))
        {
            s.parameterized_sincos(r, sin_a, cos_a);
        }
    }
}
BENCHMARK(parameterized_sincos_2_bench)->Arg(1)->Arg(10)->Arg(100);

//
// S3
//
static void parameterized_sincos_3_bench(benchmark::State &state)
{
    for (auto _ : state)
    {
        double sin_a{0};
        double cos_a{0};
        const S3 s{};
        for (double r = 300; r < 2000; r += 1./state.range(0))
        {
            s.parameterized_sincos(r, sin_a, cos_a);
        }
    }
}
BENCHMARK(parameterized_sincos_3_bench)->Arg(1)->Arg(10)->Arg(100);

//
// S4
//
static void parameterized_sincos_4_bench(benchmark::State &state)
{
    for (auto _ : state)
    {
        double sin_a{0};
        double cos_a{0};
        const S4 s{};
        for (double r = 300; r < 2000; r += 1./state.range(0))
        {
            s.parameterized_sincos(r, sin_a, cos_a);
        }
    }
}
BENCHMARK(parameterized_sincos_4_bench)->Arg(1)->Arg(10)->Arg(100);

//
// main
//
BENCHMARK_MAIN();
