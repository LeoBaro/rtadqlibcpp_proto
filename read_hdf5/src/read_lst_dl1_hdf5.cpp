#include "lst_dl1.h"

int main(void) {


  string filename = "/data/dl1_LST-1.1.Run01927.0033.fits.h5";
  //string filename = "/home/leofaber/dl1_LST-1.1.Run01927.0033.fits.h5";
  //string filename = "/dev/shm/dl1_LST-1.1.Run01927.0033.fits.h5";

  string group = "/dl1/event/telescope/image";
  string dataset = "LST_LSTCam";
  int events = 52999;

  LST_DL1 lst_dl1;

  //auto data = lst_dl1.read_data_from_hdf5(filename, group, dataset, events);


  //auto data = lst_dl1.read_field_from_hdf5(filename, group, dataset, events);
  
  lst_dl1.create_compound();

  lst_dl1.read_compound_field_as_array();

  //lst_dl1.read_compound_field_as_static_matrix();

  lst_dl1.read_compound_field_as_matrix();

  // cout << data << endl;
}
