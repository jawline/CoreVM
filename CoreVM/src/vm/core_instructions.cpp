#include "core.h"
#include "coreutils.h"

using namespace VM;

void Core::noOp(Core* inst) {
	setProgramCounter(getProgramCounter()+1);
	printf("NOOP\n");
}

void Core::loadImmediate(Core* inst) {
	uint8_t reg = _state->getDataByte(getProgramCounter()+1);
	uint32_t val = _state->getDataUInt(getProgramCounter()+2);
	inst->_registers[reg] = val;
	setProgramCounter(getProgramCounter() + 6);
	printf("LOAD IMMEDIATE $%i:=%i\n", reg, val);
}

void Core::move(Core* inst) {
	uint8_t dst = _state->getDataByte(getProgramCounter()+1);
	uint8_t src = _state->getDataByte(getProgramCounter()+2);
	_state->setRegisterUint(dst, _state->getRegisterUInt(src));
	setProgramCounter(getProgramCounter()+3);
	printf("MOVE %i %i\n", dst, src);
}

void Core::jumpImmediate(Core* inst) {
	uint32_t val = _state->getDataUInt(getProgramCounter()+1);
	setProgramCounter(val);
	printf("JMP %i\n", val);
}

void Core::jumpRegister(Core* inst) {
	uint8_t reg = _state->getDataByte(getProgramCounter()+1);
	setProgramCounter(_state->getRegisterUInt(reg));
	printf("JMPR %i\n", val);
}

void Core::addImmediate(Core* inst) {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	int32_t val = _state->getDataInt(getProgramCounter()+2);
	_state->setRegisterInt(r1, _state->getRegisterInt(r1) + val);
	setProgramCounter(getProgramCounter() + 6);
	printf("ADD %i %i\n", r1, val);
}

void Core::subtractImmediate(Core* inst) {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	int32_t val = _state->getDataInt(getProgramCounter()+2);
	_state->setRegisterInt(r1, _state->getRegisterInt(r1) - val);
	setProgramCounter(getProgramCounter() + 6);
	printf("SUB %i %i\n", r1, val);
}

void Core::multiplyImmediate(Core* inst) {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	int32_t val = _state->getDataInt(getProgramCounter()+2);
	_state->setRegisterInt(r1, _state->getRegisterInt(r1) * val);
	setProgramCounter(getProgramCounter() + 6);
	printf("MUL %i %i\n", r1, val);
}

void Core::divideImmediate(Core* inst) {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	int32_t val = _state->getDataInt(getProgramCounter()+2);
	_state->setRegisterInt(r1, _state->getRegisterInt(r1) / val);
	setProgramCounter(getProgramCounter() + 6);
	printf("DIV %i %i\n", r1, val);
}

void Core::greaterThanImmediate(Core* inst) {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	int32_t val = _state->getDataInt(getProgramCounter()+2);
	_state->setRegisterInt(r1, _state->getRegisterInt(r1) > val ? 1 : 0);
	setProgramCounter(getProgramCounter() + 6);
	printf("GT %i %i\n", r1, val);
}

void Core::lessThanImmediate(Core* inst) {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	int32_t val = _state->getDataInt(getProgramCounter()+2);
	_state->setRegisterInt(r1, _state->getRegisterInt(r1) < val ? 1 : 0);
	setProgramCounter(getProgramCounter() + 6);
	printf("LT %i %i\n", r1, val);
}

void Core::addRegister(Core* inst) {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	uint8_t r2 = _state->getDataByte(getProgramCounter()+2);
	_state->setRegisterInt(_state->getRegisterInt(r1) + _state->getRegisterInt(r2));
	setProgramCounter(getProgramCounter() + 3);
	printf("ADD %i %i\n", r1, r2);
}

void Core::subtractRegister(Core* inst) {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	uint8_t r2 = _state->getDataByte(getProgramCounter()+2);
	_state->setRegisterInt(_state->getRegisterInt(r1) - _state->getRegisterInt(r2));
	setProgramCounter(getProgramCounter() + 3);
	printf("SUB %i %i\n", r1, r2);
}

void Core::multiplyRegister(Core* inst) {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	uint8_t r2 = _state->getDataByte(getProgramCounter()+2);
	_state->setRegisterInt(_state->getRegisterInt(r1) * _state->getRegisterInt(r2));
	setProgramCounter(getProgramCounter() + 3);
	printf("MUL %i %i\n", r1, r2);
}

void Core::divideRegister(Core* inst) {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	uint8_t r2 = _state->getDataByte(getProgramCounter()+2);
	_state->setRegisterInt(_state->getRegisterInt(r1) / _state->getRegisterInt(r2));
	setProgramCounter(getProgramCounter() + 3);
	printf("DIV %i %i\n", r1, r2);
}

void Core::greaterThanRegister(Core* inst) {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	uint8_t r2 = _state->getDataByte(getProgramCounter()+2);
	_state->setRegisterInt(_state->getRegisterInt(r1) > _state->getRegisterInt(r2) ? 1 : 0);
	setProgramCounter(getProgramCounter() + 3);
	printf("GT %i %i\n", r1, r2);
}

void Core::lessThanRegister(Core* inst) {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	uint8_t r2 = _state->getDataByte(getProgramCounter()+2);
	_state->setRegisterInt(_state->getRegisterInt(r1) < _state->getRegisterInt(r2) ? 1 : 0);
	setProgramCounter(getProgramCounter() + 3);
	printf("LT %i %i\n", r1, r2);
}

void Core::setMemoryInt(Core* inst) {
	uint8_t reg = _state->getDataByte(getProgramCounter()+1);
	uint32_t loc = _state->getDataUInt(getProgramCounter()+2);
	_state->setDataUInt(loc, _state->getRegisterUInt(reg));
	setProgramCounter(getProgramCounter() + 6);
	printf("SETM %i %i\n", reg, loc);
}

