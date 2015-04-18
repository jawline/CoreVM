#ifndef _VARIABLE_DEF_H_
#define _VARIABLE_DEF_H_

namespace Constraints {
	class Variable {
	private:
		unsigned int _index;

	public:
		Variable(unsigned int index);
		~Variable();

		unsigned int getIndex();
	};
}

#endif //_VARIABLE_DEF_H_