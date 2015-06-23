#include "core.h"

using namespace VM;

void Core::noOp() {
	setProgramCounter(getProgramCounter()+1);
	printf("NOOP\n");
}

void Core::loadImmediate() {
	uint8_t reg = _state->getDataByte(getProgramCounter()+1);
	uint32_t val = _state->getDataUInt(getProgramCounter()+2);
	_state->setRegisterUInt(reg, val);
	setProgramCounter(getProgramCounter() + 6);
	printf("LOAD IMMEDIATE %s=%i\n", RegisterUtils::getRegisterName(reg), val);
}

void Core::move() {
	uint8_t dst = _state->getDataByte(getProgramCounter()+1);
	uint8_t src = _state->getDataByte(getProgramCounter()+2);
	_state->moveRegister(dst, src);
	setProgramCounter(getProgramCounter()+3);
	printf("MOVE %i %i\n", dst, src);
}

void Core::jumpImmediate() {
	uint32_t val = _state->getDataUInt(getProgramCounter()+1);
	setProgramCounter(val);
	printf("JMP %i\n", val);
}

void Core::jumpRegister() {
	uint8_t reg = _state->getDataByte(getProgramCounter()+1);
	setProgramCounter(_state->getRegisterUInt(reg));
	printf("JMPR %i\n", reg);
}

void Core::addImmediate() {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	int32_t val = _state->getDataInt(getProgramCounter()+2);

	if (_state->isSymbolic(r1)) {
		_state->addSymbol(r1, val);
	} else {
		_state->setRegisterInt(r1, _state->getRegisterInt(r1) + val);
	}

	setProgramCounter(getProgramCounter() + 6);
	printf("ADD %i %i\n", r1, val);
}

void Core::subtractImmediate() {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	int32_t val = _state->getDataInt(getProgramCounter()+2);

	if (_state->isSymbolic(r1)) {
		_state->addSymbol(r1, -val);
	} else {
		_state->setRegisterInt(r1, _state->getRegisterInt(r1) - val);
	}
	setProgramCounter(getProgramCounter() + 6);
	printf("SUB %i %i\n", r1, val);
}

void Core::multiplyImmediate() {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	int32_t val = _state->getDataInt(getProgramCounter()+2);
	
	if (_state->isSymbolic(r1)) {
		_state->multiplySymbol(r1, val);
		printf("SYMBOLIC MULTIPLY %i %i\n", r1, val);
	} else {
		_state->setRegisterInt(r1, _state->getRegisterInt(r1) * val);
		setProgramCounter(getProgramCounter() + 6);
		printf("MUL %i %i\n", r1, val);
	}
}

void Core::divideImmediate() {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	int32_t val = _state->getDataInt(getProgramCounter()+2);
	
	if (_state->isSymbolic(r1)) {
		_state->divideSymbol(r1, val);
		printf("SYMBOLIC DIVIDE %i %i\n", r1, val);
	} else {
		_state->setRegisterInt(r1, _state->getRegisterInt(r1) / val);
		setProgramCounter(getProgramCounter() + 6);
		printf("DIV %i %i\n", r1, val);
	}
}

void Core::greaterThanImmediate() {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	int32_t val = _state->getDataInt(getProgramCounter()+2);
	setProgramCounter(getProgramCounter() + 6);

	if (_state->isSymbolic(r1)) {
		printf("FORKING\n");
		CoreState *left, *right;
		forkState(left, right);

		#pragma message "TODO: GreaterThanImmediate"
	} else {
		_state->setRegisterInt(r1, _state->getRegisterInt(r1) > val ? 1 : 0);
	}

	printf("GT %i %i\n", r1, val);
}

void Core::lessThanImmediate() {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	int32_t val = _state->getDataInt(getProgramCounter()+2);

	if (_state->isSymbolic(r1)) {
		printf("FORKING\n");
		CoreState *left, *right;
		forkState(left, right);

		#pragma message "TODO: LessThanImmediate"
	} else {
		_state->setRegisterInt(r1, _state->getRegisterInt(r1) < val ? 1 : 0);
	}
	setProgramCounter(getProgramCounter() + 6);
	printf("LT %i %i\n", r1, val);
}

