#include "core.h"

using namespace VM;

Core::Core() {
	_registers = new uint32_t[NumRegisters];
	setupJumpTable();
	setupIntTable();
}

Core::~Core() {
	delete[] _registers;
	delete[] _jumpTable;
}

void Core::setupIntTable() {
	_jumpTable = new std::function<void(Core*)>[256];
	for (unsigned int i = 0; i < 256; i++) {
		_jumpTable[i] = nullptr;
	}
}

void Core::setupJumpTable() {
	_jumpTable = new std::function<void(Core*)>[NumInstructions];
	
	_jumpTable[NoOp] = &Core::noOp;
	_jumpTable[LoadImmediate] = &Core::loadImmediate;
	_jumpTable[Move] = &Core::move;

	_jumpTable[AddImmediate] = &Core::addImmediate;
	_jumpTable[SubtractImmediate] = &Core::subtractImmediate;
	_jumpTable[MultiplyImmediate] = &Core::multiplyImmediate;
	_jumpTable[DivideImmediate] = &Core::divideImmediate;
	_jumpTable[GreaterThanImmediate] = &Core::greaterThanImmediate;
	_jumpTable[LessThanImmediate] = &Core::lessThanImmediate;

	_jumpTable[AddRegister] = &Core::addRegister;
	_jumpTable[SubtractRegister] = &Core::subtractRegister;
	_jumpTable[MultiplyRegister] = &Core::multiplyRegister;
	_jumpTable[DivideRegister] = &Core::divideRegister;
	_jumpTable[GreaterThanRegister] = &Core::lessThanRegister;
	_jumpTable[LessThanRegister] = &Core::greaterThanRegister;

	_jumpTable[SetMemoryInt] = &Core::setMemoryInt;
	_jumpTable[GetMemoryInt] = &Core::getMemoryInt;
	
	_jumpTable[SetMemoryIntRegister] = &Core::setMemoryIntRegister;
	_jumpTable[GetMemoryIntRegister] = &Core::getMemoryIntRegister;

	_jumpTable[JumpImmediate] = &Core::jumpImmediate;
	_jumpTable[JumpRegister] = &Core::jumpRegister;

	_jumpTable[JumpEqualImmediateImmediate] = jumpEqualImmediateImmediate;
	_jumpTable[JumpNotEqualImmediateImmediate] = jumpNotEqualImmediateImmediate;
	_jumpTable[JumpEqualRegisterImmediate] = jumpEqualRegisterImmediate;
	_jumpTable[JumpNotEqualRegisterImmediate] = jumpNotEqualRegisterImmediate;

	_jumpTable[JumpEqualImmediateRegister] = jumpEqualImmediateRegister;
	_jumpTable[JumpNotEqualImmediateRegister] = jumpNotEqualImmediateRegister;
	_jumpTable[JumpEqualRegisterRegister] = jumpEqualRegisterRegister;
	_jumpTable[JumpNotEqualRegisterRegister] = jumpNotEqualRegisterRegister;
	
	_jumpTable[Interrupt] = interrupt;
}

void Core::setData(uint8_t* data, unsigned int dataSize) {
	_data = data;
	_maxData = dataSize;
}

void Core::run() {
	_registers[ProgramCounter] = 0;
	while (_registers[ProgramCounter] < _maxData) {
		_jumpTable[_data[_registers[ProgramCounter]]](this);
	}
}

int Core::registerAsInt(unsigned int const& registerNumber) const {
	return ((int*)&_registers[registerNumber])[0];
}

void Core::registerSetInt(unsigned int const& registerNumber, int const& val) {
	((int*)&_registers[registerNumber])[0] = val;
}


void Core::registerInterrupt(uint8_t interruptNumber, std::function<void(Core*)> callback) {
	_intTable[interruptNumber] = callback;
}
