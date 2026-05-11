cmake -B build -S . --preset=msvc-release
cmake --build build --config Release
ctest -C Release --output-on-failure --test-dir .\build
