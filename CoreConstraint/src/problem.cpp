#include "problem.h"

using namespace Constraints;

Problem::Problem() {
	_lastv = 0;
}

Problem::~Problem() {}

Variable Problem::createVariable(std::string const& name) {
	_variables.push_back(Variable(name, _lastv+1));
	return Variable(name, _lastv++);
}

void Problem::addConstraint(Constraint const& constraint) {
	_constraints.push_back(constraint);
}

bool Problem::isSatisfiable() const {
	return false;
}

std::string Problem::toString() const {
	std::string result;

	result = "Problem\n";

	if (_variables.size()) {
		for (unsigned int i = 0; i < _variables.size(); i++) {
			if (i) {
				result += ", ";
			}
			result += _variables[i].toString();
		}
		result += "\n";
	}

	if (_constraints.size()) {
		for (unsigned int i = 0; i < _constraints.size(); i++) {
			result += _constraints[i].toString() + "\n";
		}
	}

	printf("Satisfiable: %i\n", isSatisfiable());

	return result;
}

Simplex::Table Problem::toTable() const {
	Simplex::Table result;

	result.addRow();
	result.addColumn("q");
	result.setField(result.getCurrentRow(), "q", 1);
	
	for (unsigned int i = 0; i < _variables.size(); i++) {
		result.addColumn(_variables[i].toString());
		result.setField(result.getCurrentRow(), _variables[i].toString(), -1);
	}

	result.addColumn("result");
	result.setField(result.getCurrentRow(), "result", 0);

	for (unsigned int i = 0; i < _constraints.size(); i++) {
		_constraints[i].addToTable(result);
	}

	result.moveColumnToEnd("result");

	return result;
}