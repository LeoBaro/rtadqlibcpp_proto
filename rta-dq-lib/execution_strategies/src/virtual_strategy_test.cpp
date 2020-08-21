#include <iostream>
using std::cout;
using std::endl;

#include <chrono>

#include <string>
using std::string;

#include "ExecutionParams.hpp"
#include "HDF5ReadingCompoundFieldStrategy.hpp"


void run(HDF5ReadingCompoundFieldStrategy<float *> & strat, ParamsForHDF5CompoundFieldReading & params, string field_name) {
    auto t1 = std::chrono::high_resolution_clock::now();
    float * p = strat.exec(params);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    cout << "==> H5DF reading '"<<field_name<<"' field took: " << duration << "ms." << endl;
    for(int i=0; i<1; i++) cout << p[i] << " ";
    delete p;
}


int main() {

    string file_name = "/data/dl1_LST-1.1.Run01927.0033.fits.h5";
    //string file_name = "/home/leofaber/dl1_LST-1.1.Run01927.0033.fits.h5";
    //string file_name = "/dev/shm/dl1_LST-1.1.Run01927.0033.fits.h5";
    string group_name = "/dl1/event/telescope/image";
    string dataset_name = "LST_LSTCam";


    HDF5ReadingCompoundFieldStrategy<float *> strat;


    ParamsForHDF5CompoundFieldReading rcf_params_for_image(file_name, group_name, dataset_name, "image", 52999, 1855);
    ParamsForHDF5CompoundFieldReading rcf_params_for_event_id(file_name, group_name, dataset_name, "event_id", 52999, 1);
    ParamsForHDF5CompoundFieldReading rcf_params_for_num_trig_pix(file_name, group_name, dataset_name, "num_trig_pix", 52999, 1);
    ParamsForHDF5CompoundFieldReading rcf_params_for_obs_id(file_name, group_name, dataset_name, "obs_id", 52999, 1);
    ParamsForHDF5CompoundFieldReading rcf_params_for_pulse_time(file_name, group_name, dataset_name, "pulse_time", 52999, 1855);
    ParamsForHDF5CompoundFieldReading rcf_params_for_tel_id(file_name, group_name, dataset_name, "tel_id", 52999, 1);
    ParamsForHDF5CompoundFieldReading rcf_params_for_trigger_type(file_name, group_name, dataset_name, "trigger_type", 52999, 1);
    ParamsForHDF5CompoundFieldReading rcf_params_for_trigger_time(file_name, group_name, dataset_name, "trigger_time", 52999, 1);

    
    run(strat, rcf_params_for_image, "image");
    run(strat, rcf_params_for_event_id, "event_id");
    run(strat, rcf_params_for_num_trig_pix, "num_trig_pix");
    run(strat, rcf_params_for_obs_id, "obs_id");
    run(strat, rcf_params_for_pulse_time, "pulse_time");
    run(strat, rcf_params_for_tel_id, "tel_id");
    run(strat, rcf_params_for_trigger_type, "trigger_type");
    run(strat, rcf_params_for_trigger_time, "trigger_time");
    

    return 0;
}