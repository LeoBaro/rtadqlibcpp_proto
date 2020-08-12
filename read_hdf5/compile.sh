#!/bin/bash

#g++ -I /opt/anaconda3/envs/rdlcpp/include -L /home/leofaber/Documents/inaf/tasks/rta-dq-lib-c++/deps/CMake-hdf5-1.10.5-install/lib -lhdf5 -lhdf5_cpp src/hdf5_lib_test.cpp -o hdf5_lib_test

g++ -I /opt/anaconda3/envs/rdlcpp/include -I include -L /home/leofaber/Documents/inaf/tasks/rta-dq-lib-c++/deps/CMake-hdf5-1.10.5-install/lib -lhdf5 -lhdf5_cpp src/read_lst_dl1_hdf5.cpp src/lst_dl1.cpp -o read_lst_dl1_hdf5
