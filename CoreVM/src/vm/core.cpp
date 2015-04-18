#include "core.h"

using namespace VM;

Core::Core() {
	_registers = new uint32_t[NumRegisters];
	setupJumpTable();
}

Core::~Core() {
	delete[] _registers;
	delete[] _jumpTable;
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