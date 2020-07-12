#include <iostream>
#include <vector>
#include <assert.h>

#include "tinyxml.h"
#include "datatype.h"

using std::string;
using std::vector;
using std::shared_ptr;

class Datatypes
{
    public:
        static Datatypes * Instance();
        void load_datatypes_from_xml(const char * xml_file_path);
        shared_ptr<Datatype> getDatatype(string datatype_id);

    private:
        Datatypes() {}
        static Datatypes * _instance;
        vector< shared_ptr<Datatype> > datatypes;
        shared_ptr<Datatype> parse_datatype(TiXmlNode* datatypeElem);




    public:
        Datatypes(Datatypes const&)       = delete;
        void operator=(Datatypes const&)  = delete;
};
