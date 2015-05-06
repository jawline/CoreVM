/*#include <stdio.h>
#include "simplex/parser.h"
#include "simplex/solver.h"

using namespace Simplex;

int main(int argc, char** argv) {

	if (argc != 2) {
		printf("Usage: %s max problem\n", argv[0]);
		return -1;
	}

	Table instance;
	SimplexResult results;
	
	parserInit();

	if (parseString(instance, argv[1])) {
		instance.print();
	} else {
		printf("Failed to parse table. Exit\n");
		return -1;
	}

	Solver::solveTable(instance, results);

	printf("Results: %f\n", results.result);
	parserFree();
	return 0;
}*/

#include <stdio.h>
#include <iostream>
#include "problem.h"
#include "solver.h"

using namespace Constraints;

int main(int argc, char** argv) {
	printf("CoreConstraints\n");

	Problem p;
	Variable a = p.createVariable("A");
	Variable b = p.createVariable("B");

	Constraint d;
	
	d.addItem(a,5);
	d.setResult(10);

	Constraint q;

	q.addItem(a, 5);
	q.addItem(b, 1);
	q.setResult(20);

	p.addConstraint(d);
	p.addConstraint(q);

	std::cout << p.toString();

	Simplex::SimplexResult res;
	Simplex::Table table;
	std::vector<int> artificialColumns;
	p.toTable(table, artificialColumns);
	table.print();
	
	if (Simplex::Solver::solveTable(table, artificialColumns, res)) {
		printf("%f\n", res.result);
	} else {
		printf("Cannot solve\n");
	}

	return -1;
}