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

	VM::Core c;
	c.setData(data, size);

	/**
	 * Print VM ram at start of execution
	 */
	printf("RAM at start of execution\n");
	printRam(data, size);

	c.run();

	/**
	 * Print VM ram at end of execution
	 */
	printf("RAM at end of execution\n");
	printRam(data, size);
	delete[] data;

	return 0;
}