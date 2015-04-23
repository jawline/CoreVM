#include "core.h"

using namespace VM;
using namespace std::placeholders;

Core::Core(uint8_t* data, unsigned int dataSize) {
	_state = new CoreState(data, dataSize);
	setupJumpTable();
	setupIntTable();
}

Core::~Core() {
	delete _state;
	delete[] _intTable;
	delete[] _jumpTable;
}

void Core::setupIntTable() {
	_intTable = new std::function<void(Core*)>[256];
	for (unsigned int i = 0; i < 256; i++) {
		_intTable[i] = nullptr;
	}
}

void Core::setupJumpTable() {
	_jumpTable = new std::function<void()>[NumInstructions];
	
	_jumpTable[NoOp] = std::bind(&Core::noOp, this);
	_jumpTable[LoadImmediate] = std::bind(&Core::loadImmediate, this);
	_jumpTable[Move] = std::bind(&Core::move, this);

	_jumpTable[AddImmediate] = std::bind(&Core::addImmediate, this);
	_jumpTable[SubtractImmediate] = std::bind(&Core::subtractImmediate, this);
	_jumpTable[MultiplyImmediate] = std::bind(&Core::multiplyImmediate, this);
	_jumpTable[DivideImmediate] = std::bind(&Core::divideImmediate, this);
	_jumpTable[GreaterThanImmediate] = std::bind(&Core::greaterThanImmediate, this);
	_jumpTable[LessThanImmediate] = std::bind(&Core::lessThanImmediate, this);

	_jumpTable[AddRegister] = std::bind(&Core::addRegister, this);
	_jumpTable[SubtractRegister] = std::bind(&Core::subtractRegister, this);
	_jumpTable[MultiplyRegister] = std::bind(&Core::multiplyRegister, this);
	_jumpTable[DivideRegister] = std::bind(&Core::divideRegister, this);
	_jumpTable[GreaterThanRegister] = std::bind(&Core::lessThanRegister, this);
	_jumpTable[LessThanRegister] = std::bind(&Core::greaterThanRegister, this);

	_jumpTable[SetMemoryInt] = std::bind(&Core::setMemoryInt, this);
	_jumpTable[GetMemoryInt] = std::bind(&Core::getMemoryInt, this);
	
	_jumpTable[SetMemoryIntRegister] = std::bind(&Core::setMemoryIntRegister, this);
	_jumpTable[GetMemoryIntRegister] = std::bind(&Core::getMemoryIntRegister, this);

	_jumpTable[JumpImmediate] = std::bind(&Core::jumpImmediate, this);
	_jumpTable[JumpRegister] = std::bind(&Core::jumpRegister, this);

	_jumpTable[JumpEqualImmediateImmediate] = std::bind(&Core::jumpEqualImmediateImmediate, this);
	_jumpTable[JumpNotEqualImmediateImmediate] = std::bind(&Core::jumpNotEqualImmediateImmediate, this);
	_jumpTable[JumpEqualRegisterImmediate] = std::bind(&Core::jumpEqualRegisterImmediate, this);
	_jumpTable[JumpNotEqualRegisterImmediate] = std::bind(&Core::jumpNotEqualRegisterImmediate, this);

	_jumpTable[JumpEqualImmediateRegister] = std::bind(&Core::jumpEqualImmediateRegister, this);
	_jumpTable[JumpNotEqualImmediateRegister] = std::bind(&Core::jumpNotEqualImmediateRegister, this);
	_jumpTable[JumpEqualRegisterRegister] = std::bind(&Core::jumpEqualRegisterRegister, this);
	_jumpTable[JumpNotEqualRegisterRegister] = std::bind(&Core::jumpNotEqualRegisterRegister, this);
	
	_jumpTable[Interrupt] = std::bind(&Core::interrupt, this);
}

CoreState* Core::getState() {
	return _state;
}

void Core::run() {
	setProgramCounter(0);
	while (getProgramCounter() < _state->getDataSize()) {
		_jumpTable[_state->getDataByte(getProgramCounter())]();
	}
}

void Core::registerInterrupt(uint8_t interruptNumber, std::function<void(Core*)> callback) {
	_intTable[interruptNumber] = callback;
}
