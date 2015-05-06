#ifndef _COLUMN_DEF_H_
#define _COLUMN_DEF_H_
#include <string>

namespace Simplex {
  class Column {
    private:
      std::string _name;
      bool _artificial;
    public:
      Column();
      Column(std::string const& name);
      Column(char const* name, size_t len);
      ~Column();

      void setArtificial(bool a);
      bool isArtificial() const;
      std::string getName() const;
  };
}

#endif //_COLUMN_DEF_H_
