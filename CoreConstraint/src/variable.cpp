#include "variable.h"

using namespace Constraints;

Variable::Variable(unsigned int index) {
	_index = index;
}

Variable::~Variable() {}

unsigned int Variable::getIndex() const {
	return _index;
}