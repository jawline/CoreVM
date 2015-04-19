#ifndef _PROBLEM_DEF_H_
#define _PROBLEM_DEF_H_
#include "constraint.h"

namespace Constraints {
	class Problem {
	private:
		unsigned int _lastv;
		std::vector<Constraint> _constraints;

	public:
		Problem();
		~Problem();

		Variable createVariable(std::string const& name);
		void addConstraint(Constraint const& constraint);

		std::string toString() const;
	};
}

#endif //_PROBLEM_DEF_H_