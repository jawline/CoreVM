#ifndef _COMPOSITE_SYMBOL_DEF_H_
#define _COMPOSITE_SYMBOL_DEF_H_
#include <CoreCS/problem.h>

namespace VM {
  
  enum CompositeSymbolType {
    Scale, Add, AddValue, Reference
  };

  class CompositeSymbol {
  protected:
    virtual void addToConstraint(Constraints::Constraint& constraint) = 0;

  public:
    CompositeSymbol();
    virtual ~CompositeSymbol();

    void buildConstraint(Constraints::Constraint& constraint, Constraints::ComparisonType type, int32_t result);
  };
}

#endif //_COMPOSITE_SYMBOL_DEF_H_