void Core::addRegister() {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	uint8_t r2 = _state->getDataByte(getProgramCounter()+2);
	_state->setRegisterInt(r1, _state->getRegisterInt(r1) + _state->getRegisterInt(r2));
	setProgramCounter(getProgramCounter() + 3);
	printf("ADD %i %i\n", r1, r2);
}

void Core::subtractRegister() {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	uint8_t r2 = _state->getDataByte(getProgramCounter()+2);
	_state->setRegisterInt(r1, _state->getRegisterInt(r1) - _state->getRegisterInt(r2));
	setProgramCounter(getProgramCounter() + 3);
	printf("SUB %i %i\n", r1, r2);
}

void Core::multiplyRegister() {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	uint8_t r2 = _state->getDataByte(getProgramCounter()+2);
	
	bool r1Reg = _state->isSymbolic(r1);
	bool r2Reg = _state->isSymbolic(r2);
	
	if (r1Reg && r2Reg) {
	} else if (r1Reg) {
	} else if (r2Reg) {
	} else {
		_state->setRegisterInt(r1, _state->getRegisterInt(r1) * _state->getRegisterInt(r2));
		setProgramCounter(getProgramCounter() + 3);
		printf("MUL %i %i\n", r1, r2);
	}
}

void Core::divideRegister() {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	uint8_t r2 = _state->getDataByte(getProgramCounter()+2);
	
	bool r1Reg = _state->isSymbolic(r1);
	bool r2Reg = _state->isSymbolic(r2);
	
	if (r1Reg && r2Reg) {
		printf("NONLINEAR NOT SUPPORTED YET\n");
	} else if (r1Reg) {
	} else if (r2Reg) {
	} else {
		_state->setRegisterInt(r1, _state->getRegisterInt(r1) / _state->getRegisterInt(r2));
		setProgramCounter(getProgramCounter() + 3);
		printf("DIV %i %i\n", r1, r2);
	}
}

void Core::greaterThanRegister() {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	uint8_t r2 = _state->getDataByte(getProgramCounter()+2);
	_state->setRegisterInt(r1, _state->getRegisterInt(r1) > _state->getRegisterInt(r2) ? 1 : 0);
	setProgramCounter(getProgramCounter() + 3);
	printf("GT %i %i\n", r1, r2);
}

void Core::lessThanRegister() {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	uint8_t r2 = _state->getDataByte(getProgramCounter()+2);
	_state->setRegisterInt(r1, _state->getRegisterInt(r1) < _state->getRegisterInt(r2) ? 1 : 0);
	setProgramCounter(getProgramCounter() + 3);
	printf("LT %i %i\n", r1, r2);
}

void Core::setMemoryInt() {
	uint8_t reg = _state->getDataByte(getProgramCounter()+1);
	uint32_t loc = _state->getDataUInt(getProgramCounter()+2);
	_state->setDataUInt(loc, _state->getRegisterUInt(reg));
	setProgramCounter(getProgramCounter() + 6);
	printf("WARNING: SETM CANNOT HANDLE SYMBOLIC VALUES\n");
	printf("SETM %i %i\n", reg, loc);
}

void Core::getMemoryInt() {
	uint8_t reg = _state->getDataByte(getProgramCounter()+1);
	uint32_t loc = _state->getDataUInt(getProgramCounter()+2);
	_state->setRegisterUInt(reg, _state->getDataUInt(loc));
	setProgramCounter(getProgramCounter() + 6);
	printf("WARNING: GETM CANNOT HANDLE SYMBOLIC VALUES\n");
	printf("GETM %i %i\n", reg, loc);
}

void Core::setMemoryIntRegister() {
	uint8_t reg = _state->getDataByte(getProgramCounter()+1);
	uint8_t locReg = _state->getDataByte(getProgramCounter()+2);
	_state->setDataUInt(_state->getRegisterUInt(locReg), _state->getRegisterUInt(reg));
	setProgramCounter(getProgramCounter() + 3);
	printf("WARNING: SETM CANNOT HANDLE SYMBOLIC VALUES\n");
	printf("SETM %i %i\n", reg, locReg);
}

