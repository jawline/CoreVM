#ifndef _REFERENCE_SYMBOL_DEF_H_
#define _REFERENCE_SYMBOL_DEF_H_
#include "compositesymbol.h"
#include <CoreCS/problem.h>

namespace VM {
  class ReferenceSymbol : public CompositeSymbol {
  private:
    Constraints::Variable _variable;
  public:
    ReferenceSymbol(Constraints::Variable var);
    virtual ~ReferenceSymbol();
  };
}

#endif //_REFERENCE_SYMBOL_DEF_H_
