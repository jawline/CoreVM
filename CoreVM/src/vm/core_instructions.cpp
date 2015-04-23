#include "core.h"
#include "coreutils.h"

using namespace VM;

void Core::noOp(Core* inst) {
	inst->setProgramCounter(inst->getProgramCounter()+1);
	printf("NOOP\n");
}

void Core::loadImmediate(Core* inst) {
	uint8_t reg = inst->_state->getDataByte(inst->getProgramCounter()+1);
	uint32_t val = inst->_state->getDataUInt(inst->getProgramCounter()+2);
	inst->_state->setRegisterUInt(reg, val);
	inst->setProgramCounter(inst->getProgramCounter() + 6);
	printf("LOAD IMMEDIATE $%i:=%i\n", reg, val);
}

void Core::move(Core* inst) {
	uint8_t dst = inst->_state->getDataByte(inst->getProgramCounter()+1);
	uint8_t src = inst->_state->getDataByte(inst->getProgramCounter()+2);
	inst->_state->setRegisterUInt(dst, inst->_state->getRegisterUInt(src));
	inst->setProgramCounter(inst->getProgramCounter()+3);
	printf("MOVE %i %i\n", dst, src);
}

void Core::jumpImmediate(Core* inst) {
	uint32_t val = inst->_state->getDataUInt(inst->getProgramCounter()+1);
	inst->setProgramCounter(val);
	printf("JMP %i\n", val);
}

void Core::jumpRegister(Core* inst) {
	uint8_t reg = inst->_state->getDataByte(inst->getProgramCounter()+1);
	inst->setProgramCounter(inst->_state->getRegisterUInt(reg));
	printf("JMPR %i\n", reg);
}

void Core::addImmediate(Core* inst) {
	uint8_t r1 = inst->_state->getDataByte(inst->getProgramCounter()+1);
	int32_t val = inst->_state->getDataInt(inst->getProgramCounter()+2);
	inst->_state->setRegisterInt(r1, inst->_state->getRegisterInt(r1) + val);
	inst->setProgramCounter(inst->getProgramCounter() + 6);
	printf("ADD %i %i\n", r1, val);
}

void Core::subtractImmediate(Core* inst) {
	uint8_t r1 = inst->_state->getDataByte(inst->getProgramCounter()+1);
	int32_t val = inst->_state->getDataInt(inst->getProgramCounter()+2);
	inst->_state->setRegisterInt(r1, inst->_state->getRegisterInt(r1) - val);
	inst->setProgramCounter(inst->getProgramCounter() + 6);
	printf("SUB %i %i\n", r1, val);
}

void Core::multiplyImmediate(Core* inst) {
	uint8_t r1 = inst->_state->getDataByte(inst->getProgramCounter()+1);
	int32_t val = inst->_state->getDataInt(inst->getProgramCounter()+2);
	inst->_state->setRegisterInt(r1, inst->_state->getRegisterInt(r1) * val);
	inst->setProgramCounter(inst->getProgramCounter() + 6);
	printf("MUL %i %i\n", r1, val);
}

void Core::divideImmediate(Core* inst) {
	uint8_t r1 = inst->_state->getDataByte(inst->getProgramCounter()+1);
	int32_t val = inst->_state->getDataInt(inst->getProgramCounter()+2);
	inst->_state->setRegisterInt(r1, inst->_state->getRegisterInt(r1) / val);
	inst->setProgramCounter(inst->getProgramCounter() + 6);
	printf("DIV %i %i\n", r1, val);
}

void Core::greaterThanImmediate(Core* inst) {
	uint8_t r1 = inst->_state->getDataByte(inst->getProgramCounter()+1);
	int32_t val = inst->_state->getDataInt(inst->getProgramCounter()+2);
	inst->_state->setRegisterInt(r1, inst->_state->getRegisterInt(r1) > val ? 1 : 0);
	inst->setProgramCounter(inst->getProgramCounter() + 6);
	printf("GT %i %i\n", r1, val);
}

void Core::lessThanImmediate(Core* inst) {
	uint8_t r1 = inst->_state->getDataByte(inst->getProgramCounter()+1);
	int32_t val = inst->_state->getDataInt(inst->getProgramCounter()+2);
	inst->_state->setRegisterInt(r1, inst->_state->getRegisterInt(r1) < val ? 1 : 0);
	inst->setProgramCounter(inst->getProgramCounter() + 6);
	printf("LT %i %i\n", r1, val);
}

void Core::addRegister(Core* inst) {
	uint8_t r1 = inst->_state->getDataByte(inst->getProgramCounter()+1);
	uint8_t r2 = inst->_state->getDataByte(inst->getProgramCounter()+2);
	inst->_state->setRegisterInt(r1, inst->_state->getRegisterInt(r1) + inst->_state->getRegisterInt(r2));
	inst->setProgramCounter(inst->getProgramCounter() + 3);
	printf("ADD %i %i\n", r1, r2);
}

