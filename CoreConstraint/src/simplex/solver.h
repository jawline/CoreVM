#ifndef _TABLEAU_SOLVER_DEF_H_
#define _TABLEAU_SOLVER_DEF_H_
#include <stdbool.h>
#include "tableau.h"

using namespace Simplex;

/**
 * Structure to hold results of simplex solver run
 */
typedef struct {
  double value;
} simplex_result;

bool isBasic(Table& instance, int col);

/**
 * Solve the simplex tableau
 * NOTE: It is assumed that the last column in the table is the results column
 */
void solveTable(Table& instance, simplex_result* results);

#endif //_TABLEAU_SOLVER_DEF_H_
