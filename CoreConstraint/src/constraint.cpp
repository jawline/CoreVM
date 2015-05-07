#include "constraint.h"
#include "problem_constants.h"
#include <math.h>

using namespace Constraints;

const char* Constraint::ComparisonTypeStrings[NumComparisonTypes] = {"=", "!=", "<", ">", ">=", "<="};
unsigned int slackd = 0;

Constraint::Constraint() {
	_value = 0;
	_type = Equal;
}

Constraint::Constraint(double value) {
	_value = value;
	_type = Equal;
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
				if (_items[i].second > 0) {
					result += "+ ";
				} else {
					result += "- ";
				}
			}
			result += std::to_string(fabs(_items[i].second));
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

void Constraint::addToTable(Simplex::Table& table) const {
	table.addRow();
	
	for (unsigned int i = 0; i < _items.size(); i++) {
		table.addColumn(_items[i].first.toString());
		table.setField(table.getCurrentRow(), _items[i].first.toString(), _items[i].second);
	}
	
	ComparisonType localType = _type;
	double localValue = _value;
	
	if (localType == GreaterThanOrEqual) {
		localType = GreaterThan;
		localValue += 1;
	}
	
	if (localType == LessThanOrEqual) {
		localType = LessThan;
		localValue -= 1;
	}

	std::string name;

	switch (localType) {
		case Equal:

			//No slack - Add an artificial variable with the same sign as the result
			name = std::string("artificial") + std::to_string(slackd);
			table.addColumn(name, true);
			table.setField(table.getCurrentRow(), name, localValue > 0 ? 1 : -1);
			slackd++;

			break;
		case LessThan:
			name = std::string("slack") + std::to_string(slackd);
			table.addColumn(name);
			table.setField(table.getCurrentRow(), name, 1);

			//If the slack doesn't have the same sign as the result add an artificial variable
			if (localValue < 0) {
				name = std::string("artificial") + std::to_string(slackd);
				table.addColumn(name, true);
				table.setField(table.getCurrentRow(), name, -1);
			}

			slackd++;
			break;
		case GreaterThan:
			name = std::string("slack") + std::to_string(slackd);
			table.addColumn(name);
			table.setField(table.getCurrentRow(), name, -1);
			
			//If the slack doesn't have the same sign as the result add an artificial variable
			if (localValue > 0) {
				name = std::string("artificial") + std::to_string(slackd);
				table.addColumn(name, true);
				table.setField(table.getCurrentRow(), name, 1);
			}

			slackd++;
			break;
		default:
			printf("%s NOT HANDLED YET\n", ComparisonTypeStrings[_type]);
			break;
	}

	table.setField(table.getCurrentRow(), ProblemConstants::cResultColumnName, localValue);
}

ComparisonType Constraint::getComparisonType() const {
	return _type;
}
