#include "compositesymbol.h"

using namespace VM;

CompositeSymbol::CompositeSymbol() {}
CompositeSymbol::~CompositeSymbol() {}

void CompositeSymbol::buildConstraint(Constraints::Constraint& constraint, Constraints::ComparisonType type, int32_t result) {
	addToConstraint(constraint);
	constraint.setComparisonType(type);
	constraint.setResult(result + constraint.getResult());
}