void Core::subtractRegister(Core* inst) {
	uint8_t r1 = inst->_state->getDataByte(inst->getProgramCounter()+1);
	uint8_t r2 = inst->_state->getDataByte(inst->getProgramCounter()+2);
	inst->_state->setRegisterInt(r1, inst->_state->getRegisterInt(r1) - inst->_state->getRegisterInt(r2));
	inst->setProgramCounter(inst->getProgramCounter() + 3);
	printf("SUB %i %i\n", r1, r2);
}

void Core::multiplyRegister(Core* inst) {
	uint8_t r1 = inst->_state->getDataByte(inst->getProgramCounter()+1);
	uint8_t r2 = inst->_state->getDataByte(inst->getProgramCounter()+2);
	inst->_state->setRegisterInt(r1, inst->_state->getRegisterInt(r1) * inst->_state->getRegisterInt(r2));
	inst->setProgramCounter(inst->getProgramCounter() + 3);
	printf("MUL %i %i\n", r1, r2);
}

void Core::divideRegister(Core* inst) {
	uint8_t r1 = inst->_state->getDataByte(inst->getProgramCounter()+1);
	uint8_t r2 = inst->_state->getDataByte(inst->getProgramCounter()+2);
	inst->_state->setRegisterInt(r1, inst->_state->getRegisterInt(r1) / inst->_state->getRegisterInt(r2));
	inst->setProgramCounter(inst->getProgramCounter() + 3);
	printf("DIV %i %i\n", r1, r2);
}

void Core::greaterThanRegister(Core* inst) {
	uint8_t r1 = inst->_state->getDataByte(inst->getProgramCounter()+1);
	uint8_t r2 = inst->_state->getDataByte(inst->getProgramCounter()+2);
	inst->_state->setRegisterInt(r1, inst->_state->getRegisterInt(r1) > inst->_state->getRegisterInt(r2) ? 1 : 0);
	inst->setProgramCounter(inst->getProgramCounter() + 3);
	printf("GT %i %i\n", r1, r2);
}

void Core::lessThanRegister(Core* inst) {
	uint8_t r1 = inst->_state->getDataByte(inst->getProgramCounter()+1);
	uint8_t r2 = inst->_state->getDataByte(inst->getProgramCounter()+2);
	inst->_state->setRegisterInt(r1, inst->_state->getRegisterInt(r1) < inst->_state->getRegisterInt(r2) ? 1 : 0);
	inst->setProgramCounter(inst->getProgramCounter() + 3);
	printf("LT %i %i\n", r1, r2);
}

void Core::setMemoryInt(Core* inst) {
	uint8_t reg = inst->_state->getDataByte(inst->getProgramCounter()+1);
	uint32_t loc = inst->_state->getDataUInt(inst->getProgramCounter()+2);
	inst->_state->setDataUInt(loc, inst->_state->getRegisterUInt(reg));
	inst->setProgramCounter(inst->getProgramCounter() + 6);
	printf("SETM %i %i\n", reg, loc);
}

void Core::getMemoryInt(Core* inst) {
	uint8_t reg = inst->_state->getDataByte(inst->getProgramCounter()+1);
	uint32_t loc = inst->_state->getDataUInt(inst->getProgramCounter()+2);
	inst->_state->setRegisterUInt(reg, inst->_state->getDataUInt(loc));
	inst->setProgramCounter(inst->getProgramCounter() + 6);
	printf("GETM %i %i\n", reg, loc);
}

void Core::setMemoryIntRegister(Core* inst) {
	uint8_t reg = inst->_state->getDataByte(inst->getProgramCounter()+1);
	uint8_t locReg = inst->_state->getDataByte(inst->getProgramCounter()+2);
	inst->_state->setDataUInt(inst->_state->getRegisterUInt(locReg), inst->_state->getRegisterUInt(reg));
	inst->setProgramCounter(inst->getProgramCounter() + 3);
	printf("SETM %i %i\n", reg, locReg);
}

void Core::getMemoryIntRegister(Core* inst) {
	uint8_t reg = inst->_state->getDataByte(inst->getProgramCounter()+1);
	uint8_t locReg = inst->_state->getDataByte(inst->getProgramCounter()+2);
	inst->_state->setRegisterUInt(reg, inst->_state->getDataUInt(inst->_state->getRegisterUInt(locReg)));
	inst->setProgramCounter(inst->getProgramCounter() + 3);
	printf("GETM %i %i\n", reg, locReg);
}

void Core::jumpEqualImmediateImmediate(Core* inst) {
	uint8_t r1 = inst->_state->getDataByte(inst->getProgramCounter() + 1);
	uint32_t val = inst->_state->getDataUInt(inst->getProgramCounter() + 2);
	uint32_t dst = inst->_state->getDataUInt(inst->getProgramCounter() + 6);
	if (inst->_state->getRegisterUInt(r1) == val) {
		inst->setProgramCounter(dst);
	} else {
		inst->setProgramCounter(inst->getProgramCounter() + 10);
	}
	printf("JEQII\n");
}

