#ifndef _SOLVER_CONSTRAINT_DEF_H_
#define _SOLVER_CONSTRAINT_DEF_H_
#include "variable.h"
#include <vector>
#include <string>

namespace Constraints {
	typedef std::pair<Variable,double> ConstraintItem;

	class Constraint {
	private:
		std::vector<ConstraintItem> _items;
		double _value;
	public:
		Constraint();
		Constraint(double value);
		~Constraint();

		void addItem(Variable const& var, double multiplier);
		void setResult(double endValue);
		std::string toString() const;
	};
};

#endif //_SOLVER_CONSTRAINT_DEF_H_