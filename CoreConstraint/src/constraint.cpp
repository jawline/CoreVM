#include "constraint.h"

using namespace Constraints;

Constraint::Constraint() {
	_value = 0;
}

Constraint::Constraint(unsigned int value) {
	_value = value;
}

Constraint::~Constraint() {}

void Constraint::addItem(Variable const& var, double multiplier) {
	_items.push_back(ConstraintItem(var, multiplier));
}

void Constraint::setResult(unsigned int endValue) {
	_value = endValue;
}