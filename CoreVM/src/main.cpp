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
		if (reg[i].isSymbolic()) {
			printf("%s:sym ", VM::RegisterUtils::getRegisterName(i));
		} else {
			printf("%s:%u ", VM::RegisterUtils::getRegisterName(i), reg[i].getValue());
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

	printf("%s", c->getState()->getProblem()->toString().c_str());
}

void makeSymbolic(VM::Core* c) {
	c->getState()->makeSymbolic(0xFF & c->getState()->getRegisterUInt(VM::RegisterA));
}

void failureState(VM::Core* c) {
	if (c->getState()->getProblem()->isSatisfiable()) {
		printf("------------------------------------------------\n");
		printf("-           FAILURE            STATE           -\n");
		printf("------------------------------------------------\n");
		printInterrupt(c);
		printf("------------------------------------------------\n");
		printf("-             END             STATE            -\n");
		printf("------------------------------------------------\n");
	} else {
		printf("------------------------------------------------\n");
		printf("-              NO             FAIL             -\n");
		printf("------------------------------------------------\n");
		printInterrupt(c);
	}
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
	c.registerInterrupt(2, failureState);
	c.run();
	
	return 0;
}
