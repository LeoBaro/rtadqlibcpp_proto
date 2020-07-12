#include <string>
#include <vector>
#include <memory>

#include "field.h"

using std::string;

class Datatype {

public:

	string id, id_field, time_field, description;
	std::vector<std::shared_ptr<Field>> fields;

	Datatype(string id, string id_field, string time_field, string description) {
		this->id = id;
		this->id_field = id_field;
		this->time_field = time_field;
		this->description = description;
	}

	void add_field(string name, string data_type, string data_shape, int x_dim, int y_dim, string unit_of_measure) {

		auto field = std::shared_ptr<Field>(new Field(name, data_type, data_shape, x_dim, y_dim, unit_of_measure));

		this->fields.push_back(field);
	}

	void check() {
		if(this->id.empty()) {
			cout << "[Datatype] check() -> 'id' is NULL or EMPTY." << endl;
			exit(1);
		}
		if(this->id_field.empty()) {
			cout << "[Datatype] check() -> 'id_field' is NULL or EMPTY." << endl;
			exit(1);
		}
		if(this->time_field.empty()) {
			cout << "[Datatype] check() -> 'time_field' is NULL or EMPTY." << endl;
			exit(1);
		}

		// check for child elements
		for(auto it = std::begin(fields); it != std::end(fields); ++it) {
				std::shared_ptr<Field> field_ptr = *it;
				field_ptr->check();
		}
	}


};
