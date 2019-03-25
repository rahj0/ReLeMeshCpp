# ReLeMesh C++ Interface Project
This project is created to support my [ReLeMesh project](https://gitlab.com/rasmushjort8/relemesh). The target for this project is a shared lib, which can be used in the original python project. The hope is to speed up the training of the neural networks, which was slowed down significantly by the python implementation of the environment.
The project is written in c++17. 

### Prerequisites

Project is tested on Ubuntu 18.10
Using g++ 8.2.0

## Getting Started

To build the shared lib simply
```
make
```

Running the tests
```
make test
```

Running the python interface test:
```
make pyTest
```

## Author

* **Rasmus O. Hjort** -[LinkedIn](linkedin.com/in/rasmus-o-hjort-b8179289)