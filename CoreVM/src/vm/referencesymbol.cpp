#include "referencesymbol.h"

using namespace VM;

ReferenceSymbol::ReferenceSymbol(Constraints::Variable var) {
  _variable = var;
}

ReferenceSymbol::~ReferenceSymbol() {}
