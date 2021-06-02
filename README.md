# Vector3D
Vector3D is a header-only extension of C++14 providing mathematical vector class and commonly used functions.

# Usage
Simply include **vector3d.h** in your project.

It needs [fmt](https://github.com/fmtlib/fmt) library by default for Python-like output format in C++.
If you don't plan to use it, comment out `#define _USE_FMT` in line 3 of the **vector3d.h**

Important to note that the precision of floating point is **float** by default. If you want to replace it to **double**, replace the number of `#define _FLOATINGPOINT_PRECISION` in line 6 of the **vector3d.h**


You can see how to use it in **main.cpp**

# Author
* Daichi Ishida

# License
"Vector3D" is under [The Unlicense](https://unlicense.org).

