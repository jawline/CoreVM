#ifndef _VARIABLE_DEF_H_
#define _VARIABLE_DEF_H_

namespace Constraints {
	class Variable {
		friend class Problem;
	private:
		unsigned int _index;

	protected:
		Variable(unsigned int index);
	public:
		~Variable();
		unsigned int getIndex() const;
	};
}

#endif //_VARIABLE_DEF_H_
