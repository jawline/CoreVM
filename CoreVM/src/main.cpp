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
	
	/**
	 * Print VM ram at start of execution
	 */
	printf("RAM at start of execution\n");
	printRam(data, size);

	VM::CoreState* state = new VM::CoreState(data, size);

	VM::Core c;
	c.registerInterrupt(0, printInterrupt);
	c.registerInterrupt(1, makeSymbolInterrupt);
	c.setData(state);

	c.run();

	/**
	 * Print VM ram at end of execution
	 */
	printf("RAM at end of execution\n");
	printRam(data, size);
	
	//The state takes ownership of 'data' when it is passed to it, and destroying state should free data
	delete state;

	return 0;
}
