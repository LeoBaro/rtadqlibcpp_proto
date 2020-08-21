#ifndef HDF5_READING_COMPOUND_SCALAR_FIELD_STRATEGY_HPP
#define HDF5_READING_COMPOUND_SCALAR_FIELD_STRATEGY_HPP

#include "H5Cpp.h"
using namespace H5;


#include "HDF5ReadingCompoundFieldStrategy.hpp"

template <class T> 
class HDF5ReadingCompoundScalarFieldStrategy: public HDF5ReadingCompoundFieldStrategy<T> {

    public:

        HDF5ReadingCompoundScalarFieldStrategy(ParamsForHDF5CompoundFieldReading & params) 
        {
            this->compound_field_data = new float[ params.how_many ];
        }

        T* exec(ExecutionParams & params);
};


/**
 * This method opens an HDF5 file and reads a scalar field of a compound dataset element.
 *
 * This output array is allocated by the class' constructor.
 * 
 * @param params an object of class ParamsForHDF5CompoundFieldReading
 */
template <class T>
T* HDF5ReadingCompoundScalarFieldStrategy<T>::exec(ExecutionParams & params) {
    
    ParamsForHDF5CompoundFieldReading & cf_params = (ParamsForHDF5CompoundFieldReading &) params;

    this->file    = new H5File  (cf_params.file_name, H5F_ACC_RDONLY);
    this->group   = new Group   (this->file->openGroup(cf_params.group_name));
    this->dataset = new DataSet (this->group->openDataSet(cf_params.dataset_name));

    CompType field_type( sizeof(T) );
        field_type.insertMember( cf_params.field_name, 0, PredType::NATIVE_FLOAT);

    Exception::dontPrint(); // should be centralized

    try  
    {
        this->dataset->read(this->compound_field_data, field_type);
    }
    // catch failure caused by the H5File operations
    catch( Exception error )
    {   
        error.printErrorStack();
    }

    delete this->dataset;
    delete this->group;
    delete this->file;

    return this->compound_field_data;
}


#endif