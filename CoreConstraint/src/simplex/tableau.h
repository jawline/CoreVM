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

		void addColumn(char const* name, size_t length);
		void addRow();

		unsigned int getCurrentRow() const;
		double* getRowData(unsigned int row) const;
		
		double getField(unsigned int row, unsigned int col) const;

		void setField(double d, unsigned int row, unsigned int col);
		void setField(double d, unsigned int row, std::string const& column);

		void swapColumn(unsigned int c1, unsigned int c2);

		void print();
	};
}

#endif //_SIMPLEX_TABLAEU_DEF_H_
