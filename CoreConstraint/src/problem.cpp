#include "problem.h"

using namespace Constraints;

Problem::Problem() {
	_lastv = 0;
}

Problem::~Problem() {}

Variable Problem::createVariable(std::string const& name) {
	return Variable(name, _lastv++);
}

void Problem::addConstraint(Constraint const& constraint) {
	_constraints.push_back(constraint);
}

std::string Problem::toString() const {
	std::string result;
	result = "Problem\n";

	for (unsigned int i = 0; i < _constraints.size(); i++) {
		result += _constraints[i].toString() + "\n";
	}

	return result;
}