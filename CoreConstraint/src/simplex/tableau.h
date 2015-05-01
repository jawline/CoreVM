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
		~Table();

		int getColumnId(std::string const& name) const;
		Column* getColumn(std::string const& name) const;

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

		void print();
	};
}

#endif //_SIMPLEX_TABLAEU_DEF_H_
