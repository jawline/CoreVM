#include "core.h"
#include "coreutils.h"

using namespace VM;

void Core::noOp(Core* inst) {
	inst->_registers[ProgramCounter] += 1;
	printf("NOOP\n");
}

void Core::loadImmediate(Core* inst) {
	uint8_t reg;
	uint32_t val;
	CoreUtils::byteFromBuffer(reg, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::uintFromBuffer(val, &inst->_data[inst->_registers[ProgramCounter]+2]);
	inst->_registers[reg] = val;
	inst->_registers[ProgramCounter] += 6;
	printf("LOAD IMMEDIATE $%i:=%i\n", reg, val);
}

void Core::jumpImmediate(Core* inst) {
	uint32_t val;
	CoreUtils::uintFromBuffer(val, &inst->_data[inst->_registers[ProgramCounter]+1]);
	inst->_registers[ProgramCounter] = val;
	printf("JMP %i\n", val);
}

void Core::addRegister(Core* inst) {
	uint8_t dst, r1, r2;
	CoreUtils::byteFromBuffer(dst, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+2]);
	CoreUtils::byteFromBuffer(r2, &inst->_data[inst->_registers[ProgramCounter]+3]);
	inst->rSetInt(dst, inst->rAsInt(r1) + inst->rAsInt(r2));
	inst->_registers[ProgramCounter] += 4;
	printf("ADD %i %i %i %i\n", dst, r1, r2, inst->_registers[dst]);
}

void Core::subtractRegister(Core* inst) {
	uint8_t dst, r1, r2;
	CoreUtils::byteFromBuffer(dst, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+2]);
	CoreUtils::byteFromBuffer(r2, &inst->_data[inst->_registers[ProgramCounter]+3]);
	inst->rSetInt(dst, inst->rAsInt(r1) - inst->rAsInt(r2));
	inst->_registers[ProgramCounter] += 4;
	printf("SUB %i %i %i %i\n", dst, r1, r2, inst->_registers[dst]);
}

void Core::multiplyRegister(Core* inst) {
	uint8_t dst, r1, r2;
	CoreUtils::byteFromBuffer(dst, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+2]);
	CoreUtils::byteFromBuffer(r2, &inst->_data[inst->_registers[ProgramCounter]+3]);
	inst->rSetInt(dst, inst->rAsInt(r1) * inst->rAsInt(r2));
	inst->_registers[ProgramCounter] += 4;
	printf("MUL %i %i %i %i\n", dst, r1, r2, inst->_registers[dst]);
}

void Core::divideRegister(Core* inst) {
	uint8_t dst, r1, r2;
	CoreUtils::byteFromBuffer(dst, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+2]);
	CoreUtils::byteFromBuffer(r2, &inst->_data[inst->_registers[ProgramCounter]+3]);
	inst->rSetInt(dst, inst->rAsInt(r1) / inst->rAsInt(r2));
	inst->_registers[ProgramCounter] += 4;
	printf("DIV %i %i %i %i\n", dst, r1, r2, inst->_registers[dst]);
}