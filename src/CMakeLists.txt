
add_library(pyartkit_cpp Canvas.cpp Geometry.cpp pngwriter.cpp)
add_executable(testcanvas_manual testcanvas_manual.cpp Canvas.cpp Geometry.cpp pngwriter.cpp)

find_package(PNG REQUIRED)

target_link_libraries(pyartkit_cpp PNG::PNG)
target_include_directories(pyartkit_cpp PRIVATE ${PNG_INCLUDE_DIR})
target_include_directories(pyartkit_cpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(testcanvas_manual PNG::PNG)
target_include_directories(testcanvas_manual PRIVATE ${PNG_INCLUDE_DIR})
target_include_directories(testcanvas_manual PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
