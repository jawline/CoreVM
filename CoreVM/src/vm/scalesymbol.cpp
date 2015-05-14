#include "scalesymbol.h"

using namespace VM;

ScaleSymbol(CompositeSymbol* symbol, int scalar) {
  _symbol = symbol;
  _scalar = scalar;
}

ScaleSymbol::~ScaleSymbol() {
  delete _symbol;
}
