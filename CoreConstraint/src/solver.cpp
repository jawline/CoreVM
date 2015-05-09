#include "solver.h"
#include <stdio.h>
#include <string.h>

using namespace Simplex;

bool Solver::isBasic(Table& instance, int col) {
	unsigned int count = 0;
	for (unsigned int i = 0; i < instance.getNumRows(); i++) {
		if (instance.getField(i, col) != 0) {
			count++;
		}
	}
	return count == 1;
}

//TODO: Could be more efficient. The row->col->row search could be turned into just a row->col search
int Solver::findBasic(Table& instance, int row) {

	//-1 excludes the result row
	for (unsigned int i = 0; i < instance.getNumColumns() - 1; i++) {
		if (isBasic(instance, i) && instance.getField(row, i) != 0) {
			return i;
		}
	}
	return -1;
}

/**
 * Return the ID of the pivot column or -1 if there is not pivot column
 */
int Solver::findPivotColumn(Table& instance) {

	//Check there are at least three columns (At least one variable, the objective variable, and the results columns)
	if (instance.getNumColumns() < 3) {
		return -1;
	}

	//Don't grab the first column, it shouldn't changed
	int cPivot = 1;
	double cPivotValue = instance.getField(0, 1);

	//Never look at the first column, it shouldn't change
	for (unsigned int i = 1; i < instance.getNumColumns() - 1; i++) {
		if (instance.getField(0, i) != 0 && instance.getField(0, i) < cPivotValue) {
			cPivot = i;
			cPivotValue = instance.getField(0, i);
		}
	}

	//If the columns objective value is >= 0 then it cannot be a pivot column
	return cPivotValue < 0 ? cPivot : -1;
}

double Solver::findRatio(Table& instance, int row, int column, int resCol) {
	double resultField = instance.getField(row, column);
	//TODO: Verify this is correct
	//Avoids divide by zero
	return resultField != 0 ? instance.getField(row, resCol) / resultField : 0;
}

int Solver::findPivotRow(Table& instance, int column) {

	if (instance.getNumRows() < 2) {
		printf("no pivot possible\n");
		return -1;
	}

	int resultsColumn = instance.getNumColumns() - 1;
	
	int cPivot = 1;
	double cPivotR = findRatio(instance, 1, column, resultsColumn);
	
	//Find the row to be used as the pivot, excluding the objective function
	for (unsigned int i = 1; i < instance.getNumRows(); i++) {
		if (findRatio(instance, i, column, resultsColumn) < cPivotR) {
			cPivot = i;
			cPivotR = findRatio(instance, i, column, resultsColumn);
		}
	}

	return cPivotR != 0 ? cPivot : -1;
}

void Solver::makeRowUnit(Table& instance, int row, int col) {
	instance.divideRow(row, instance.getField(row, col));
}

void Solver::makeOtherRowsUnit(Table& instance, int baseRow, int col) {
	for (unsigned int i = 0; i < instance.getNumRows(); i++) {
		if (i != baseRow && instance.getField(i, col) != 0) {
			instance.subtractRow(i, baseRow, instance.getField(i, col));
		}
	}
}

void Solver::setupArtificialTable(Table& instance, Table& original, std::vector<int> const& artificialVariables) {
	//TODO: store the top row instead, this is crazy ineficient
	original = instance;
	for (unsigned int i = 1; i < instance.getNumColumns(); i++) {
		instance.setField(0, i, 0);
	}
	for (unsigned int i = 0; i < artificialVariables.size(); i++) {
		instance.setField(0, artificialVariables[i], -1);
	}
}

void Solver::restoreTable(Table& instance, Table& original) {
	for (unsigned int i = 1; i < instance.getNumColumns(); i++) {
		instance.setField(0, i, original.getField(0, i));
	}
	instance.removeArtificials();
}

