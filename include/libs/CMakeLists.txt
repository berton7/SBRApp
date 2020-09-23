add_library(myxboxlib STATIC xbox.cpp)
add_library(myseriallib STATIC serial.cpp)
add_executable(xboxLibTest xboxTester.cpp)
target_link_libraries(xboxLibTest myxboxlib Xinput)

set_property(GLOBAL PROPERTY MyLibs ${mylibs} myxboxlib myseriallib)
target_include_directories(myxboxlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(myseriallib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
