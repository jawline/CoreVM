#include "corestate.h"

using namespace VM;

void CoreState::copyRegisters() {
	uint32_t* registers = new uint32_t[NumRegisters];
	memcpy(registers, _registers, sizeof(uint32_t) * NumRegisters);
	_registers = make_shared<uint32_t>(registers);
	_copyRegistersOnWrite = false;
}

void CoreState::copyData() {
  uint8_t* data = new uint8_t[_dataSize];
  memcpy(data, _data, _dataSize);
  _data = make_shared<uint8_t>(data);
	_copyDataOnWrite = false;
}
