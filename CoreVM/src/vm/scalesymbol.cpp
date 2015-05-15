#include "scalesymbol.h"

using namespace VM;

ScaleSymbol::ScaleSymbol(CompositeSymbol* symbol, int scalar) {
  _symbol = symbol;
  _scalar = scalar;
}

ScaleSymbol::~ScaleSymbol() {
  delete _symbol;
}

void ScaleSymbol::addToConstraint(Constraints::Constraint& constraint) {
}