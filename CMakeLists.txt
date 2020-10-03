cmake_minimum_required (VERSION 3.8)

project ("SBRApp")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(SBRController include/SBR/xbox.cpp include/SBR/xbox.h)
include_directories(include)

if (WIN32)
    set(SBRControllerLibs SBRController XInput)
endif(WIN32)

add_executable(MainSBRApp app/main.cpp)
target_link_libraries(MainSBRApp ${SBRControllerLibs})

add_subdirectory ("test")
