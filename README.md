# ReLeMesh C++ Interface Project
This project is created to support my [ReLeMesh project](https://gitlab.com/rasmushjort8/relemesh). 
The target for this project is a shared lib, which can be used in the original python project. 
The hope is to speed up the training of the neural networks, which was slowed down significantly by the python implementation of the environment.
Another reason why I started moving to C++ instead of improving the python code, was my plan to create a WebAssembly App using this lib, at some point.

The project is written in c++17. 

### Prerequisites

*  Project is tested on Ubuntu 18.10
*  Using g++ 8.2.0
*  Boost 1.69 (Only used for unit tests)

## Getting Started

To build the shared lib simply
```
mkdir lib
mkdir lib/debug && mkdir lib/tests && mkdir bin
make libOnly
```

Running all tests requires to have boost 1.69 installed and setup so that g++ can include it.
```
make test
```

Running the python interface test:
```
make pyTest
```

## Author

* **Rasmus O. Hjort** -[LinkedIn](linkedin.com/in/rasmus-o-hjort-b8179289)