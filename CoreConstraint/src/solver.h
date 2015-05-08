#ifndef _TABLEAU_SOLVER_DEF_H_
#define _TABLEAU_SOLVER_DEF_H_
#include <vector>
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
		static int findPivotColumn(Table& instance);
		static double findRatio(Table& instance, int row, int column, int resCol);
		static int findPivotRow(Table& instance, int column);
		static void makeRowUnit(Table& instance, int row, int col);
		static void makeOtherRowsUnit(Table& instance, int baseRow, int col);
		static void setupArtificialTable(Table& instance, Table& original, std::vector<int> const& artificialVariables);
		static void restoreTable(Table& instance, Table& original);
		static void findBasicData(Table& instance, int* rowBasicData, double* rowBasicSolution);
		static void handleFinalBasicData(Table& instance, int* rowBasicData, double* rowBasicSolution);
		static bool pivotTable(Table& instance, int* rowBasicData, double* rowBasicSolution, std::vector<int> const& artficialVariables);

	public:
		/**
		 * Solve the simplex tableau
		 * NOTE: It is assumed that the last column in the table is the results column
		 */
		static bool solveTable(Table& instance, std::vector<int> const& artificialVariables, SimplexResult& results);
	};
}

#endif //_TABLEAU_SOLVER_DEF_H_
