#include "tableau.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace Simplex;

Table::Table() {
		_columns = nullptr;
		_numColumns = 0;
		_rowData = nullptr;
		_numRows = 0;
}

Table::~Table() {
	if (_columns) {
		delete[] _columns;
	}
	if (_rowData) {
		delete[] _rowData;
	}
}

int Table::getColumnId(std::string const& name) {
	for (int i = 0; i < _numColumns; i++) {
		if (_columns[i].getName().compare(name) == 0) {
			return i;
		}
	}
	return -1;
}

Column* Table::getColumn(std::string const& name) {
	int temp;
	if ((temp = getColumnId(name)) != -1) {
		return &_columns[temp];
	}
	return 0;
}

int Table::addColumn(std::string& name) {

	if (getColumnId(name) != -1) {
		return getColumnId(name);
	}

	//Allocate memory and copy existing columns
	Column* newColumns = new Column[_numColumns + 1];
	for (unsigned int i = 0; i < _numColumns; i++) {
		newColumns[i] = _columns[i];
	}
	
	//Free existing data and set new data
	if (_columns) {
		delete[] _columns;
	}
	_columns = newColumns;
	
	//Initialise new column
	_columns[_numColumns] = Column(name);
	
	//Expand existing row data
	expandRows(_numColumns+1);
	return _numColumns++;
}

void Table::addRow() {
	
	//Allocate memory and copy over existing rows
	double* newRowData = new double[_numRows+1 * _numColumns];
	memcpy(newRowData, _rowData, sizeof(double) * _numRows * _numColumns);
	
	//Set new rows to 0
	memset(newRowData + (_numRows * _numColumns), 0, sizeof(double) * _numColumns);

	//Free old data and set new row data
	if (_rowData) {
		delete[] _rowData;
	}
	_rowData = newRowData;
	_numRows++;
}

void Table::expandRows(int newNumColumns) {
	
	//Allocate new data
	double* newRowData = new double[_numRows * newNumColumns];
	double* oldRowData = _rowData;
	memset(newRowData, 0, newNumColumns * _numRows * sizeof(double));
	
	//Copy the existing rows
	for (unsigned int column = 0; column < _numColumns; column++) {
		for (unsigned int row = 0; row < _numRows; row++) {
			newRowData[(row * newNumColumns) + column] = oldRowData[(row * _numColumns) + column];
		}
	}
	
	//Free old data and set new data
	if (_rowData) {
		delete[] _rowData;
	}

	_rowData = newRowData;
}

int Table::getNumRows() const {
	return _numRows;
}

int Table::getNumColumns() const {
	return _numColumns;
}

unsigned int Table::getCurrentRow() {
	return _numRows >= 1 ? _numRows - 1 : 0;
}

double* Table::getRowData(unsigned int rowNum) {
	//TODO: Assert rowNum < _numRows ?
	return _rowData + (_numColumns * rowNum);
}

double Table::getField(unsigned int row, unsigned int column) const {
	return *(getRowData(row) + column);
}

void Table::setTableField(unsigned int row, unsigned int column, double val) {
	*(getRowData(row) + column) = val;
}

double Table::getField(unsigned int row, std::string const& name) {
	int col = getColumnId(name);
	//TODO: Assert col != -1
	return getField(row, col);
}

void Table::setField(unsigned int row, std::string const& name, double val) {
	int col = getColumnId(name);
	//TODO: assert col != -1
	setField(row, col, val);
}

void Table::swapColumn(unsigned int a, unsigned int b) {
	double temp;
	for (unsigned int i = 0; i < _numRows; i++) {
		temp = getField(i, a);
		setField(i, a, getField(i, b));
		setField(i, b, temp);
	}
	Column tempCol = _columns[a];
	_columns[a] = _columns[b];
	_columns[b] = tempCol;
}

void Table::print() {
	for (unsigned int i = 0; i < _numColumns; i++) {
		printf("| %s |", _columns[i].getName().c_str());
	}
	printf("\n");
	for (unsigned int row = 0; row < _numRows; row++) {
		for (unsigned int column = 0; column < _numColumns; column++) {
			printf("| %f |", _rowData[row * _numColumns + column]);
		}
		printf("\n");
	}
}
