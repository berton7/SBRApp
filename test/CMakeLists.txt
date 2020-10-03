add_executable(ControllerTest xboxTester.cpp)
add_dependencies(ControllerTest SBRController)
target_link_libraries(ControllerTest ${SBRControllerLibs})
