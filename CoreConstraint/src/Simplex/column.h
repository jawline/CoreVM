#ifndef _COLUMN_DEF_H_
#define _COLUMN_DEF_H_
#include <string>

namespace Simplex {
  class Column {
    private:
      std::string _name;
    public:
      Column(std::string const& name);
      ~Column();
  }
}

#endif //_COLUMN_DEF_H_
