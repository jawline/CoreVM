#include "filehelper.h"
#include <stdio.h>

bool FileHelper::readFileToMemory(char const* filename, uint8_t*& resultDest, unsigned long& sizeDest) {
	FILE* fin = fopen(filename, "rb");

	if (!fin) {
		printf("Could not open file %s\n", filename);
		return false;
	}

	fseek(fin, 0, SEEK_END);
	unsigned long size = ftell(fin);
	fseek(fin, 0, SEEK_SET);

	uint8_t* buffer = new uint8_t[size];
	if (fread(buffer, size, 1, fin) != 1) {
		//Clear the buffer and return 0 if the load fails
		printf("Failed to read the file %s into memory\n", filename);
		delete[] buffer;
		fclose(fin);
		return false;
	}

	fclose(fin);
	resultDest = buffer;
	sizeDest = size;
	return true;
}