void Solver::findBasicData(Table& instance, int* rowBasicData, double* rowBasicSolution) {
	
	printf("------------------------------------------\n");
	printf("-             BASIC INFO                 -\n");
	printf("------------------------------------------\n");

	//First row is the objective function, should have no basic variables
	for (unsigned int i = 1; i < instance.getNumRows(); i++) {
		rowBasicData[i] = findBasic(instance, i);
		if (rowBasicData[i] == -1) {
			printf("Failed to find basic variable for row %i\n", i);
			rowBasicSolution[i] = 0;
		} else {
			double basicField = instance.getField(i, rowBasicData[i]);
			double resultField = instance.getField(i, instance.getNumColumns() - 1);
			rowBasicSolution[i] = basicField / resultField;
			printf("Row %i: Col %i is basic (Solution: %f/%f -> %f)\n",
				i,
				rowBasicData[i],
				instance.getField(i, rowBasicData[i]),
				instance.getField(i, instance.getNumColumns() - 1),
				rowBasicSolution[i]);
		}
	}
	
	printf("------------------------------------------\n");
}

void Solver::handleFinalBasicData(Table& instance, int* rowBasicData, double* rowBasicSolution) {
	printf("------------------------------------------\n");
	printf("-              FINAL BASIC               -\n");
	printf("------------------------------------------\n");
	for (unsigned int i = 0; i < instance.getNumRows(); i++) {
		if (rowBasicData[i] != -1) {
			printf("%s: %f\n",
				instance.getColumn(i)->getName().c_str(), 
				instance.getField(i, instance.getNumColumns() - 1));
		} else {
			printf("Row %i unmapped\n", i);
		}
	}
	printf("------------------------------------------\n");
}

bool Solver::allArtificialsZero(Table const& instance, std::vector<int> const& artificialVariables) {
	for (unsigned int i = 0; i < artificialVariables.size(); i++) {
		if (instance.getField(0, artificialVariables[i]) != 0) {
			return false;
		}
	}
	return true;
}

bool Solver::pivotTable(Table& instance, int* rowBasicData, double* rowBasicSolution, std::vector<int> const& artificialVariables) {
	int pivotC, iterations = 0;
	unsigned int numArtificials = artificialVariables.size();
	
	while ((pivotC = findPivotColumn(instance)) != -1) {
		int pivotR = findPivotRow(instance, pivotC);
		if (pivotR == -1) {
			//TODO: Verify whether pivotR will ever be -1
			//TODO: Verify what that means?
			printf("AAAAH Should I be here?\n");
			return false;
		}
		
		double ratio = findRatio(instance, pivotR, pivotC, instance.getNumColumns() - 1);
		
		printf("Operation Number: %i\n", iterations);
		printf("Pivot Column: %i\n", pivotC);
		printf("Pivot Row: %i\n", pivotR);
		printf("Pivot Ratio: %f\n", ratio);
		
		makeRowUnit(instance, pivotR, pivotC);
		makeOtherRowsUnit(instance, pivotR, pivotC);
		instance.print();
		rowBasicData[pivotR] = pivotC;
		
		if (numArtificials) {
			if (instance.getField(0, instance.getNumColumns() -1) == 0) {
				break;
			}
			if (allArtificialsZero(instance, artificialVariables)) {
				return false;
			}
		}

		iterations++;
	}

	return true;
}

bool Solver::solveTable(Table& instance, std::vector<int> const& artificialVariables, SimplexResult& results) {
	Table original;
	unsigned int numArtificials = artificialVariables.size();

	if (numArtificials) {
		setupArtificialTable(instance, original, artificialVariables);
		printf("DEBUG: Changed to artificial table\n");
	}
	
	int* rowBasicData = new int[instance.getNumRows()];
	double* rowBasicSolution = new double[instance.getNumRows()];
	findBasicData(instance, rowBasicData, rowBasicSolution);
	
	if (!pivotTable(instance, rowBasicData, rowBasicSolution, artificialVariables)) {
		return false;
	}
	
	if (numArtificials) {
		handleFinalBasicData(instance, rowBasicData, rowBasicSolution);
	}

	delete[] rowBasicData;
	delete[] rowBasicSolution;
	results.result = instance.getField(0, instance.getNumColumns() - 1);

	if (numArtificials) {
		restoreTable(instance, original);
		printf("DEBUG: Stripped artificials\n");
		return solveTable(instance, std::vector<int>(), results);
	} else {
		return true;
	}
}
