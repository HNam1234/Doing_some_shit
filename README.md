# Hello World C++ (CMake)

Prerequisites (Ubuntu/Debian):

```bash
sudo apt update
sudo apt install -y cmake g++ pkg-config libopencv-dev
```

Minimal C++ "Hello, World!" project using CMake.

Build (Linux):

```bash
mkdir -p build
cmake -S . -B build
cmake --build build --config Debug
```

Run:

```bash
./build/hello
```

Output:
- Writes `output.png` in the project root.

VS Code:
- Use the `Run Build Task` (default: `build`) to compile.
- Use the `Debug` configuration named "Debug hello" to run under the debugger.
