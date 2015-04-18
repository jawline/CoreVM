#include "problem.h"

using namespace Constraints;

Problem::Problem() {
	_lastv = 0;
}

Problem::~Problem() {}

Variable Problem::createVariable() {
	return Variable(_lastv++);
}

void Problem::addConstraint(Constraint const& constraint) {
	_constraints.push_back(constraint);
}