#include "vm/core.h"
#include "util/filehelper.h"

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
	c.run();

	delete[] data;

	return 0;
}