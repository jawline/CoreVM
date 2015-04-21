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

	class RegisterUtils {
	public:
		static RegisterID getRegisterId(char const* name);
	};
}

#endif //_REGISTERS_DEF_H_
