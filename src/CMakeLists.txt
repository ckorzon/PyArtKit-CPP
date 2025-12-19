
add_library(artkit_core core/Canvas.cpp core/Geometry.cpp core/pngwriter.cpp)
add_executable(testcanvas_manual testcanvas_manual.cpp core/Canvas.cpp core/Geometry.cpp core/pngwriter.cpp)

find_package(PNG REQUIRED)

target_link_libraries(artkit_core PNG::PNG)
target_include_directories(artkit_core PRIVATE ${PNG_INCLUDE_DIR})
target_include_directories(artkit_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/core)

target_link_libraries(testcanvas_manual PNG::PNG)
target_include_directories(testcanvas_manual PRIVATE ${PNG_INCLUDE_DIR})
target_include_directories(testcanvas_manual PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/core)

# Find Python installation using CMake
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

message(STATUS "Python executable:      ${Python3_EXECUTABLE}")
message(STATUS "Python include dirs:    ${Python3_INCLUDE_DIRS}")
message(STATUS "Python libraries:       ${Python3_LIBRARIES}")
message(STATUS "Python DLL:             ${Python3_RUNTIME_LIBRARY_DIRS}")

message(STATUS "Python include dir: ${Python3_INCLUDE_DIRS}")
message(STATUS "Python library: ${Python3_LIBRARIES}")

# Create a Python extension module from the C++ code
add_library(pyartkit_cpp MODULE python/pycanvas.cpp)

target_link_libraries(pyartkit_cpp
    PRIVATE
        artkit_core
        Python3::Python
)

set_target_properties(pyartkit_cpp PROPERTIES
    PREFIX ""
    SUFFIX ".pyd"   # Windows requires .pyd suffix for Python extensions
)
