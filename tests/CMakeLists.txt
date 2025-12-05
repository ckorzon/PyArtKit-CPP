
# Collect the Catch2 library which executes the tests
find_package(Catch2 CONFIG REQUIRED)

# Create the executable for the tests
add_executable(test_canvas test_canvas.cpp)
add_executable(test_geometry test_geometry.cpp)

# Link the Catch2 library to the tests executable
target_link_libraries(test_canvas PRIVATE pyartkit_cpp Catch2::Catch2WithMain)
target_link_libraries(test_geometry PRIVATE pyartkit_cpp Catch2::Catch2WithMain)

add_test(NAME test_canvas COMMAND test_canvas)
add_test(NAME test_geometry COMMAND test_geometry)
