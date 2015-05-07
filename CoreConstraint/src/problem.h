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
		
		inline bool isSolvable(Simplex::Table& currentTable, unsigned int i) const;
		bool simSat(Simplex::Table& currentTable, unsigned int i) const;
	public:
		Problem();
		~Problem();

		Variable createVariable(std::string const& name);
		void addConstraint(Constraint const& constraint);

		bool isSatisfiable() const;
		std::string toString() const;
	};
}

#endif //_PROBLEM_DEF_H_
