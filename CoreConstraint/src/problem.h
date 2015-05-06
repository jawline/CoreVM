#ifndef _PROBLEM_DEF_H_
#define _PROBLEM_DEF_H_
#include "constraint.h"
#include "tableau.h"

namespace Constraints {
	class Problem {
	private:
		unsigned int _lastv;
		std::vector<Variable> _variables;
		std::vector<Constraint> _constraints;

	public:
		Problem();
		~Problem();

		Variable createVariable(std::string const& name);
		void addConstraint(Constraint const& constraint);

		bool isSatisfiable() const;
		std::string toString() const;
		bool toTable(Simplex::Table& emptyTable) const;
	};
}

#endif //_PROBLEM_DEF_H_
