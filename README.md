# Parametrized sincos
Playground for using SIMD for the parametrized sincos calculation in ATLAS: [LArWheelCalculatorGeometry.cxx](https://gitlab.cern.ch/mmuskinj/athena/-/blob/master/DetectorDescription/GeoModel/GeoSpecialShapes/src/LArWheelCalculatorGeometry.cxx)

# Build using CMake
```
cmake -DBENCHMARK_ENABLE_GTEST_TESTS=OFF <path-to-source-dir>
make
```

# Executables

- `sincos`: run a basic test to confirm that all implementations give the same result
- `sincos_benchamrk`: run the google benchmark to time the various implementations
