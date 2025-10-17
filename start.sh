rm -rf build/
# cmake -G "Ninja" -S ./Src/ -B ./build/ -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Debug
cmake -G "Ninja" -S Src/ -B build/ -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Debug
# cmake -G "Ninja" -S ./Src/ -B ./build/ -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Release
cmake --build build/
