#ifndef _REGISTERS_DEF_H_
#define _REGISTERS_DEF_H_

namespace VM {
	typedef enum {
		ProgramCounter = 0,
		RegisterA,
		RegisterB,
		RegisterC,
		RegisterD,
		RegisterE,
		RegisterF,
		RegisterG,
		RegisterH,
		RegisterI,
		RegisterJ,
		RegisterK,
		RegisterL,
		RegisterM,
		RegisterN,
		RegisterO,
		RegisterP,
		RegisterQ,
		NumRegisters,
		InvalidRegister
	} RegisterID;

	/**
	 * Utility functions which allow for easier parsing and debugging output
	 */
	class RegisterUtils {
	private:
		/**
		 * Mappings from RegisterID to string names
		 */
		static char const* mapping[];
	public:
		/**
		 * Return a registers string name (PC, A, B, etc..) from its numeric id
		 */
		static char const* getRegisterName(unsigned int id);
		
		/**
		 * Return a registers numeric ID (0, 1, 2, ...) from its string name
		 */
		static RegisterID getRegisterId(char const* name);
	};
}

#endif //_REGISTERS_DEF_H_
