#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Field {

  public:
    string name, data_shape, data_type, unit_of_measure;
    int x_dim, y_dim;

    Field(string name, string data_type, string data_shape, int x_dim, int y_dim, string unit_of_measure) {
      this->name = name;
      this->data_type = data_type;
      this->data_shape = data_shape;
      this->x_dim = x_dim;
      this->y_dim = y_dim;
      this->unit_of_measure = unit_of_measure;
    }

    void check() {

      if(this->name.empty()) {
        cout << "[Field] check() -> 'name' is NULL or EMPTY." << endl;
        exit(1);
      }

      if(this->data_type.empty()) {
        cout << "[Field] check() -> 'data_type' is NULL or EMPTY." << endl;
        exit(1);
      }

      if(this->data_shape.empty()) {
        cout << "[Field] check() -> 'data_shape' is NULL or EMPTY." << endl;
        exit(1);
      }

      if(this->data_shape == "array1d" && this->x_dim == 0) {
        cout << "[Field] check() -> data_shape is 'array1d' but x_dim is 0." << endl;
        exit(1);
      }

      if(this->data_shape == "array2d") {
        if(this->x_dim == 0) {
          cout << "[Field] check() -> data_shape is 'array2d' but x_dim is 0." << endl;
          exit(1);
        }
        if(this->x_dim == 0) {
          cout << "[Field] check() -> data_shape is 'array2d' but y_dim is 0." << endl;
          exit(1);
        }
      }
    }


};
