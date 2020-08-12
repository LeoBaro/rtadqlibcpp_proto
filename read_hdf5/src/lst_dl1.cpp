#include "lst_dl1.h"

LST_DL1::LST_DL1() {

}

std::shared_ptr<lst_dl1_image> LST_DL1::read_data_from_hdf5(string file_name, string group_name, string dataset_name, int how_many) {

  start = clock();

  lst_dl1_image * d = new lst_dl1_image[how_many];

  Exception::dontPrint();

  try  {

    H5File  * file    = new H5File  (file_name, H5F_ACC_RDONLY);
    Group   * group   = new Group   (file->openGroup(group_name));
    DataSet * dataset = new DataSet (group->openDataSet(dataset_name));

    hsize_t adims[1] = { 1855 };
    hid_t loctype = H5Tarray_create(H5T_NATIVE_FLOAT, 1, adims);
    hsize_t adims2[1] = { 1 };
    hid_t loctype2 = H5Tarray_create (H5T_NATIVE_DOUBLE, 1, adims2);

    // Creating the memory type
    CompType lst_dl1_mtype( sizeof(lst_dl1_image) );

      lst_dl1_mtype.insertMember( "event_id", HOFFSET(lst_dl1_image, event_id), PredType::NATIVE_INT);
      lst_dl1_mtype.insertMember( "image", HOFFSET(lst_dl1_image, image), loctype);
      lst_dl1_mtype.insertMember( "num_trig_pix", HOFFSET(lst_dl1_image, num_trig_pix), PredType::NATIVE_INT);
      lst_dl1_mtype.insertMember( "obs_id", HOFFSET(lst_dl1_image, obs_id), PredType::NATIVE_INT);
      lst_dl1_mtype.insertMember( "pulse_time", HOFFSET(lst_dl1_image, pulse_time), loctype);
      lst_dl1_mtype.insertMember( "tel_id", HOFFSET(lst_dl1_image, tel_id), PredType::NATIVE_INT);
      lst_dl1_mtype.insertMember( "trigger_time", HOFFSET(lst_dl1_image, trigger_time), loctype2);
      lst_dl1_mtype.insertMember( "trigger_type", HOFFSET(lst_dl1_image, trigger_type), PredType::NATIVE_INT);
      

    //std::ios_base::sync_with_stdio(false); // unsync the I/O of C and C++.
    dataset->read(d, lst_dl1_mtype);

    delete dataset;
    delete group;
    delete file;

  }  // end of try block

  // catch failure caused by the H5File operations
  catch( FileIException error )
  {
     error.printErrorStack();
     return nullptr;
  }

  // catch failure caused by the DataSet operations
  catch( DataSetIException error )
  {
     error.printErrorStack();
     return nullptr;
  }

  // catch failure caused by the DataSpace operations
  catch( DataSpaceIException error )
  {
     error.printErrorStack();
     return nullptr;
  }

  // catch failure caused by the DataSpace operations
  catch( DataTypeIException error )
  {
     error.printErrorStack();
     return nullptr;
  }

  end = clock();

  double time_taken = double(end - start) / double(CLOCKS_PER_SEC);

  cout << "[LST_DL1] Reading data took: " << std::fixed
       << time_taken << std::setprecision(5);
  cout << " sec " << endl;


  return std::shared_ptr<lst_dl1_image>(data);
}
