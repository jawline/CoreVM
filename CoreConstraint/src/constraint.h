#ifndef _SOLVER_CONSTRAINT_DEF_H_
#define _SOLVER_CONSTRAINT_DEF_H_
#include "variable.h"
#include <vector>

namespace Constraints {
	typedef std::pair<Variable,double> ConstraintItem;

	class Constraint {
	private:
		std::vector<ConstraintItem> _items;
		unsigned int _value;

	public:
		Constraint();
		Constraint(unsigned int value);
		~Constraint();

		void addItem(Variable const& var, double multiplier);
		void setResult(unsigned int endValue);
	};
};

#endif //_SOLVER_CONSTRAINT_DEF_H_