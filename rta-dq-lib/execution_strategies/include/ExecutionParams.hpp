#ifndef EXECUTION_PARAMS_HPP
#define EXECUTION_PARAMS_HPP

#include <string>
using std::string;


class ExecutionParams {

};


class ParamsForHDF5Reading: public ExecutionParams {
    
    public:

        ParamsForHDF5Reading(string file_name, string group_name, string dataset_name) : file_name(file_name), group_name(group_name), dataset_name(dataset_name) {}

        string file_name;
        string group_name;
        string dataset_name;
};

class ParamsForHDF5CompoundFieldReading: public ParamsForHDF5Reading {
    
    public:

        ParamsForHDF5CompoundFieldReading(string file_name, string group_name, string dataset_name, string field_name, int how_many, int field_size = 1) 
                    
            : ParamsForHDF5Reading(file_name, group_name, dataset_name), field_name(field_name), how_many(how_many), field_size(field_size) {}

        string field_name;
        int how_many;
        int field_size;
};



class OPParams: public ExecutionParams {

};

#endif