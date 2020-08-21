#ifndef HDF5_READING_STRATEGY_HPP
#define HDF5_READING_STRATEGY_HPP

#include "ExecutionStrategy.hpp"

template <class T>
class HDF5ReadingStrategy : public ExecutionStrategy<T> {

    public:

        virtual T* exec(ExecutionParams & params) = 0;
};

#endif