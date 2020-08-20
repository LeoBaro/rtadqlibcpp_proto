#include <iostream>
using std::cout;
using std::endl;

#include <chrono>

#include "ExecutionParams.hpp"
#include "HDF5ReadingCompoundFieldStrategy.hpp"



int main() {

    string file_name = "/data/dl1_LST-1.1.Run01927.0033.fits.h5";
    //string file_name = "/home/leofaber/dl1_LST-1.1.Run01927.0033.fits.h5";
    //string file_name = "/dev/shm/dl1_LST-1.1.Run01927.0033.fits.h5";
    string group_name = "/dl1/event/telescope/image";
    string dataset_name = "LST_LSTCam";



    HDF5ReadingCompoundFieldStrategy<float *> strat;


    ParamsForHDF5CompoundFieldReading rcf_params_for_image(file_name, group_name, dataset_name, "image", 52999, 1855);
    ParamsForHDF5CompoundFieldReading rcf_params_for_event_id(file_name, group_name, dataset_name, "event_id", 52999, 1);



    auto t1 = std::chrono::high_resolution_clock::now();
    float * p = strat.exec(rcf_params_for_image);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    cout << "==> H5DF reading image field took: " << duration << "ms." << endl;
    delete p;



    t1 = std::chrono::high_resolution_clock::now();
    p = strat.exec(rcf_params_for_event_id);
    t2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    cout << "==> H5DF reading image field took: " << duration << "ms." << endl;



    for(int i=0; i<10; i++)
        cout << p[i] << " ";

    delete p;

    return 0;
}