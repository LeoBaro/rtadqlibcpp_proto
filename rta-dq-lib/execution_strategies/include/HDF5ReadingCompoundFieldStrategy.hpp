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

    herr_t     status;
    hid_t      file_tid, group_tid, dataset_tid, field_tid;

    file_tid = H5Fopen(cf_params.file_name.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
    group_tid = H5Gopen2(file_tid, cf_params.group_name.c_str(), H5P_DEFAULT);
    dataset_tid = H5Dopen2(group_tid, cf_params.dataset_name.c_str(), H5P_DEFAULT);

    field_tid = H5Tcreate(H5T_COMPOUND, sizeof(float) * cf_params.field_size);

    if(cf_params.field_size > 1) 
    {
        hsize_t adims[1] = { cf_params.field_size };
        hid_t loctype = H5Tarray_create(H5T_NATIVE_FLOAT, 1, adims);
        status = H5Tinsert(field_tid, cf_params.field_name.c_str(), 0, loctype);
    }
    else 
    {
        status = H5Tinsert(field_tid, cf_params.field_name.c_str(), 0, H5T_NATIVE_FLOAT);
    }

    status = H5Dread(dataset_tid, field_tid, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);

    H5Tclose(field_tid);
    H5Dclose(dataset_tid);
    H5Gclose(group_tid);
    H5Fclose(file_tid);

    return data;
}

#endif