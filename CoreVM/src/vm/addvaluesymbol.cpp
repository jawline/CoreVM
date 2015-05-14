#include "addvaluesymbol.h"

using namespace VM;

AddValueSymbol::AddValueSymbol(CompositeSymbol* symbol, int value) {
  _symbol = symbol;
  _value = value;
}

AddValueSymbol::~AddValueSymbol() {
  delete _symbol;
}
