
# Collect the Catch2 library which executes the tests
find_package(Catch2 CONFIG REQUIRED)

# Create the executable for the tests
add_executable(test_canvas test_canvas.cpp)
add_executable(test_geometry test_geometry.cpp)
add_executable(test_shapes test_shapes.cpp)
add_executable(test_colorschemes test_colorschemes.cpp)

# Link the Catch2 library to the tests executable
target_link_libraries(test_canvas PRIVATE artkit_core Catch2::Catch2WithMain)
target_link_libraries(test_geometry PRIVATE artkit_core Catch2::Catch2WithMain)
target_link_libraries(test_shapes PRIVATE artkit_core Catch2::Catch2WithMain)
target_link_libraries(test_colorschemes PRIVATE artkit_core Catch2::Catch2WithMain)

add_test(NAME test_canvas COMMAND test_canvas)
add_test(NAME test_geometry COMMAND test_geometry)
add_test(NAME test_shapes COMMAND test_shapes)
add_test(NAME test_colorschemes COMMAND test_colorschemes)
