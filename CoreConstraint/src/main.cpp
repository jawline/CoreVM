#include "solver.h"
#include <stdio.h>
#include <iostream>

using namespace Constraints;

int main(int argc, char** argv) {
	printf("CoreConstraints\n");

	Problem p;
	Variable a = p.createVariable("A");
	Variable b = p.createVariable("B");

	Constraint d;
	d.addItem(a, 5);
	d.setResult(10);

	p.addConstraint(d);

	Constraint r;
	r.addItem(a, 10);
	r.addItem(b, 5);
	r.setResult(20);

	p.addConstraint(r);

	std::cout << p.toString();

	return -1;
}
