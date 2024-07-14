cmake_minimum_required(VERSION 3.28)
project(image_processor)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")

add_executable(
        image_processor
        image_processor.cpp
        bmp.cpp
        bmp.h
        image.cpp
        image.h
        filters/base.h
        filters/crop.cpp
        filters/crop.h
        filters/grayscale.cpp
        filters/grayscale.h
        filters/negative.cpp
        filters/negative.h
        filters/matrix_filters/matrix.cpp
        filters/matrix_filters/matrix.h
        filters/matrix_filters/sharp.cpp
        filters/matrix_filters/sharp.h
        filters/matrix_filters/edge_detection.cpp
        filters/matrix_filters/edge_detection.h
        filters/nostalgic.cpp
        filters/nostalgic.h
        execution_control/shared_structures.h
        execution_control/parser.cpp
        execution_control/parser.h
        execution_control/processor.cpp
        execution_control/processor.h
        execution_control/producer.cpp
        execution_control/producer.h
        exceptions.cpp
        exceptions.h
)

target_include_directories(image_processor
        PUBLIC ${PROJECT_SOURCE_DIR})
