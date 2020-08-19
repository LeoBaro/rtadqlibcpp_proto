#ifndef LSTDL1_H
#define LSTDL1_H

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;

#include <bits/stdc++.h>


#include "H5Cpp.h"
using namespace H5;


const int IMAGE_SIZE = 1855;

typedef struct lst_dl1_image {

  long long int event_id;
  double image[IMAGE_SIZE];
  long long int num_trig_pix;
  long long int obs_id;
  double pulse_time[IMAGE_SIZE];
  long long int tel_id;
  double trigger_time[1];
  long long int trigger_type;

} lst_dl1_image;

class LST_DL1 {

  public:

    LST_DL1();

    void create_compound();

    void read_compound_field_as_array();
    void read_compound_field_as_matrix();
    void read_compound_field_as_static_matrix();

    std::shared_ptr<lst_dl1_image> read_data_from_hdf5(string filename, string group, string dataset, int how_many);

    int * read_field_from_hdf5(string filename, string group, string dataset, int how_many);



  private:

    std::shared_ptr<lst_dl1_image> data;
    clock_t start, end;

};


#endif
