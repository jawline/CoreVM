#include "variable.h"

using namespace Constraints;

Variable::Variable() {}
Variable::Variable(std::string const& name, bool isSigned) {
	_name = name;
	_isSigned = isSigned;
}

Variable::~Variable() {}

std::string Variable::toString() const {
	return _name;
}

bool Variable::isSigned() const {
	return _isSigned;
}
