#include "lst_dl1.h"

#include <chrono>

LST_DL1::LST_DL1() {

}

#include "hdf5.h"
#define H5FILE_NAME          "SDScompound.h5"
#define DATASETNAME   "ArrayOfStructures"
#define LENGTH        10
#define RANK          1
#define ARRSIZE        10


typedef struct s1_t {
   int    a;
   float  b;
   double c; 
   float arr[ARRSIZE];
} s1_t;

void LST_DL1::create_compound() {


   int        i;
   hid_t      file, dataset, space; /* Handles */
   herr_t     status;
   hsize_t    dim[] = {LENGTH};   /* Dataspace dimensions */

   s1_t       s1[LENGTH];
   hid_t      s1_tid;   


   
   /*
   * Initialize the data
   */
   for (i = 0; i < LENGTH; i++) {
   s1[i].a = i;
   s1[i].b = i*i;
   s1[i].c = 1./(i+1);
   for (int j = 0; j < ARRSIZE; j++) {
         cout << i+j << " "; 
         s1[i].arr[j] = i+j;
      }
      cout << endl;
   }

   /*
   * Create the data space.
   */
   space = H5Screate_simple(RANK, dim, NULL);

   /*
   * Create the file.
   */
   file = H5Fcreate(H5FILE_NAME, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

   /*
   * Create the memory data type.
   */
   hsize_t adims[1] = { ARRSIZE };
   hid_t loctype = H5Tarray_create(H5T_NATIVE_FLOAT, 1, adims);

   s1_tid = H5Tcreate (H5T_COMPOUND, sizeof(s1_t));
   H5Tinsert(s1_tid, "a_name", HOFFSET(s1_t, a), H5T_NATIVE_INT);
   H5Tinsert(s1_tid, "c_name", HOFFSET(s1_t, c), H5T_NATIVE_DOUBLE);
   H5Tinsert(s1_tid, "b_name", HOFFSET(s1_t, b), H5T_NATIVE_FLOAT);
   H5Tinsert(s1_tid, "arr_name", HOFFSET(s1_t, arr), loctype);

   /*
   * Create the dataset.
   */
   dataset = H5Dcreate2(file, DATASETNAME, s1_tid, space, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

   /*
   * Wtite data to the dataset;
   */
   status = H5Dwrite(dataset, s1_tid, H5S_ALL, H5S_ALL, H5P_DEFAULT, s1);

   /*
   * Release resources
   */
   H5Tclose(s1_tid);
   H5Sclose(space);
   H5Dclose(dataset);
   H5Fclose(file);

}

void LST_DL1::read_compound_field_as_array() {

   /* Third "structure" ( will be used to read float field of s1) */
   hid_t      s3_tid;   /* Memory datatype handle */
   float *    s3 = new float[LENGTH];

   int        i;
   hid_t      file, dataset, space; /* Handles */
   herr_t     status;
   hsize_t    dim[] = {LENGTH};   /* Dataspace dimensions */


   /*
   * Open the file and the dataset.
   */
   file = H5Fopen(H5FILE_NAME, H5F_ACC_RDONLY, H5P_DEFAULT);

   dataset = H5Dopen2(file, DATASETNAME, H5P_DEFAULT);

   /*
   * Create a data type for s3.
   */
   s3_tid = H5Tcreate(H5T_COMPOUND, sizeof(float));

   status = H5Tinsert(s3_tid, "b_name", 0, H5T_NATIVE_FLOAT);

   /*
   * Read field b from s1 dataset. Field in the file is found by its name.
   */
   status = H5Dread(dataset, s3_tid, H5S_ALL, H5S_ALL, H5P_DEFAULT, s3);

   /*
   * Display the field
   */
   printf("\n");
   printf("Field b : \n");
   for( i = 0; i < LENGTH; i++) printf("%.4f ", s3[i]);
   printf("\n");

   /*
   * Release resources
   */
   delete s3;
   H5Tclose(s3_tid);
   H5Dclose(dataset);
   H5Fclose(file);

}

void LST_DL1::read_compound_field_as_static_matrix() {
   /* Third "structure" ( will be used to read float field of s1) */
   hid_t      s3_tid;   /* Memory datatype handle */


   float s3[LENGTH][ARRSIZE];

   int        i;
   hid_t      file, dataset, space; /* Handles */
   herr_t     status;
   hsize_t    dim[] = {LENGTH};   /* Dataspace dimensions */


   /*
   * Open the file and the dataset.
   */
   file = H5Fopen(H5FILE_NAME, H5F_ACC_RDONLY, H5P_DEFAULT);

   dataset = H5Dopen2(file, DATASETNAME, H5P_DEFAULT);

   /*
   * Create a data type for s3.
   */

   s3_tid = H5Tcreate(H5T_COMPOUND, sizeof(float)*ARRSIZE);
   cout << "==> H5Tcreate status: " << status << endl;


   hsize_t adims[1] = { ARRSIZE };
   hid_t loctype = H5Tarray_create(H5T_NATIVE_FLOAT, 1, adims);

   status = H5Tinsert(s3_tid, "arr_name", 0, loctype);
   cout << "==> H5Tinsert status: " << status << endl;
   /*
   * Read field b from s1 dataset. Field in the file is found by its name.
   */
   status = H5Dread(dataset, s3_tid, H5S_ALL, H5S_ALL, H5P_DEFAULT, s3);
   cout << "==> H5Dread status: " << status << endl;

   /*
   * Display the field
   */
   printf("\n");
   printf("Field array : \n");

   
   for( i = 0; i < LENGTH; i++){
      for(int j=0; j < ARRSIZE; j++) {
         printf("%.4f ", s3[i][j]);
      }
      printf("\n");
   } 
   

  /*
   for( i = 0; i < LENGTH*ARRSIZE; i++){
      printf("%.4f ", s3[i]);
   }
   */
   printf("\n");

   /*
   * Release resources
   */
   //delete s3;
   H5Tclose(s3_tid);
   H5Dclose(dataset);
   H5Fclose(file);
}

void LST_DL1::read_compound_field_as_matrix() {

   /* Third "structure" ( will be used to read float field of s1) */
   hid_t      s3_tid;   /* Memory datatype handle */


   float* s3 = new float[LENGTH*ARRSIZE];
   
   int        i;
   hid_t      file, dataset, space; /* Handles */
   herr_t     status;
   hsize_t    dim[] = {LENGTH};   /* Dataspace dimensions */

   /*
   * Open the file and the dataset.
   */
   file = H5Fopen(H5FILE_NAME, H5F_ACC_RDONLY, H5P_DEFAULT);

   dataset = H5Dopen2(file, DATASETNAME, H5P_DEFAULT);

   s3_tid = H5Tcreate(H5T_COMPOUND, sizeof(float)*ARRSIZE);
   cout << "==> H5Tcreate status: " << status << endl;

   hsize_t adims[1] = { ARRSIZE };
   hid_t loctype = H5Tarray_create(H5T_NATIVE_FLOAT, 1, adims);

   status = H5Tinsert(s3_tid, "arr_name", 0, loctype);
   cout << "==> H5Tinsert status: " << status << endl;

   auto t1 = std::chrono::high_resolution_clock::now();

   status = H5Dread(dataset, s3_tid, H5S_ALL, H5S_ALL, H5P_DEFAULT, s3);

   auto t2 = std::chrono::high_resolution_clock::now();

   auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
   cout << "==> H5Dread status: " << status << "Took: " << duration << "ms." << endl;



   printf("\n");
   printf("Field array : \n");
   for( i = 0; i < LENGTH; i++){
      for(int j=0; j < ARRSIZE; j++) {
         printf("%.4f ", s3[i*LENGTH+j]);
      }
      printf("\n");
   } 

   printf("\n");

   delete s3;
   H5Tclose(s3_tid);
   H5Dclose(dataset);
   H5Fclose(file);

}

int * LST_DL1::read_field_from_hdf5(string file_name, string group_name, string dataset_name, int how_many) {
   
   start = clock();

   /* Third "structure" ( will be used to read int field of s1) */
   hid_t      s3_tid;   /* Memory datatype handle */
   int      s3[LENGTH];

   int        i;
   hid_t      file, dataset, space, group_id; /* Handles */
   herr_t     status;
   hsize_t    dim[] = {LENGTH};   /* Dataspace dimensions */

   /*
   * Open the file and the dataset.
   */
   file = H5Fopen(file_name.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
   group_id = H5Gopen (file, group_name.c_str(), H5P_DEFAULT);
   dataset = H5Dopen(file, dataset_name.c_str(), group_id);

   /* 
   * Create a data type for s3.
   */
   s3_tid = H5Tcreate(H5T_COMPOUND, sizeof(int));

   status = H5Tinsert(s3_tid, "b_name", 0, H5T_NATIVE_INT);

   /*
   * Read field b from s1 dataset. Field in the file is found by its name.
   */
   status = H5Dread(dataset, s3_tid, H5S_ALL, H5S_ALL, H5P_DEFAULT, s3);

   /*
   * Display the field
   */
   printf("\n");
   printf("Field b : \n");
   for( i = 0; i < LENGTH; i++) printf("%.4f ", s3[i]);
   printf("\n");

   /*
   * Release resources
   */

   H5Tclose(s3_tid);
   H5Dclose(dataset);
   H5Fclose(file);

   /*
   Exception::dontPrint();

   try  {

      
      H5File  * file    = new H5File  (file_name, H5F_ACC_RDONLY);
      Group   * group   = new Group   (file->openGroup(group_name));
      DataSet * dataset = new DataSet (group->openDataSet(dataset_name));

      int * s3 = new int[LENGTH];

      CompType int_field_memtype( sizeof(int) );
   
         int_field_memtype.insertMember("event_id", 0, PredType::NATIVE_INT);

      printf("Hi! \n");

      dataset->read(s3, int_field_memtype);

      printf("\n");
      printf("Field event_id : \n");
      for(int i = 0; i < LENGTH; i++) printf("%d ", s3[i]);
      printf("\n");


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
   */


   end = clock();

   double time_taken = double(end - start) / double(CLOCKS_PER_SEC);

   cout << "[LST_DL1] Reading data took: " << std::fixed << time_taken << std::setprecision(5);
   cout << " sec " << endl;

   return new int[10];
}

std::shared_ptr<lst_dl1_image> LST_DL1::read_data_from_hdf5(string file_name, string group_name, string dataset_name, int how_many) {

  start = clock();

  lst_dl1_image * d = new lst_dl1_image[how_many];

  Exception::dontPrint();

  try  {

    H5File  * file    = new H5File  (file_name, H5F_ACC_RDONLY);
    Group   * group   = new Group   (file->openGroup(group_name));
    DataSet * dataset = new DataSet (group->openDataSet(dataset_name));

    hsize_t adims[1] = { ARRSIZE };
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
