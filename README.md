# Overview

This is a set of C++ codes developed to study algorithms and concepts of computer science. It posseses the following characteristics:

- Developed with C++11;
- This code uses some UNIX functions, so it is platform dependent (it was only tested on Linux);
- This project was initially developed in C and later converted to C++. Check the original version with a more detailed description [here](https://github.com/ClecioJung/studying-c);

# Usage

Download this project and compile it by typing the command `make` in its folder. Next, just run one of the executables located in the `bin` folder. Here is an example:

```console
$ make
$ ./bin/dynamic-array
```

In order to check if there is any memory leak, use the `valgrind` command:

```console
$ valgrind --tool=memcheck ./bin/dynamic-array
```

To run all the tests, use the following command:

```console
$ make test
```