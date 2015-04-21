	#include "core.h"
#include "coreutils.h"

using namespace VM;

void Core::noOp(Core* inst) {
	inst->_registers[ProgramCounter] += 1;
	printf("NOOP\n");
}

void Core::loadImmediate(Core* inst) {
	uint8_t reg;
	uint32_t val;
	CoreUtils::byteFromBuffer(reg, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::uintFromBuffer(val, &inst->_data[inst->_registers[ProgramCounter]+2]);
	inst->_registers[reg] = val;
	inst->_registers[ProgramCounter] += 6;
	printf("LOAD IMMEDIATE $%i:=%i\n", reg, val);
}

void Core::move(Core* inst) {
	uint8_t dst, src;
	CoreUtils::byteFromBuffer(dst, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::byteFromBuffer(src, &inst->_data[inst->_registers[ProgramCounter]+2]);
	inst->_registers[dst] = inst->_registers[src];
	inst->_registers[ProgramCounter] += 3;
}

void Core::jumpImmediate(Core* inst) {
	uint32_t val;
	CoreUtils::uintFromBuffer(val, &inst->_data[inst->_registers[ProgramCounter]+1]);
	inst->_registers[ProgramCounter] = val;
	printf("JMP %i\n", val);
}

void Core::jumpRegister(Core* inst) {
	uint8_t val;
	CoreUtils::byteFromBuffer(val, &inst->_data[inst->_registers[ProgramCounter]+1]);
	inst->_registers[ProgramCounter] = inst->_registers[val];
	printf("JMPR %i\n", val);
}

void Core::addImmediate(Core* inst) {
	uint8_t r1;
	int32_t val;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::intFromBuffer(val, &inst->_data[inst->_registers[ProgramCounter]+2]);
	inst->registerSetInt(r1, inst->registerAsInt(r1) + val);
	inst->_registers[ProgramCounter] += 6;
	printf("ADD %i %i\n", r1, val);
}

void Core::subtractImmediate(Core* inst) {
	uint8_t r1;
	int32_t val;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::intFromBuffer(val, &inst->_data[inst->_registers[ProgramCounter]+2]);
	inst->registerSetInt(r1, inst->registerAsInt(r1) - val);
	inst->_registers[ProgramCounter] += 6;
	printf("SUB %i %i\n", r1, val);
}

void Core::multiplyImmediate(Core* inst) {
	uint8_t r1;
	int32_t val;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::intFromBuffer(val, &inst->_data[inst->_registers[ProgramCounter]+2]);
	inst->registerSetInt(r1, inst->registerAsInt(r1) * val);
	inst->_registers[ProgramCounter] += 6;
	printf("MUL %i %i\n", r1, val);
}

void Core::divideImmediate(Core* inst) {
	uint8_t r1;
	int32_t val;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::intFromBuffer(val, &inst->_data[inst->_registers[ProgramCounter]+2]);
	inst->registerSetInt(r1, inst->registerAsInt(r1) / val);
	inst->_registers[ProgramCounter] += 6;
	printf("DIV %i %i\n", r1, val);
}

void Core::greaterThanImmediate(Core* inst) {
	uint8_t r1;
	int32_t val;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::intFromBuffer(val, &inst->_data[inst->_registers[ProgramCounter]+2]);
	inst->registerSetInt(r1, inst->registerAsInt(r1) > val ? 1 : 0);
	inst->_registers[ProgramCounter] += 6;
	printf("GT %i %i\n", r1, val);
}

void Core::lessThanImmediate(Core* inst) {
	uint8_t r1;
	int32_t val;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::intFromBuffer(val, &inst->_data[inst->_registers[ProgramCounter]+2]);
	inst->registerSetInt(r1, inst->registerAsInt(r1) < val ? 1 : 0);
	inst->_registers[ProgramCounter] += 6;
	printf("LT %i %i\n", r1, val);
}

void Core::addRegister(Core* inst) {
	uint8_t r1, r2;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::byteFromBuffer(r2, &inst->_data[inst->_registers[ProgramCounter]+2]);
	inst->registerSetInt(r1, inst->registerAsInt(r1) + inst->registerAsInt(r2));
	inst->_registers[ProgramCounter] += 3;
	printf("ADD %i %i %i\n",r1, r2, inst->_registers[r1]);
}

void Core::subtractRegister(Core* inst) {
	uint8_t r1, r2;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::byteFromBuffer(r2, &inst->_data[inst->_registers[ProgramCounter]+2]);
	inst->registerSetInt(r1, inst->registerAsInt(r1) - inst->registerAsInt(r2));
	inst->_registers[ProgramCounter] += 3;
	printf("SUB %i %i %i\n",r1, r2, inst->_registers[r1]);
}

void Core::multiplyRegister(Core* inst) {
	uint8_t r1, r2;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::byteFromBuffer(r2, &inst->_data[inst->_registers[ProgramCounter]+2]);
	inst->registerSetInt(r1, inst->registerAsInt(r1) * inst->registerAsInt(r2));
	inst->_registers[ProgramCounter] += 3;
	printf("MUL %i %i %i\n",r1, r2, inst->_registers[r1]);
}

void Core::divideRegister(Core* inst) {
	uint8_t r1, r2;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::byteFromBuffer(r2, &inst->_data[inst->_registers[ProgramCounter]+2]);
	inst->registerSetInt(r1, inst->registerAsInt(r1) / inst->registerAsInt(r2));
	inst->_registers[ProgramCounter] += 3;
	printf("DIV %i %i %i\n",r1, r2, inst->_registers[r1]);
}

void Core::greaterThanRegister(Core* inst) {
	uint8_t r1, r2;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::byteFromBuffer(r2, &inst->_data[inst->_registers[ProgramCounter]+2]);
	inst->registerSetInt(r1, inst->registerAsInt(r1) > inst->registerAsInt(r2));
	inst->_registers[ProgramCounter] += 3;
	printf("GT %i %i %i\n",r1, r2, inst->_registers[r1]);
}

void Core::lessThanRegister(Core* inst) {
	uint8_t r1, r2;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::byteFromBuffer(r2, &inst->_data[inst->_registers[ProgramCounter]+2]);
	inst->registerSetInt(r1, inst->registerAsInt(r1) < inst->registerAsInt(r2));
	inst->_registers[ProgramCounter] += 3;
	printf("LT %i %i %i\n",r1, r2, inst->_registers[r1]);
}

void Core::setMemoryInt(Core* inst) {
	uint8_t reg;
	uint32_t loc;
	CoreUtils::byteFromBuffer(reg, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::uintFromBuffer(loc, &inst->_data[inst->_registers[ProgramCounter]+2]);
	CoreUtils::uintToBuffer(inst->_registers[reg], &inst->_data[loc]);
	inst->_registers[ProgramCounter] += 6;
	printf("SETM %i %i %i\n", reg, loc, ((uint32_t*)&inst->_data[loc])[0]);
}

void Core::getMemoryInt(Core* inst) {
	uint8_t reg;
	uint32_t loc;
	CoreUtils::byteFromBuffer(reg, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::uintFromBuffer(loc, &inst->_data[inst->_registers[ProgramCounter]+2]);
	CoreUtils::uintFromBuffer(inst->_registers[reg], &inst->_data[loc]);
	inst->_registers[ProgramCounter] += 6;
	printf("GETM %i %i %i\n", reg, loc, ((uint32_t*)&inst->_data[loc])[0]);
}

void Core::setMemoryIntRegister(Core* inst) {
	uint8_t reg;
	uint8_t locReg;
	CoreUtils::byteFromBuffer(reg, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::byteFromBuffer(locReg, &inst->_data[inst->_registers[ProgramCounter]+2]);
	CoreUtils::uintToBuffer(inst->_registers[reg], &inst->_data[inst->_registers[locReg]]);
	inst->_registers[ProgramCounter] += 3;
	printf("SETM %i %i\n", reg, locReg);
}

void Core::getMemoryIntRegister(Core* inst) {
	uint8_t reg;
	uint8_t locReg;
	CoreUtils::byteFromBuffer(reg, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::byteFromBuffer(locReg, &inst->_data[inst->_registers[ProgramCounter]+2]);
	CoreUtils::uintFromBuffer(inst->_registers[reg], &inst->_data[inst->_registers[locReg]]);
	inst->_registers[ProgramCounter] += 3;
	printf("GETM %i %i\n", reg, locReg);
}

void Core::jumpEqualImmediateImmediate(Core* inst) {
	uint8_t r1;
	uint32_t val, dst;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::uintFromBuffer(val, &inst->_data[inst->_registers[ProgramCounter]+2]);
	CoreUtils::uintFromBuffer(dst, &inst->_data[inst->_registers[ProgramCounter]+6]);
	if (inst->_registers[r1] == val) {
		inst->_registers[ProgramCounter] = dst;
	} else {
		inst->_registers[ProgramCounter] += 10;
	}
	printf("JEQII\n");
}

void Core::jumpNotEqualImmediateImmediate(Core* inst) {
	uint8_t r1;
	uint32_t val, dst;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::uintFromBuffer(val, &inst->_data[inst->_registers[ProgramCounter]+2]);
	CoreUtils::uintFromBuffer(dst, &inst->_data[inst->_registers[ProgramCounter]+6]);
	if (inst->_registers[r1] != val) {
		inst->_registers[ProgramCounter] = dst;
	} else {
		inst->_registers[ProgramCounter] += 10;
	}
	printf("JNEII\n");
}

void Core::jumpEqualImmediateRegister(Core* inst) {
	uint8_t r1, dst;
	uint32_t val;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::uintFromBuffer(val, &inst->_data[inst->_registers[ProgramCounter]+2]);
	CoreUtils::byteFromBuffer(dst, &inst->_data[inst->_registers[ProgramCounter]+6]);
	if (inst->_registers[r1] == val) {
		inst->_registers[ProgramCounter] = inst->_registers[dst];
	} else {
		inst->_registers[ProgramCounter] += 7;
	}
	printf("JEQIR\n");
}

void Core::jumpNotEqualImmediateRegister(Core* inst) {
	uint8_t r1, dst;
	uint32_t val;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::uintFromBuffer(val, &inst->_data[inst->_registers[ProgramCounter]+2]);
	CoreUtils::byteFromBuffer(dst, &inst->_data[inst->_registers[ProgramCounter]+6]);
	if (inst->_registers[r1] != val) {
		inst->_registers[ProgramCounter] = inst->_registers[dst];
	} else {
		inst->_registers[ProgramCounter] += 7;
	}
	printf("JNEIR\n");
}

void Core::jumpEqualRegisterImmediate(Core* inst) {
	uint8_t r1, r2;
	uint32_t dstReg;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::byteFromBuffer(r2, &inst->_data[inst->_registers[ProgramCounter]+2]);
	CoreUtils::uintFromBuffer(dstReg, &inst->_data[inst->_registers[ProgramCounter]+3]);
	if (inst->_registers[r1] == inst->_registers[r2]) {
		inst->_registers[ProgramCounter] = inst->_registers[dstReg];
	} else {
		inst->_registers[ProgramCounter] += 7;
	}
	printf("JEQRI\n");
}

void Core::jumpNotEqualRegisterImmediate(Core* inst) {
	uint8_t r1, r2;
	uint32_t dstReg;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::byteFromBuffer(r2, &inst->_data[inst->_registers[ProgramCounter]+2]);
	CoreUtils::uintFromBuffer(dstReg, &inst->_data[inst->_registers[ProgramCounter]+3]);
	if (inst->_registers[r1] != inst->_registers[r2]) {
		inst->_registers[ProgramCounter] = inst->_registers[dstReg];
	} else {
		inst->_registers[ProgramCounter] += 7;
	}
	printf("JNEQRI\n");
}

void Core::jumpEqualRegisterRegister(Core* inst) {
	uint8_t r1, r2, dstReg;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::byteFromBuffer(r2, &inst->_data[inst->_registers[ProgramCounter]+2]);
	CoreUtils::byteFromBuffer(dstReg, &inst->_data[inst->_registers[ProgramCounter]+3]);
	if (inst->_registers[r1] == inst->_registers[r2]) {
		inst->_registers[ProgramCounter] = inst->_registers[dstReg];
	} else {
		inst->_registers[ProgramCounter] += 4;
	}
	printf("JEQRR\n");
}

void Core::jumpNotEqualRegisterRegister(Core* inst) {
	uint8_t r1, r2, dstReg;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::byteFromBuffer(r2, &inst->_data[inst->_registers[ProgramCounter]+2]);
	CoreUtils::byteFromBuffer(dstReg, &inst->_data[inst->_registers[ProgramCounter]+3]);
	if (inst->_registers[r1] != inst->_registers[r2]) {
		inst->_registers[ProgramCounter] = inst->_registers[dstReg];
	} else {
		inst->_registers[ProgramCounter] += 4;
	}
	printf("JNEQRR\n");
}

void Core::interrupt(Core* inst) {
	uint8_t intNumber;
	CoreUtils::byteFromBuffer(intNumber, inst->_registers[RegisterA]);
	
	if (inst->_intTable[intNumber]) {
		_intTable[intNumber](inst);
		printf("HANDLE INT %i\n", intNumber);
	} else {
		printf("NO INT HANDLER REGISTERED FOR %i\n", intNumber);
	}
}
