#include "vm/core.h"
#include "util/filehelper.h"

void printRam(uint8_t const* data, size_t size) {
	for (unsigned int i = 0; i < size; i++) {
		printf("%02x ", data[i]);
		if (i != 0 && i % 24 == 0) {
			printf("\n");
		}
	}
	if (size % 25 != 0) {
		printf("\n");
	}
}

void printRegisters(VM::RegisterState const* reg) {
	for (unsigned int i = 0; i < VM::NumRegisters; i++) {
		if (reg[i].symbolic) {
			printf("%s:sym ", VM::RegisterUtils::getRegisterName(i));
		} else {
			printf("%s:%u ", VM::RegisterUtils::getRegisterName(i), reg[i].value);
		}
	}
	printf("\n");
}

void printInterrupt(VM::Core* c) {
	printf("HIT PRINT INTERRUPT\n");

	/**
	 * Print VM registers
	 */
	printf("REGISTERS\n");
	printRegisters(c->getState()->getRegisters());

	/**
	 * Print VM ram contents 
	 */
	printf("RAM contents execution\n");
	printRam(c->getState()->getData(), c->getState()->getDataSize());
}

void makeSymbolic(VM::Core* c) {
	c->getState()->makeSymbolic(0xFF & c->getState()->getRegisterUInt(VM::RegisterA));
}

int main(int argc, char** argv) {

	if (argc != 2) {
		printf("Wrong number of args\n");
		return -1;
	}

	uint8_t* data;
	unsigned long size;

	if (!FileHelper::readFileToMemory(argv[1], data, size)) {
		printf("error reading file\n");
		return -1;
	}

	//data is now 'owned' by the VMCore and will be freed by it at the end of execution
	VM::Core c(data, size);
	c.registerInterrupt(0, printInterrupt);
	c.registerInterrupt(1, makeSymbolic);
	c.run();
	
	return 0;
}
