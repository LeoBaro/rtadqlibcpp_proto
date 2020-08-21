#ifndef HDF5_READING_COMPOUND_FIELD_STRATEGY_HPP
#define HDF5_READING_COMPOUND_FIELD_STRATEGY_HPP

#include "H5Cpp.h"
using namespace H5;


#include "HDF5ReadingStrategy.hpp"

template <class T> 
class HDF5ReadingCompoundFieldStrategy: public HDF5ReadingStrategy<T> {

    public:
        
        virtual T* exec(ExecutionParams & params) = 0;

    protected:
        H5File  * file;
        Group   * group;
        DataSet * dataset;

        T* compound_field_data;
};


#endif