#ifndef _TABLEAU_SOLVER_DEF_H_
#define _TABLEAU_SOLVER_DEF_H_
#include <stdbool.h>
#include "tableau.h"

namespace Simplex {
	/**
	 * Structure to hold results of simplex solver run
	 */
	class SimplexResult {
	public:
		double result;
	};

	class Solver {
	private:
		static bool isBasic(Table& instance, int col);
		static int findBasic(Table& instance, int row);

	public:
		/**
		 * Solve the simplex tableau
		 * NOTE: It is assumed that the last column in the table is the results column
		 */
		static void solveTable(Table& instance, SimplexResult& results);
	};
}

#endif //_TABLEAU_SOLVER_DEF_H_
