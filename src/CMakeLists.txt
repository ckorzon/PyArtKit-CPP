
add_library(artkit_core STATIC core/color.cpp core/colorscheme.cpp core/canvas.cpp core/geometry.cpp core/pngwriter.cpp core/shapes.cpp)

find_package(PNG REQUIRED)

target_link_libraries(artkit_core PUBLIC PNG::PNG)
target_include_directories(artkit_core PRIVATE ${PNG_INCLUDE_DIR})
target_include_directories(artkit_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/core)

# Find Python installation using CMake
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

message(STATUS "Python executable:      ${Python3_EXECUTABLE}")
message(STATUS "Python include dirs:    ${Python3_INCLUDE_DIRS}")
message(STATUS "Python libraries:       ${Python3_LIBRARIES}")
message(STATUS "Python DLL:             ${Python3_RUNTIME_LIBRARY_DIRS}")

message(STATUS "Python include dir: ${Python3_INCLUDE_DIRS}")
message(STATUS "Python library: ${Python3_LIBRARIES}")


add_library(pyartkit_bindings OBJECT
    python/pycanvas.cpp
    python/pycolor.cpp
    python/pycolorscheme.cpp
    python/pyshapes.cpp
)

target_link_libraries(pyartkit_bindings
    PRIVATE
        artkit_core
        PNG::PNG
        Python3::Python
)

target_include_directories(pyartkit_bindings PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/python)

# Create a Python extension module from the C++ code
add_library(pyartkitcpp MODULE $<TARGET_OBJECTS:pyartkit_bindings> python/pyartkit.cpp)

configure_file(
    "${CMAKE_SOURCE_DIR}/src/python/pyartkitcpp.pyi"
    "${CMAKE_CURRENT_BINARY_DIR}/Release/pyartkitcpp.pyi"
    COPYONLY
)

target_link_libraries(pyartkitcpp
    PRIVATE
        artkit_core
        PNG::PNG
        Python3::Python
)

set_target_properties(pyartkitcpp PROPERTIES
    PREFIX ""
    SUFFIX ".pyd"   # Windows requires .pyd suffix for Python extensions
)
