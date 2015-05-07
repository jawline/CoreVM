#ifndef _VARIABLE_DEF_H_
#define _VARIABLE_DEF_H_
#include <string>

namespace Constraints {
	class Variable {
	private:
		std::string _name;
		bool _isSigned;
	public:
		Variable();
		Variable(std::string const& name, bool isSigned);
		~Variable();
		
		/**
		 * Return the variables name
		 */
		std::string toString() const;
		
		/**
		 * Return true if this is a signed integer
		 */
		bool isSigned() const;
	};
}

#endif //_VARIABLE_DEF_H_