void Core::getMemoryInt(Core* inst) {
	uint8_t reg = _state->getDataByte(getProgramCounter()+1);
	uint32_t loc = _state->getDataUInt(getProgramCounter()+2);
	_state->setRegisterUInt(reg, _state->getDataUInt(loc));
	setProgramCounter(getProgramCounter() + 6);
	printf("GETM %i %i\n", reg, loc);
}

void Core::setMemoryIntRegister(Core* inst) {
	uint8_t reg = _state->getDataByte(getProgramCounter()+1);
	uint8_t locReg = _state->getDataByte(getProgramCounter()+2);
	_state->setDataUInt(_state->getRegisterUInt(locReg), _state->getRegisterUInt(reg));
	setProgramCounter(getProgramCounter() + 3);
	printf("SETM %i %i\n", reg, locReg);
}

void Core::getMemoryIntRegister(Core* inst) {
	uint8_t reg = _state->getDataByte(getProgramCounter()+1);
	uint8_t locReg = _state->getDataByte(getProgramCounter()+2);
	_state->setRegisterUInt(reg, _state->getDataUInt(_state->getRegisterUInt(locReg)));
	setProgramCounter(getProgramCounter() + 3);
	printf("GETM %i %i\n", reg, locReg);
}

void Core::jumpEqualImmediateImmediate(Core* inst) {
	uint8_t r1 = _state->getDataByte(getProgramCounter() + 1);
	uint32_t val = _state->getDataUInt(getProgramCounter() + 2);
	uint32_t dst = _state->getDataUInt(getProgramCounter() + 6);
	if (_state->getRegisterUInt(r1) == val) {
		setProgramCounter(dst);
	} else {
		setProgramCounter(getProgramCounter() + 10);
	}
	printf("JEQII\n");
}

void Core::jumpNotEqualImmediateImmediate(Core* inst) {
	uint8_t r1 = _state->getDataByte(getProgramCounter() + 1);
	uint32_t val = _state->getDataUInt(getProgramCounter() + 2);
	uint32_t dst = _state->getDataUInt(getProgramCounter() + 6);
	if (_state->getRegisterUInt(r1) != val) {
		setProgramCounter(dst);
	} else {
		setProgramCounter(getProgramCounter() + 10);
	}
	printf("JNEII\n");
}

void Core::jumpEqualImmediateRegister(Core* inst) {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	uint32_t val = _state->getDataUInt(getProgramCounter()+2);
	uint8_t dst = _state->getDataByte(getProgramCounter()+6);
	if (_state->getRegisterUInt(r1) == val) {
		setProgramCounter(_state->getRegisterUInt(dst));
	} else {
		setProgramCounter(getProgramCounter() + 7);
	}
	printf("JEQIR\n");
}

void Core::jumpNotEqualImmediateRegister(Core* inst) {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	uint32_t val = _state->getDataUInt(getProgramCounter()+2);
	uint8_t dst = _state->getDataByte(getProgramCounter()+6);
	if (_state->getRegisterUInt(r1) != val) {
		setProgramCounter(_state->getRegisterUInt(dst));
	} else {
		setProgramCounter(getProgramCounter() + 7);
	}
	printf("JNEIR\n");
}

void Core::jumpEqualRegisterImmediate(Core* inst) {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	uint8_t r2 = _state->getDataByte(getProgramCounter()+2);
	uint32_t dst = _state->getDataUInt(getProgramCounter()+3);
	if (_state->getRegisterUInt(r1) == _state->getRegisterUInt(r2)) {
		setProgramCounter(dst);
	} else {
		setProgramCounter(getProgramCounter()+7);
	}
	printf("JEQRI\n");
}

void Core::jumpNotEqualRegisterImmediate(Core* inst) {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	uint8_t r2 = _state->getDataByte(getProgramCounter()+2);
	uint32_t dst = _state->getDataUInt(getProgramCounter()+3);
	if (_state->getRegisterUInt(r1) != _state->getRegisterUInt(r2)) {
		setProgramCounter(dst);
	} else {
		setProgramCounter(getProgramCounter()+7);
	}
	printf("JNEQRI\n");
}

void Core::jumpEqualRegisterRegister(Core* inst) {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	uint8_t r2 = _state->getDataByte(getProgramCounter()+2);
	uint8_t dst = _state->getDataByte(getProgramCounter()+3);
	if (_state->getRegisterUInt(r1) == _state->getRegisterUInt(r2)) {
		setProgramCounter(_state->getRegisterUInt(dst));
	} else {
		setProgramCounter(getProgramCounter()+4);
	}
	printf("JEQRR\n");
}

void Core::jumpNotEqualRegisterRegister(Core* inst) {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	uint8_t r2 = _state->getDataByte(getProgramCounter()+2);
	uint8_t dst = _state->getDataByte(getProgramCounter()+3);
	if (_state->getRegisterUInt(r1) != _state->getRegisterUInt(r2)) {
		setProgramCounter(_state->getRegisterUInt(dst));
	} else {
		setProgramCounter(getProgramCounter()+4);
	}
	printf("JNEQRR\n");
}

void Core::interrupt(Core* inst) {
	uint8_t intNumber = _state->getDataByte(getProgramCounter() + 1);

	if (intNumber < 256 && inst->_intTable[intNumber]) {
		inst->_intTable[intNumber](inst);
		printf("HANDLE INT %i\n", intNumber);
	} else {
		printf("NO INT HANDLER REGISTERED FOR %i\n", intNumber);
		if (intNumber >= 256) {
			printf("INTERRUPT NUMBER CANNOT EXCEED 256\n");
		}
	}
	
	setProgramCounter(getProgramCounter() + 2);
}
