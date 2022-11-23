cmake_minimum_required(VERSION 3.23)
project(MP2_BRANCH)

set(CMAKE_CXX_STANDARD 14)

add_executable(MP2_BRANCH src/main.cpp src/predictors/Predictor.h src/Stats.h src/predictors/SmithPredictor.cpp src/predictors/SmithPredictor.h src/predictors/BimodalPredictor.cpp src/predictors/BimodalPredictor.h)
