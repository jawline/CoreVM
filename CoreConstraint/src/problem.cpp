#include "problem.h"
#include "problem_constants.h"
#include "solver.h"

using namespace Constraints;
using namespace Simplex;

Problem::Problem() {
	_lastv = 0;
}

Problem::~Problem() {}

Variable Problem::createVariable(std::string const& name) {
	_variables.push_back(Variable(name, true, _lastv+1));
	return Variable(name, true, _lastv++);
}

void Problem::addConstraint(Constraint const& constraint) {
	_constraints.push_back(constraint);
}

bool Problem::isSatisfiable() const {
	Table table;
	table.empty();
	table.addRow();
	table.addColumn(ProblemConstants::cObjectColumnName);
	table.setField(table.getCurrentRow(), ProblemConstants::cObjectColumnName, 1);
	
	for (unsigned int i = 0; i < _variables.size(); i++) {
		result.addColumn(_variables[i].toString());
		result.setField(result.getCurrentRow(), _variables[i].toString(), -1);
	}
	
	result.addColumn(ProblemConstants::cResultColumnName);
	result.setField(result.getCurrentRow(), ProblemConstants::cResultColumnName, 0);
	return simSat(table, 0);
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

	for (unsigned int i = 0; i < _constraints.size(); i++) {
			result += _constraints[i].toString() + "\n";
	}

	if (_variables.size()) {
		for (unsigned int i = 0; i < _variables.size(); i++) {
			if (i) {
				result += ", ";
			}
			result += _variables[i].toString();
		}
		result += " > 0\n";
	}

	printf("Satisfiable: %i\n", isSatisfiable());

	return result;
}

bool Problem::toTable(Simplex::Table& result) const {

	result.addColumn(ProblemConstants::cResultColumnName);
	result.setField(result.getCurrentRow(), ProblemConstants::cResultColumnName, 0);
	
	for (unsigned int i = 0; i < _constraints.size(); i++) {
		_constraints[i].addToTable(result);
	}
	
	result.moveColumnToEnd(ProblemConstants::cResultColumnName);
	return true;
}

bool Problem::isSolvable(Simplex::Table& currentTable, unsigned int i) const {
	if (i == _constraints.size() - 1) {
	} else {
		simSat(currentTable, i+1);
	}
}

bool Problem::simSat(Simplex::Table& currentTable, unsigned int i) const {
	isSolvable(currentTable, i);
}
