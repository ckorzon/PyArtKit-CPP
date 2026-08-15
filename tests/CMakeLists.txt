
# Collect the Catch2 library which executes the tests
find_package(Catch2 CONFIG REQUIRED)

# Find Python installation using CMake
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

# Create the executable for the tests
add_executable(test_canvas test_canvas.cpp)
add_executable(test_geometry test_geometry.cpp)
add_executable(test_shapes test_shapes.cpp)
add_executable(test_colorschemes test_colorschemes.cpp)
add_executable(test_python test_python.cpp)

# Link the Catch2 library to the tests executable
target_link_libraries(test_canvas PRIVATE artkit_core Catch2::Catch2WithMain)
target_link_libraries(test_geometry PRIVATE artkit_core Catch2::Catch2WithMain)
target_link_libraries(test_shapes PRIVATE artkit_core Catch2::Catch2WithMain)
target_link_libraries(test_colorschemes PRIVATE artkit_core Catch2::Catch2WithMain)
target_link_libraries(test_python PRIVATE artkit_core pyartkit_bindings Catch2::Catch2WithMain Python3::Python)

add_test(NAME test_canvas COMMAND test_canvas)
add_test(NAME test_geometry COMMAND test_geometry)
add_test(NAME test_shapes COMMAND test_shapes)
add_test(NAME test_colorschemes COMMAND test_colorschemes)
add_test(NAME test_python COMMAND test_python)

set_tests_properties(test_python PROPERTIES
    ENVIRONMENT "PYTHONPATH=${CMAKE_BINARY_DIR}/src/Release"
)
