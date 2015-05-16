#include "referencesymbol.h"

using namespace VM;

ReferenceSymbol::ReferenceSymbol(Constraints::Variable var) {
  _variable = var;
}

ReferenceSymbol::~ReferenceSymbol() {}

void ReferenceSymbol::addToConstraint(Constraints::Constraint& constraint) {
}