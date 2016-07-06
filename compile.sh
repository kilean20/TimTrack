#!/bin/bash

g++ -O3 driftpass.h ebendpass.h equadpass.h rfcavpass.h efodo.h global.h element.cpp element.h line.h line.cpp run_test_Poincare.cpp -o ./run/run -larmadillo

