#include "vm/core.h"
#include "util/filehelper.h"

void printRam(uint8_t* data, size_t size) {
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

void printInterrupt(VM::Core* inst) {
	printf("HIT PRINT INTERRUPT\n");
}

void makeSymbolInterrupt(VM::Core* inst) {
	printf("MAKE SYMBOL INTERRUPT\n");
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
	c.registerInterrupt(1, makeSymbolInterrupt);
	
	/**
	 * Print VM ram at start of execution
	 */
	printf("RAM at start of execution\n");
	printRam(c.getState()->getData(), c.getState()->getDataSize());

	c.run();

	/**
	 * Print VM ram at end of execution
	 */
	printf("RAM at end of execution\n");
	printRam(c.getState()->getData(), c.getState()->getDataSize());
	
	return 0;
}
