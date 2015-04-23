#include "corestate.h"

using namespace VM;

CoreState::CoreState(uint8_t* data, unsigned int size) {
	_registers = make_shared<uint32_t>(new uint32_t[NumRegisters]);
	_data = make_shared<uint8_t>(data);
	_dataSize = size;
	_copyRegistersOnWrite = false;
	_copyDataOnWrite = false;
}

CoreState::CoreState(CoreState const& existing) {
	_data = existing._data;
	_dataSize = existing._dataSize;
	_registers = existing._registers;
	_copyRegistersOnWrite = true;
	_copyDataOnWrite = true;
}

void CoreState::copyRegisters() {
	uint32_t* registers = new uint32_t[NumRegisters];
	memcpy(registers, _registers.get(), sizeof(uint32_t) * NumRegisters);
	_registers = make_shared<uint32_t>(registers);
	_copyRegistersOnWrite = false;
}

void CoreState::copyData() {
	uint8_t* data = new uint8_t[_dataSize];
	memcpy(data, _data.get(), _dataSize);
	_data = make_shared<uint8_t>(data);
	_copyDataOnWrite = false;
}
