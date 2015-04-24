#include "corestate.h"
#include <string.h>

using namespace VM;

CoreState::CoreState(uint8_t* data, unsigned int size) {
	_registers = new uint32_t[NumRegisters];
	memset(_registers, 0, sizeof(uint32_t) * NumRegisters);

	_data = shared_ptr<uint8_t>(data);
	_dataSize = size;
	_copyDataOnWrite = false;
}

CoreState::CoreState(CoreState* existing) {
	_registers = new uint32_t[NumRegisters];
	memcpy(_registers, existing->_registers, sizeof(uint32_t) * NumRegisters);

	_data = existing->_data;
	_dataSize = existing->_dataSize;
	_copyDataOnWrite = true;

	//TODO: This makes the data copy if either state writes to data, ideally the other state
	//would own the data and this state would watch for writes and make a copy then to save
	//allocations
	existing->_copyDataOnWrite = true;
}

CoreState::CoreState(CoreState& existing) {
	_registers = new uint32_t[NumRegisters];
	memcpy(_registers, existing._registers, sizeof(uint32_t) * NumRegisters);

	_data = existing._data;
	_dataSize = existing._dataSize;
	_copyDataOnWrite = true;

	//TODO: This makes the data copy if either state writes to data, ideally the other state
	//would own the data and this state would watch for writes and make a copy then to save
	//allocations
	existing._copyDataOnWrite = true;
}

CoreState::~CoreState() {
	delete _registers;
}

void CoreState::copyData() {
	uint8_t* data = new uint8_t[_dataSize];
	memcpy(data, _data.get(), _dataSize);
	_data = shared_ptr<uint8_t>(data);
	_copyDataOnWrite = false;
}
