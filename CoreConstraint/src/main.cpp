#include "solver.h"
#include <stdio.h>
#include <iostream>

using namespace Constraints;

int main(int argc, char** argv) {
	printf("CoreConstraints\n");

	Problem p;
	Variable a = p.createVariable("A");
	Variable b = p.createVariable("B");
	Variable c = p.createVariable("C");

	Constraint d;
	
	d.addItem(a,5);
	d.setResult(10);

	Constraint r;

	r.addItem(a,10);
	r.addItem(b,5);
	r.setResult(20);

	Constraint q;

	q.addItem(a, 20);
	q.addItem(c, 1);
	q.setComparisonType(LessThanOrEqual);
	q.setResult(40);

	p.addConstraint(d);
	p.addConstraint(r);
	p.addConstraint(q);

	std::cout << p.toString();

	return -1;
}
