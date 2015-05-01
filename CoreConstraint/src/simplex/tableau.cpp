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
	for (int i = 0; i < instance->numColumns; i++) {
		if (instance->columns[i].getName().compare(name) == 0) {
			return i;
		}
	}
	return -1;
}

Column* Table::getColumn(std::string const& name) {
	int temp;
	if ((temp = getColumnId(instance, name)) != -1) {
		return &instance->columns[temp];
	}
	return 0;
}

int Table::addColumn(table* instance, std::string& name) {

	if (getColumnId(name) != -1) {
		return getColumnId(instance, name, nameLength);
	}

	//Allocate memory and copy existing columns
	Column* newColumns = new Column[instance->numColumns + 1];
	for (unsigned int i = 0; i < instance->numColumns; i++) {
		newColumns[i] = instance->columns[i];
	}
	
	//Free existing data and set new data
	if (instance->columns) {
		delete[] instance->columns;
	}
	instance->columns = newColumns;
	
	//Initialise new column
	instance->columns[instance->numColumns] = Column(name, nameLength);
	
	//Expand existing row data
	expandRows(instance, instance->numColumns, instance->numColumns+1);
	return instance->numColumns++;
}

void Table::addRow() {
	
	//Allocate memory and copy over existing rows
	double* newRowData = new double[_numRows+1 * _numColumns];
	memcpy(newRowData, instance->rowData, sizeof(double) * instance->numRows * instance->numColumns);
	
	//Set new rows to 0
	memset(newRowData + (instance->numRows * instance->numColumns), 0, sizeof(double) * instance->numColumns);

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

void setTableFieldWithColumnNameAndLength(table* instance, unsigned int row, char const* columnName, int length, double val) {
	int col;
	if ((col = getTableColumnIdWithLength(instance, columnName, length)) == -1) {
		printf("Column %s does not exist\n", columnName);
		return;
	}
	setTableField(instance, row, col, val);
}

double getTableFieldWithColumnName(table* instance, unsigned int row, char const* columnName) {
	return getTableFieldWithColumnNameAndLength(instance, row, columnName, strlen(columnName));
}

void setTableFieldWithColumnName(table* instance, unsigned int row, char const* columnName, double val) {
	setTableFieldWithColumnNameAndLength(instance, row, columnName, strlen(columnName), val);
}

void Table::swapColumn(unsigned int a, unsigned int b) {
	double temp;
	for (unsigned int i = 0; i < _numRows; i++) {
		temp = getField(i, a);
		setField(i, a, getField(i, b));
		setField(i, b, temp);
	}
	Column tempCol = instance->columns[a];
	instance->columns[a] = instance->columns[b];
	instance->columns[b] = tempCol;
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
