#include "addsymbol.h"

using namespace VM;

AddSymbol::AddSymbol(CompositeSymbol* symbol1, CompositeSymbol* symbol2) {
  _symbol1 = symbol1;
  _symbol2 = symbol2;
}

AddSymbol::~AddSymbol() {
  delete _symbol1;
  delete _symbol2;
}

void AddSymbol::addToConstraint(Constraints::Constraint& constraint) {}