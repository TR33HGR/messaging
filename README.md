# Building
## Setup
To setup, make a `build` directory & from it run:
```
cmake ..
```
To include unit tests, instead run:
```
cmake .. -DBUILD_TESTS=ON
```
## Actually building
From the `build` directory, run:
```
cmake --build .
```
## Actually running tests
To run tests, after building, while still in the `build` directory, run:
```
ctest --output-on-failure
```
**You will need to rebuild if you want to test new changes.**