#ifndef _TABLEAU_SOLVER_DEF_H_
#define _TABLEAU_SOLVER_DEF_H_
#include <vector>
#include "tableau.h"

namespace Simplex {

	/**
	 * Structure to hold results of simplex solver run
	 */
	struct SimplexResult {
		double result;
	};

	class Solver {
	private:
		static bool isBasic(Table& instance, int col);
		static int findBasic(Table& instance, int row);
		static int findPivotColumn(Table& instance, bool minimize);
		static double findRatio(Table& instance, int row, int column, int resCol);
		static int findPivotRow(Table& instance, int column);
		static void makeRowUnit(Table& instance, int row, int col);
		static void makeOtherRowsUnit(Table& instance, int baseRow, int col);
		static void setupArtificialTable(Table& instance, Table& original, std::vector<int> const& artificialVariables);
		static void restoreTable(Table& instance, Table& original);
		static bool findBasicData(Table& instance, int* rowBasicData, double* rowBasicSolution);
		static void handleFinalBasicData(Table& instance, int* rowBasicData, double* rowBasicSolution);
		static bool pivotTable(Table& instance, int* rowBasicData, bool minimize);
		static bool allArtificialsZero(Table const& instance, std::vector<int> const& artificialVariables);
		static bool artificialColumnsInBasis(int* basis, unsigned int numRows, std::vector<int> const& artificialColumns);

	public:
		/**
		 * Solve the simplex tableau
		 * NOTE: It is assumed that the last column in the table is the results column
		 */
		static bool solveTable(Table& instance, SimplexResult& results);
	};
}

#endif //_TABLEAU_SOLVER_DEF_H_
