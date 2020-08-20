#ifndef EXECUTION_STRATEGY_HPP
#define EXECUTION_READING_STRATEGY_HPP

#include "ExecutionParams.hpp"

template <typename T>
class ExecutionStrategy {

    public: 

        virtual T exec(ExecutionParams &) = 0;

};

#endif