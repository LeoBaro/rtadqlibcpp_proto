#include <iostream>
#include <string>

#include "datatypes.h"

int main(int argc, char* argv[]) {

  // Check the number of parameters
  if (argc < 2) {
      // Tell the user how to run the program
      std::cerr << "Usage: " << argv[0] << " PATH TO XML FILE" << std::endl;
      return 1;
  }
  // Print the user's name:
  std::cout << argv[0] << "started, " << argv[1] << " is going to be parsed!" << std::endl;

  const char * xml_file_path = argv[1];

  Datatypes * dts = Datatypes::Instance();
  dts->load_datatypes_from_xml(xml_file_path);

  return 0;
}
