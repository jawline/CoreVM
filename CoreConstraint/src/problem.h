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

		Variable createVariable();
		void addConstraint(Constraint const& constraint);
	};
}

#endif //_PROBLEM_DEF_H_