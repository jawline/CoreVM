#ifndef _VARIABLE_DEF_H_
#define _VARIABLE_DEF_H_
#include <string>

namespace Constraints {
	class Variable {
		friend class Problem;
	private:
		std::string _name;
		unsigned int _index;

	protected:
		Variable(std::string const& name, unsigned int index);

	public:
		~Variable();

		unsigned int getIndex() const;
	};
}

#endif //_VARIABLE_DEF_H_