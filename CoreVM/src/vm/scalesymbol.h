#ifndef _SCALE_SYMBOL_DEF_H_
#define _SCALE_SYMBOL_DEF_H_
#include "compositesymbol.h"

namespace VM {
  class ScaleSymbol: public CompositeSymbol {
  private:
    CompositeSymbol* _symbol;
    int _scalar;
  protected:
  	void addToConstraint(Constraints::Constraint& constraint);
  public:
    ScaleSymbol(CompositeSymbol* symbol, int scalar);
    virtual ~ScaleSymbol();

    
  };
}

#endif //_SCALE_SYMBOL_DEF_H_
