# rtadqlibcpp_proto

The purpose of this repository is to learn how to use the libraries that will be used for the development of the rta-dq-lib c++ version.

Libraries:

* tinyxml
* hdf5 (c++ api)
* xtensor
  * xtensor-io
    * https://github.com/xtensor-stack/xtensor-io
    * https://xtensor-io.readthedocs.io/en/latest/index.html
  * https://github.com/BlueBrain/HighFive
* valgrind 3.16.1

## Projects

This repository is composed by several subprojects:

* read_xml: the tinyxml library is used to read an xml configuration; the data is configuration data is transposed into custom configuration classes.
* read_hdf5: the hdf5-cpp library is used to read the lst dl1 compound datatype in the most efficient way.
* xtensor: the xtensor library is used to implement the data aggregation and transformation functions needed by the rta-dq-lib.
* read_hdf5_to_xtensor: the purpose of this project is to read an hdf5 files and store the data into xtensors in the most efficient way.
* rta-dq-lib: the actual rta-dq-lib-cpp implementation (check "Development")

## Development

### Execution Strategies
The package rta-dq-lib/execution_strategies contains a hiararchy of classes that implement the logic executed by the Nodes. 
