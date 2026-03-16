# Hello World C++ (CMake)

Binary naming
- `src/exercises/1_1.cpp` -> `build/ex_1_1`
- `src/exercises/1_2.cpp` -> `build/ex_1_2`

## Build

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

## Run thu cong

```bash
./build/ex_1_1
./build/ex_1_2
./build/hello
```
