#include "constraint.h"

using namespace Constraints;

static const char* ComparisonTypeStrings[NumComparisonTypes] = {"=", "<=", ">="};

Constraint::Constraint() {
	_value = 0;
	_type = Equals;
}

Constraint::Constraint(double value) {
	_value = value;
	_type = Equals;
}

Constraint::~Constraint() {}

void Constraint::addItem(Variable const& var, double multiplier) {
	_items.push_back(ConstraintItem(var, multiplier));
}

void Constraint::setResult(double endValue) {
	_value = endValue;
}

void Constraint::setComparisonType(ComparisonType const& type) {
	_type = type;
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
		result += ComparisonTypeStrings[_type];
		result += " ";
		result += std::to_string(_value);
	} else {
		result = "Empty Constraint";
	}
	return result;
}