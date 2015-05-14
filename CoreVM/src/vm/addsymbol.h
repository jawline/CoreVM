#ifndef _ADD_SYMBOL_DEF_H_
#define _ADD_SYMBOL_DEF_H_
#include "compositesymbol.h"

namespace VM {
  class AddSymbol: public CompositeSymbol {
  private:
    CompositeSymbol* _symbol1;
    CompositeSymbol* _symbol2;
  public:
    AddSymbol(CompositeSymbol* symbol1, CompositeSymbol* symbol2);
    virtual ~AddSymbol();
  }
}

#endif //_ADD_SYMBOL_DEF_H_
