mkdir .build/

# TODO: Complete me.
# -S specifies the source directory containing CMakeLists.txt.
# -B specifies the build directory where the build files will be generated.
cmake -S . -B .build/ -G "Visual Studio 17 2022" -DCMAKE_PREFIX_PATH=""

cmake --build .build/
