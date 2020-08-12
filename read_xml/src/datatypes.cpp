#include "datatypes.h"

Datatypes* Datatypes::_instance = 0;

Datatypes* Datatypes::Instance() {
  if (_instance == 0) {
    _instance = new Datatypes();
  }
  return _instance;
}

/**
 * A brief history of JavaDoc-style (C-style) comments.
 *
 * This is the typical JavaDoc-style C-style comment. It starts with two
 * asterisks.
 *
 * @param xml_file_path Even if there is only one possible unified theory. it is just a
 *                      set of rules and equations.
 */
void Datatypes::load_datatypes_from_xml(const char * xml_file_path) {

  TiXmlDocument doc( xml_file_path );

  bool loadOkay = doc.LoadFile();

  if(loadOkay) {

    TiXmlNode* root = &doc;
    if ( !root ) return;

    int t = root->Type();

    assert(t == TiXmlNode::TINYXML_DOCUMENT);

    TiXmlNode* declarationElem = root->FirstChild();

    assert(declarationElem->Type() == TiXmlNode::TINYXML_DECLARATION);

    TiXmlNode* datatypesElem = declarationElem->NextSibling();

    assert(datatypesElem->Type() == TiXmlNode::TINYXML_ELEMENT);

    for ( TiXmlNode* datatype_elem = datatypesElem->FirstChild(); datatype_elem != 0; datatype_elem = datatype_elem->NextSibling()) {

      t = datatype_elem->Type();

      assert(t == TiXmlNode::TINYXML_ELEMENT);

      std::cout << "<" << datatype_elem->Value() << ">" << std::endl;

      auto datatype = parse_datatype(datatype_elem);

      datatypes.push_back(datatype);

    }

  }
  else {
		std::cout << "Failed to load file " << xml_file_path << std::endl;
    exit(1);
	}
}

shared_ptr<Datatype> Datatypes::getDatatype(string datatype_id) {

  for(auto it = std::begin(datatypes); it != std::end(datatypes); ++it) {

      std::shared_ptr<Datatype> datatype_ptr = *it;

      if(datatype_ptr->id == datatype_id)

        return datatype_ptr;
  }

  return nullptr;
}




/*
  Private API
*/
string get_attribute_value(TiXmlElement * elem, const char * attribute_key) {
  const char * s_value = elem->Attribute(attribute_key);
  if(s_value != NULL)
    return string(s_value);
  else
    return string();
}

shared_ptr<Datatype> Datatypes::parse_datatype(TiXmlNode* datatype_node) {

  // get attributes from datatype_elem and pass them to the Datatype constructor

  TiXmlElement * datatype_elem = datatype_node->ToElement();

  string id = get_attribute_value(datatype_elem, "id");
  string id_field = get_attribute_value(datatype_elem, "id_field");
  string time_field = get_attribute_value(datatype_elem, "time_field");
  string desc = get_attribute_value(datatype_elem, "desc");

  auto dt = std::shared_ptr<Datatype>(new Datatype(id, time_field, id_field, desc));

  // parse attributes of the <field> child elements
  for ( TiXmlNode * field_node = datatype_node->FirstChild(); field_node != 0; field_node = field_node->NextSibling()) {

    TiXmlElement * field_node_elem = field_node->ToElement();

    string name = get_attribute_value(field_node_elem, "name");
    string data_type = get_attribute_value(field_node_elem, "data_type");
    string data_shape = get_attribute_value(field_node_elem, "data_shape");

    int x_dim;
    if(! field_node_elem->QueryIntAttribute("x_dim", &x_dim) == TIXML_SUCCESS)
      x_dim = 0;

    int y_dim;
    if(! field_node_elem->QueryIntAttribute("y_dim", &y_dim) == TIXML_SUCCESS)
      y_dim = 0;

    string unit_of_measure = get_attribute_value(field_node_elem, "unit_of_measure");

    dt->add_field(name, data_type, data_shape, x_dim, y_dim, unit_of_measure);
	}


  dt->check();

  return dt;
}
