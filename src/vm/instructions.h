#ifndef _INSTRUCTION_DEF_H_
#define _INSTRUCTION_DEF_H_

namespace VM {
	enum {
		NoOp = 0x0,
		LoadImmediate,
		JumpImmediate,
		AddImmediate,
		SubtractImmediate,
		JumpRegister
	};
}

#endif //_INSTRUCTION_DEF_H_