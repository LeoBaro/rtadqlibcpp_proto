#include <iostream>
using std::cout;
using std::endl;

#include <chrono>

#include <string>
using std::string;

#include "ExecutionParams.hpp"
#include "HDF5ReadingCompoundScalarFieldStrategy.hpp"
#include "HDF5ReadingCompoundArrayFieldStrategy.hpp"


void run(HDF5ReadingCompoundFieldStrategy<float> & strat, ParamsForHDF5CompoundFieldReading & params, string field_name, int print_samples=1) {
    auto t1 = std::chrono::high_resolution_clock::now();
    float * p = strat.exec(params);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    cout << "==> H5DF reading '"<<field_name<<"' field took: " << duration << "ms. Samples: ";
    for(int i = 0; i < print_samples; i++) cout << p[i] << " ";
    cout << endl;
    delete p;
}


int main() {

    string file_name = "/data/dl1_LST-1.1.Run01927.0033.fits.h5";
    //string file_name = "/home/leofaber/dl1_LST-1.1.Run01927.0033.fits.h5";
    //string file_name = "/dev/shm/dl1_LST-1.1.Run01927.0033.fits.h5";
    string group_name = "/dl1/event/telescope/image";
    string dataset_name = "LST_LSTCam";


    // scalar fields
    ParamsForHDF5CompoundFieldReading params_for_event_id(file_name, group_name, dataset_name, "event_id", 52999, 1);
    HDF5ReadingCompoundScalarFieldStrategy<float> event_id_reader(params_for_event_id);


    ParamsForHDF5CompoundFieldReading params_for_num_trig_pix(file_name, group_name, dataset_name, "num_trig_pix", 52999, 1);
    HDF5ReadingCompoundScalarFieldStrategy<float> num_trig_pix_reader(params_for_num_trig_pix);


    ParamsForHDF5CompoundFieldReading params_for_obs_id(file_name, group_name, dataset_name, "obs_id", 52999, 1);
    HDF5ReadingCompoundScalarFieldStrategy<float> obs_id_reader(params_for_obs_id);


    ParamsForHDF5CompoundFieldReading params_for_tel_id(file_name, group_name, dataset_name, "tel_id", 52999, 1);
    HDF5ReadingCompoundScalarFieldStrategy<float> tel_id_reader(params_for_tel_id);


    ParamsForHDF5CompoundFieldReading params_for_trigger_type(file_name, group_name, dataset_name, "trigger_type", 52999, 1);
    HDF5ReadingCompoundScalarFieldStrategy<float> trigger_type_reader(params_for_trigger_type);



    // array fields

    ParamsForHDF5CompoundFieldReading params_for_image(file_name, group_name, dataset_name, "image", 52999, 1855);
    HDF5ReadingCompoundArrayFieldStrategy<float> image_reader(params_for_image);

    ParamsForHDF5CompoundFieldReading params_for_pulse_time(file_name, group_name, dataset_name, "pulse_time", 52999, 1855);
    HDF5ReadingCompoundArrayFieldStrategy<float> pulse_time_reader(params_for_pulse_time);

    ParamsForHDF5CompoundFieldReading params_for_trigger_time(file_name, group_name, dataset_name, "trigger_time", 52999, 1);
    HDF5ReadingCompoundArrayFieldStrategy<float> trigger_time_reader(params_for_trigger_time);

    


    // reading scalar fields
    run(event_id_reader, params_for_event_id, "event_id");
    run(num_trig_pix_reader, params_for_num_trig_pix, "num_trig_pix");
    run(obs_id_reader, params_for_obs_id, "obs_id");
    run(tel_id_reader, params_for_tel_id, "tel_id");
    run(trigger_type_reader, params_for_trigger_type, "trigger_type");

    // reading array fields
    run(image_reader, params_for_image, "image");
    run(pulse_time_reader, params_for_pulse_time, "pulse_time");
    run(trigger_time_reader, params_for_trigger_time, "trigger_time");

    

    return 0;
}