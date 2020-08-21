#ifndef EXECUTION_PARAMS_HPP
#define EXECUTION_PARAMS_HPP

#include <string>
using std::string;


class ExecutionParams {

};


class ParamsForHDF5CompoundFieldReading: public ExecutionParams {
    
    public:

        ParamsForHDF5CompoundFieldReading(string file_name, string group_name, string dataset_name, string field_name, int how_many, int field_size) 
                    
            : file_name(file_name), group_name(group_name), dataset_name(dataset_name), field_name(field_name), how_many(how_many), field_size(field_size) {}

        string file_name;
        string group_name;
        string dataset_name;
        string field_name;
        int how_many;
        int field_size;
};



class OPParams: public ExecutionParams {

};

#endif