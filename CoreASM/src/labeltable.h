#ifndef _LABEL_TABLE_DEF_H_
#define _LABEL_TABLE_DEF_H_
#include <string>
#include <cstddef>
#include <map>

namespace Assembler {
  class LabelTable {
    private:
      std::map<std::string, size_t> _currentLabels;

    public:
    
      /**
       * Set the label to the specified position
       */
      void setLabel(std::string const& labelName, size_t position);
      
      /**
       * If the label exists then returns true and sets position to the start of the label
       * If the label does not exist return false
       */
      bool getLabel(std::string const& labelName, size_t& position);
  };
}

#endif //_LABEL_TABLE_DEF_H_
