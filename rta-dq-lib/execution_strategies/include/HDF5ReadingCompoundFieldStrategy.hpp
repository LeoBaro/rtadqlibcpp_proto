#ifndef HDF5_READING_COMPOUND_FIELD_STRATEGY_HPP
#define HDF5_READING_COMPOUND_FIELD_STRATEGY_HPP

#include "H5Cpp.h"
using namespace H5;


#include "HDF5ReadingStrategy.hpp"

template <class T> 
class HDF5ReadingCompoundFieldStrategy: public HDF5ReadingStrategy<T> {

    public:

        T exec(ExecutionParams & params);
};


template <class T>
T HDF5ReadingCompoundFieldStrategy<T>::exec(ExecutionParams & params) {
    
    ParamsForHDF5CompoundFieldReading & cf_params = (ParamsForHDF5CompoundFieldReading &) params;

    float * data = new float[ cf_params.how_many * cf_params.field_size ];

    H5File  * file    = new H5File  (cf_params.file_name, H5F_ACC_RDONLY);
    Group   * group   = new Group   (file->openGroup(cf_params.group_name));
    DataSet * dataset = new DataSet (group->openDataSet(cf_params.dataset_name));

    CompType field_type( sizeof(float) * cf_params.field_size );

    if(cf_params.field_size > 1) 
    {   
        hsize_t adims[1] = { cf_params.field_size };
        hid_t loctype = H5Tarray_create(H5T_NATIVE_FLOAT, 1, adims);
        field_type.insertMember(cf_params.field_name, 0, loctype);
    }
    else
    {
        field_type.insertMember( cf_params.field_name, 0, PredType::NATIVE_FLOAT);
    }

    dataset->read(data, field_type);

    delete dataset;
    delete group;
    delete file;

    return data;
}

#endif