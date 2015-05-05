#include "constraint.h"

using namespace Constraints;

static const char* ComparisonTypeStrings[NumComparisonTypes] = {"=", "!=", "<", ">"};
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

void Constraint::addToTable(Simplex::Table& table, std::vector<int>& artificialColumns) const {
	table.addRow();
	for (unsigned int i = 0; i < _items.size(); i++) {
		table.addColumn(_items[i].first.toString());
		table.setField(table.getCurrentRow(), _items[i].first.toString(), _items[i].second);
	}

	std::string name;

	switch (_type) {
		case Equal:
			break;
		case LessThan:
			name = std::string("slack") + std::to_string(slackd);
			table.addColumn(name);
			table.setField(table.getCurrentRow(), name, 1);
			name = std::string("artificial") + std::to_string(slackd++);
			artificialColumns.push_back(table.addColumn(name));)
			table.setField(table.getCurrentRow(), name, 1);
			break;
		case GreaterThan:
			name = std::string("slack") + std::to_string(slackd);
			table.addColumn(name);
			table.setField(table.getCurrentRow(), name, -1);
			name = std::string("artificial") + std::to_string(slackd++);
			artificialColumns.push_back(table.addColumn(name));)
			table.setField(table.getCurrentRow(), name, 1);
			break;
		default:
			printf("%s NOT HANDLED YET\n", ComparisonTypeStrings[_type]);
			break;
	}

	table.setField(table.getCurrentRow(), "result", _value);
}
