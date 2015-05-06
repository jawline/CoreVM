#ifndef _SIMPLEX_TABLAEU_DEF_H_
#define _SIMPLEX_TABLAEU_DEF_H_
#include "column.h"

namespace Simplex {

	class Table {
	private:
		Column* _columns;
		double* _rowData;
		int _numColumns;
		int _numRows;

		void expandRows(int numNewColumns);	
	public:
		Table();
		Table(Table const& other);
		~Table();

		int getColumnId(std::string const& name) const;
		Column* getColumn(std::string const& name) const;
		Column* getColumn(int i) const;

		int getNumRows() const;
		int getNumColumns() const;

		int addColumn(std::string const& column);
		void addRow();

		unsigned int getCurrentRow() const;
		double* getRowData(unsigned int row) const;
		
		double getField(unsigned int row, unsigned int col) const;
		double getField(unsigned int row, std::string const& column) const;

		void setField(unsigned int row, unsigned int col, double value);
		void setField(unsigned int row, std::string const& column, double value);

		void swapColumn(unsigned int c1, unsigned int c2);

		void subtractRow(unsigned int r1, unsigned int r2, double scalar);
		void subtractRow(unsigned int r1, unsigned int r2);

		void multiplyRow(unsigned int r1, double scalar);
		void divideRow(unsigned int r1, double divisor);

		void moveColumnToEnd(unsigned int col);
		void moveColumnToEnd(std::string const& name);

		void empty();

		void print();
	};
}

#endif //_SIMPLEX_TABLAEU_DEF_H_
