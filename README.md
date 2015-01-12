# DynaCL
## Dynamic OpenCL library loader

### What is DynaCL?
DynaCL is a little **static C library** for MS-Windows which allows to **dynamically load the OpenCL library** functions.

### How does it work?
All you need to do in order to dynamically load OpenCL is to use the `dynacl_init()` function, whose input is a string representing the path to the DLL file to load and it does all the rest by itself.
After succesfully loading and using the library, you can unload the references to the module (and functions) by calling `dynacl_shutdown()`.

### Which OpenCL specification does DynaCL support?
DynaCL supports the **OpenCL 1.1** specification.

### Bugs and feedback
Please report bugs through the [issue tracker](https://github.com/alkafir/dynacl/issues).

Feel free to contact me at [my github profile page](http://alkafir.github.io). Any feedback is appreciated.
