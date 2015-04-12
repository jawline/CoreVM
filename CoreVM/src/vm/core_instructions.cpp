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

void Core::addImmediate(Core* inst) {
	uint8_t r1;
	int32_t val;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::intFromBuffer(val, &inst->_data[inst->_registers[ProgramCounter]+2]);
	inst->rSetInt(r1, inst->rAsInt(r1) + val);
	inst->_registers[ProgramCounter] += 6;
	printf("ADD %i %i\n", r1, val);
}

void Core::subtractImmediate(Core* inst) {
	uint8_t r1;
	int32_t val;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::intFromBuffer(val, &inst->_data[inst->_registers[ProgramCounter]+2]);
	inst->rSetInt(r1, inst->rAsInt(r1) - val);
	inst->_registers[ProgramCounter] += 6;
	printf("SUB %i %i\n", r1, val);
}

void Core::multiplyImmediate(Core* inst) {
	uint8_t r1;
	int32_t val;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::intFromBuffer(val, &inst->_data[inst->_registers[ProgramCounter]+2]);
	inst->rSetInt(r1, inst->rAsInt(r1) * val);
	inst->_registers[ProgramCounter] += 6;
	printf("MUL %i %i\n", r1, val);
}

void Core::divideImmediate(Core* inst) {
	uint8_t r1;
	int32_t val;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::intFromBuffer(val, &inst->_data[inst->_registers[ProgramCounter]+2]);
	inst->rSetInt(r1, inst->rAsInt(r1) / val);
	inst->_registers[ProgramCounter] += 6;
	printf("DIV %i %i\n", r1, val);
}

void Core::greaterThanImmediate(Core* inst) {
	uint8_t r1;
	int32_t val;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::intFromBuffer(val, &inst->_data[inst->_registers[ProgramCounter]+2]);
	inst->rSetInt(r1, inst->rAsInt(r1) > val ? 1 : 0);
	inst->_registers[ProgramCounter] += 6;
	printf("GT %i %i\n", r1, val);
}

void Core::lessThanImmediate(Core* inst) {
	uint8_t r1;
	int32_t val;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::intFromBuffer(val, &inst->_data[inst->_registers[ProgramCounter]+2]);
	inst->rSetInt(r1, inst->rAsInt(r1) < val ? 1 : 0);
	inst->_registers[ProgramCounter] += 6;
	printf("LT %i %i\n", r1, val);
}

void Core::addRegister(Core* inst) {
	uint8_t r1, r2;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::byteFromBuffer(r2, &inst->_data[inst->_registers[ProgramCounter]+2]);
	inst->rSetInt(r1, inst->rAsInt(r1) + inst->rAsInt(r2));
	inst->_registers[ProgramCounter] += 3;
	printf("ADD %i %i %i\n",r1, r2, inst->_registers[r1]);
}

void Core::subtractRegister(Core* inst) {
	uint8_t r1, r2;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::byteFromBuffer(r2, &inst->_data[inst->_registers[ProgramCounter]+2]);
	inst->rSetInt(r1, inst->rAsInt(r1) - inst->rAsInt(r2));
	inst->_registers[ProgramCounter] += 3;
	printf("SUB %i %i %i\n",r1, r2, inst->_registers[r1]);
}

void Core::multiplyRegister(Core* inst) {
	uint8_t r1, r2;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::byteFromBuffer(r2, &inst->_data[inst->_registers[ProgramCounter]+2]);
	inst->rSetInt(r1, inst->rAsInt(r1) * inst->rAsInt(r2));
	inst->_registers[ProgramCounter] += 3;
	printf("MUL %i %i %i\n",r1, r2, inst->_registers[r1]);
}

void Core::divideRegister(Core* inst) {
	uint8_t r1, r2;
	CoreUtils::byteFromBuffer(r1, &inst->_data[inst->_registers[ProgramCounter]+1]);
	CoreUtils::byteFromBuffer(r2, &inst->_data[inst->_registers[ProgramCounter]+2]);
	inst->rSetInt(r1, inst->rAsInt(r1) / inst->rAsInt(r2));
	inst->_registers[ProgramCounter] += 3;
	printf("DIV %i %i %i\n",r1, r2, inst->_registers[r1]);
}