void Core::getMemoryIntRegister() {
	uint8_t reg = _state->getDataByte(getProgramCounter()+1);
	uint8_t locReg = _state->getDataByte(getProgramCounter()+2);
	_state->setRegisterUInt(reg, _state->getDataUInt(_state->getRegisterUInt(locReg)));
	setProgramCounter(getProgramCounter() + 3);
	printf("WARNING: GETM CANNOT HANDLE SYMBOLIC VALUES\n");
	printf("GETM %i %i\n", reg, locReg);
}

void Core::jumpEqualImmediateImmediate() {
	uint8_t r1 = _state->getDataByte(getProgramCounter() + 1);
	uint32_t val = _state->getDataUInt(getProgramCounter() + 2);
	uint32_t dst = _state->getDataUInt(getProgramCounter() + 6);

	//Symbolic jump
	if (_state->isSymbolic(r1)) {
		printf("FORKING\n");
		CoreState *left, *right;
		forkState(left, right);

		#pragma message "TODO: JumpEqualImmediateImmediate"
		setProgramCounter(left, dst);
		setProgramCounter(right, getProgramCounter(right) + 10);
	} else { //Not symbolic, do normal jump
		if (_state->getRegisterUInt(r1) == val) {
			setProgramCounter(dst);
		} else {
			setProgramCounter(getProgramCounter() + 10);
		}
	}

	printf("JEQII\n");
}

void Core::jumpNotEqualImmediateImmediate() {
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

void Core::jumpEqualImmediateRegister() {
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

void Core::jumpNotEqualImmediateRegister() {
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

void Core::jumpEqualRegisterImmediate() {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	uint8_t r2 = _state->getDataByte(getProgramCounter()+2);
	uint32_t dst = _state->getDataUInt(getProgramCounter()+3);

	if (_state->isSymbolic(r1) && _state->isSymbolic(r2)) {
		printf("FORKING\n");
		CoreState *left, *right;
		forkState(left, right);

		#pragma message "TODO: JumpEqualRegisterImmediate"

		setProgramCounter(left, dst);
		setProgramCounter(right, getProgramCounter(right) + 7);
	} else {
		if (_state->getRegisterUInt(r1) == _state->getRegisterUInt(r2)) {
			setProgramCounter(dst);
		} else {
			setProgramCounter(getProgramCounter()+7);
		}
	}
	printf("JEQRI\n");
}

void Core::jumpNotEqualRegisterImmediate() {
	uint8_t r1 = _state->getDataByte(getProgramCounter()+1);
	uint8_t r2 = _state->getDataByte(getProgramCounter()+2);
	uint32_t dst = _state->getDataUInt(getProgramCounter()+3);
	
	bool r1Sym = _state->isSymbolic(r1);
	bool r2Sym = _state->isSymbolic(r2);

	if (r1Sym && r2Sym) {
		printf("FORKING\n");
		CoreState *left, *right;
		forkState(left, right);
		printf("TODO: LEFT CONSTRAINT  r1  != r2\n");
		printf("TODO: RIGHT CONSTRAINT r1 = r2\n");

		#pragma message "TODO: jumpNotEqualRegisterImmediate"

		setProgramCounter(left, dst);
		setProgramCounter(right, getProgramCounter(right) + 7);
	} else if (r1Sym) {
		#pragma message "TODO: jumpNotEqualRegisterImmediate 1 sym"
	} else if (r2Sym) {
		#pragma message "TODO: jumpNotEqualRegisterImmediate 1 sym (2nd)"
	} else {
		if (_state->getRegisterUInt(r1) != _state->getRegisterUInt(r2)) {
			setProgramCounter(dst);
		} else {
			setProgramCounter(getProgramCounter()+7);
		}
	}
	printf("JNERI\n");
}

void Core::jumpEqualRegisterRegister() {
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

void Core::jumpNotEqualRegisterRegister() {
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

void Core::interrupt() {
	uint8_t intNumber = _state->getDataByte(getProgramCounter() + 1);

	if (_intTable[intNumber]) {
		_intTable[intNumber](this);
		printf("HANDLE INT %i\n", intNumber);
	} else {
		printf("NO INT HANDLER REGISTERED FOR %i\n", intNumber);
	}
	
	setProgramCounter(getProgramCounter() + 2);
}
