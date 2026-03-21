cmake -B build -S . --preset=msvc-release
cmake --build build --config Release
.\build\tests\Release\test_canvas.exe
.\build\tests\Release\test_geometry.exe
.\build\tests\Release\test_shapes.exe