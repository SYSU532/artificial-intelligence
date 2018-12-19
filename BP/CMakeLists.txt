cmake_minimum_required(VERSION 3.10)
project(bp)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (APPLE)
    set (CMAKE_CXX_FLAGS "-lX11 -L/usr/X11/lib -I/usr/X11/include")
    add_executable(bp-mac
            src/CImg.h src/CImgMNistData.cpp src/CImgMNistData.h src/main.cpp src/NeuralNetwork.cpp src/NeuralNetwork.h src/testUtils.cpp src/testUtils.h src/NumberSegmentation.h src/NumberSegmentation.cpp)
endif (APPLE)

if(UNIX AND NOT APPLE)
    add_executable(bp-linux
            src/CImg.h src/CImgMNistData.cpp src/CImgMNistData.h src/main.cpp src/NeuralNetwork.cpp src/NeuralNetwork.h src/testUtils.cpp src/testUtils.h src/NumberSegmentation.h src/NumberSegmentation.cpp)
    set (CMAKE_CXX_FLAGS "-lX11 -pthread")
    message(STATUS "Looking for X11...")
    find_package(X11 REQUIRED)
    include_directories(${X11_INCLUDE_DIR})
    target_link_libraries(bp-linux ${X11_LIBRARIES})
endif(UNIX AND NOT APPLE)

if (WIN32)
    set (CMAKE_CXX_FLAGS "-lgdi32")
    set (CMAKE_SHARED_LINKER_FLAGS "-lgdi32")
    add_executable(bp
            src/CImg.h src/CImgMNistData.cpp src/CImgMNistData.h src/main.cpp src/NeuralNetwork.cpp src/NeuralNetwork.h src/testUtils.cpp src/testUtils.h src/NumberSegmentation.h src/NumberSegmentation.cpp)
endif(WIN32)

include_directories(.)
