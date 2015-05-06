#include "variable.h"

using namespace Constraints;

Variable::Variable() {
	_name = "INVALID";
	_index = -1;
}

Variable::Variable(std::string const& name, bool isSigned, unsigned int index) {
	_name = name;
	_isSigned = isSigned;
	_index = index;
}

Variable::~Variable() {}

unsigned int Variable::getIndex() const {
	return _index;
}

std::string Variable::toString() const {
	return _name;
}

bool Variable::isSigned() const {
	return _isSigned;
}