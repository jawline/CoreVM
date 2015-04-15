#ifndef _REGISTERS_DEF_H_
#define _REGISTERS_DEF_H_

namespace VM {
	enum {
		ProgramCounter = 0,
		RegisterA,
		RegisterB,
		RegisterC,
		RegisterD,
		NumRegisters
	} RegisterID;

	class RegisterUtils {
	public:
		static RegisterID getRegisterId(char const* name);
	}
}

#endif //_REGISTERS_DEF_H_
