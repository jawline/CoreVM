#include "constraint.h"

using namespace Constraints;

Constraint::Constraint() {
	_value = 0;
}

Constraint::Constraint(double value) {
	_value = value;
}

Constraint::~Constraint() {}

void Constraint::addItem(Variable const& var, double multiplier) {
	_items.push_back(ConstraintItem(var, multiplier));
}

void Constraint::setResult(double endValue) {
	_value = endValue;
}

std::string Constraint::toString() const {
	std::string result;
	if (_items.size()) {
		for (unsigned int i = 0; i < _items.size(); i++) {
			if (i) {
				result += "+ ";
			}
			result += std::to_string(_items[i].second);
			result += _items[i].first.toString();
			result += " ";
		}
		result += "= ";
		result += std::to_string(_value);
	} else {
		result = "Empty Constraint";
	}
	return result;
}