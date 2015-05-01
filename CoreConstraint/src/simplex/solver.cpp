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
		if (instance.getField(0, i) != 0 && (instance.getField(0, i) < cPivotValue || cPivotValue == 0)) {
			cPivot = i;
			cPivotValue = instance.getField(0, i);
		}
	}

	//If the columns objective value is >= 0 then it cannot be a pivot column
	return cPivotValue != 0 ? cPivot : -1;
}

double Solver::findRatio(Table& instance, int row, int column, int resCol) {
	return instance.getField(row, resCol) / instance.getField(row, column);
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

	return cPivot;
}

void Solver::makeRowUnit(Table& instance, int row, int col) {
	double ratio = 1.0 / instance.getField(row, col);
	for (unsigned int i = 0; i < instance.getNumColumns(); i++) {
		instance.setField(row, i, ratio * instance.getField(row, i));
	}
}

void Solver::subtractRow(Table& instance, int rowToSub, int rowFrom, double ratio) {
	for (unsigned int i = 0; i < instance.getNumColumns(); i++) {
		instance.setField(rowToSub, i, instance.getField(rowToSub, i) - (instance.getField(rowFrom, i) / ratio));
	}
}

void Solver::makeOtherRowsUnit(Table& instance, int baseRow, int col) {
	for (unsigned int i = 0; i < instance.getNumRows(); i++) {
		if (i != baseRow && instance.getField(i, col) != 0) {
			double ratioOfBaseRow = 1.0 / instance.getField(i, col);
			subtractRow(instance, i, baseRow, ratioOfBaseRow);
		}
	}
}

void Solver::solveTable(Table& instance, SimplexResult& results) {
	
	//Find the initial basic variables (Only occur in one col)
	int* rowBasicData = new int[instance.getNumRows()];
	double* rowBasicSolution = new double[instance.getNumRows()];

	for (unsigned int i = 0; i < instance.getNumRows(); i++) {
		rowBasicData[i] = 0;
		rowBasicSolution[i] = 0;
	}
	
	printf("---------\n");

	//First row is the objective function, should have no basic variables
	for (unsigned int i = 1; i < instance.getNumRows(); i++) {
		rowBasicData[i] = findBasic(instance, i);
		if (rowBasicData[i] == -1) {
			printf("Failed to find basic variable for row %i\n", i);
			rowBasicSolution = 0;
		} else {
			rowBasicSolution[i] = instance.getField(i, rowBasicData[i]) / instance.getField(i, instance.getNumColumns() - 1);
			printf("Row %i: Col %i is basic (Solution: %f/%f -> %f)\n",
				i,
				rowBasicData[i],
				instance.getField(i, rowBasicData[i]),
				instance.getField(i, instance.getNumColumns() - 1),
				rowBasicSolution[i]);
		}
	}
	
	printf("---------\n");

	int pivotC;
	int i = 0;
	
	while ((pivotC = findPivotColumn(instance)) != -1) {
		int pivotR = findPivotRow(instance, pivotC);
		double ratio = findRatio(instance, pivotR, pivotC, instance.getNumColumns() - 1);
		printf("Operation Number: %i\n", i);
		printf("Pivot Column: %i\n", pivotC);
		printf("Pivot Row: %i\n", pivotR);
		printf("Pivot Ratio: %f\n", ratio);
		makeRowUnit(instance, pivotR, pivotC);
		makeOtherRowsUnit(instance, pivotR, pivotC);
		instance.print();
		rowBasicData[pivotR] = pivotC;
		i++;
	}

	printf("---------\n");
	for (unsigned int i = 0; i < instance.getNumRows(); i++) {
		if (rowBasicData[i] != -1) {
			printf("%s: %f\n",
				instance.getColumn(i)->getName().c_str(), 
				instance.getField(i, instance.getNumColumns() - 1));
		} else {
			printf("Row %i unmapped\n", i);
		}
	}
	printf("---------\n");

	delete[] rowBasicData;
	delete[] rowBasicSolution;
	results.result = instance.getField(0, instance.getNumColumns() - 1);
}
