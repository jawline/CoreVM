#ifndef _MATRIX_DEF_H_
#define _MATRIX_DEF_H_

namespace Simplex {
  template <class T>
  class Matrix {
    private:
      T* _data;
      unsigned int _numColumns;
      unsigned int _numRows;
    public:
      Matrix(unsigned int rows, unsigned int cols);
      ~Matrix();
      
      void addRow();
      void addColumn();
  };
}

#endif //_MATRIX_DEF_H_
