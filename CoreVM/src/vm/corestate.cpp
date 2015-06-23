#include "corestate.h"
#include <string.h>

using namespace VM;

unsigned long CoreState::_lastSymbol = 0;

CoreState::CoreState(uint8_t* data, unsigned int size) {
	_registers = new RegisterState[NumRegisters];

	_data = shared_ptr<uint8_t>(data);
	_dataSize = size;
	_copyDataOnWrite = false;
	_z3Context = std::shared_ptr<z3::context>(new z3::context());
}

CoreState::CoreState(CoreState* existing) {
	_registers = new RegisterState[NumRegisters];

	_data = existing->_data;
	_dataSize = existing->_dataSize;
	_copyDataOnWrite = true;
	_symState = existing->_symState;
	_z3Context = existing->_z3Context;

	//TODO: This makes the data copy if either state writes to data, ideally the other state
	//would own the data and this state would watch for writes and make a copy then to save
	//allocations
	existing->_copyDataOnWrite = true;
}

CoreState::CoreState(CoreState& existing) {
	_registers = new RegisterState[NumRegisters];
	
	for (unsigned int i = 0; i < NumRegisters; i++) {
		_registers[i] = existing._registers[i];
	}

	_data = existing._data;
	_dataSize = existing._dataSize;
	_copyDataOnWrite = true;
	_z3Context = existing._z3Context;
	_symState = existing._symState;

	//TODO: This makes the data copy if either state writes to data, ideally the other state
	//would own the data and this state would watch for writes and make a copy then to save
	//allocations
	existing._copyDataOnWrite = true;
}

CoreState::~CoreState() {
	delete[] _registers;
}

void CoreState::makeSymbolic(uint8_t registerId) {
	auto var = _z3Context->mk_symbol("symreg" + std::to_string(_lastSymbol++));
	_registers[registerId].setSymbol(var);
}

void CoreState::copyData() {
	uint8_t* data = new uint8_t[_dataSize];
	memcpy(data, _data.get(), _dataSize);
	_data = shared_ptr<uint8_t>(data);
	_copyDataOnWrite = false;
}

RegisterState const* CoreState::getRegisters() const {
	return _registers;
}
        	
uint8_t const* CoreState::getData() const {
	return _data.get();
}
        	
unsigned int CoreState::getDataSize() const {
	return _dataSize;
}
