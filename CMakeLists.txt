cmake_minimum_required (VERSION 3.8)

project ("SBRApp")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(SBRController include/SBR/controller.cpp include/SBR/controller.h)
include_directories(include)

if (WIN32)
    set(SBRControllerLibs SBRController XInput)
elseif(UNIX)
    set(SBRControllerLibs SBRController)
endif()

add_executable(MainSBRApp app/main.cpp)
target_link_libraries(MainSBRApp ${SBRControllerLibs})

option(BUILD_TESTS "Build some tests" OFF)
if(${BUILD_TESTS})
    add_subdirectory ("test")
endif()