void Core::jumpNotEqualImmediateImmediate(Core* inst) {
	uint8_t r1 = inst->_state->getDataByte(inst->getProgramCounter() + 1);
	uint32_t val = inst->_state->getDataUInt(inst->getProgramCounter() + 2);
	uint32_t dst = inst->_state->getDataUInt(inst->getProgramCounter() + 6);
	if (inst->_state->getRegisterUInt(r1) != val) {
		inst->setProgramCounter(dst);
	} else {
		inst->setProgramCounter(inst->getProgramCounter() + 10);
	}
	printf("JNEII\n");
}

void Core::jumpEqualImmediateRegister(Core* inst) {
	uint8_t r1 = inst->_state->getDataByte(inst->getProgramCounter()+1);
	uint32_t val = inst->_state->getDataUInt(inst->getProgramCounter()+2);
	uint8_t dst = inst->_state->getDataByte(inst->getProgramCounter()+6);
	if (inst->_state->getRegisterUInt(r1) == val) {
		inst->setProgramCounter(inst->_state->getRegisterUInt(dst));
	} else {
		inst->setProgramCounter(inst->getProgramCounter() + 7);
	}
	printf("JEQIR\n");
}

void Core::jumpNotEqualImmediateRegister(Core* inst) {
	uint8_t r1 = inst->_state->getDataByte(inst->getProgramCounter()+1);
	uint32_t val = inst->_state->getDataUInt(inst->getProgramCounter()+2);
	uint8_t dst = inst->_state->getDataByte(inst->getProgramCounter()+6);
	if (inst->_state->getRegisterUInt(r1) != val) {
		inst->setProgramCounter(inst->_state->getRegisterUInt(dst));
	} else {
		inst->setProgramCounter(inst->getProgramCounter() + 7);
	}
	printf("JNEIR\n");
}

void Core::jumpEqualRegisterImmediate(Core* inst) {
	uint8_t r1 = inst->_state->getDataByte(inst->getProgramCounter()+1);
	uint8_t r2 = inst->_state->getDataByte(inst->getProgramCounter()+2);
	uint32_t dst = inst->_state->getDataUInt(inst->getProgramCounter()+3);
	if (inst->_state->getRegisterUInt(r1) == inst->_state->getRegisterUInt(r2)) {
		inst->setProgramCounter(dst);
	} else {
		inst->setProgramCounter(inst->getProgramCounter()+7);
	}
	printf("JEQRI\n");
}

void Core::jumpNotEqualRegisterImmediate(Core* inst) {
	uint8_t r1 = inst->_state->getDataByte(inst->getProgramCounter()+1);
	uint8_t r2 = inst->_state->getDataByte(inst->getProgramCounter()+2);
	uint32_t dst = inst->_state->getDataUInt(inst->getProgramCounter()+3);
	if (inst->_state->getRegisterUInt(r1) != inst->_state->getRegisterUInt(r2)) {
		inst->setProgramCounter(dst);
	} else {
		inst->setProgramCounter(inst->getProgramCounter()+7);
	}
	printf("JNEQRI\n");
}

void Core::jumpEqualRegisterRegister(Core* inst) {
	uint8_t r1 = inst->_state->getDataByte(inst->getProgramCounter()+1);
	uint8_t r2 = inst->_state->getDataByte(inst->getProgramCounter()+2);
	uint8_t dst = inst->_state->getDataByte(inst->getProgramCounter()+3);
	if (inst->_state->getRegisterUInt(r1) == inst->_state->getRegisterUInt(r2)) {
		inst->setProgramCounter(inst->_state->getRegisterUInt(dst));
	} else {
		inst->setProgramCounter(inst->getProgramCounter()+4);
	}
	printf("JEQRR\n");
}

void Core::jumpNotEqualRegisterRegister(Core* inst) {
	uint8_t r1 = inst->_state->getDataByte(inst->getProgramCounter()+1);
	uint8_t r2 = inst->_state->getDataByte(inst->getProgramCounter()+2);
	uint8_t dst = inst->_state->getDataByte(inst->getProgramCounter()+3);
	if (inst->_state->getRegisterUInt(r1) != inst->_state->getRegisterUInt(r2)) {
		inst->setProgramCounter(inst->_state->getRegisterUInt(dst));
	} else {
		inst->setProgramCounter(inst->getProgramCounter()+4);
	}
	printf("JNEQRR\n");
}

void Core::interrupt(Core* inst) {
	uint8_t intNumber = inst->_state->getDataByte(inst->getProgramCounter() + 1);

	if (intNumber < 256 && inst->_intTable[intNumber]) {
		inst->_intTable[intNumber](inst);
		printf("HANDLE INT %i\n", intNumber);
	} else {
		printf("NO INT HANDLER REGISTERED FOR %i\n", intNumber);
		if (intNumber >= 256) {
			printf("INTERRUPT NUMBER CANNOT EXCEED 256\n");
		}
	}
	
	inst->setProgramCounter(inst->getProgramCounter() + 2);
}
