#include "bytebuffer.h"
#include <string.h>

using namespace Assembler;

ByteBuffer::ByteBuffer() {
	buffer = new uint8_t[cDefaultBufferSize];
	bufferCurrentIter = 0;
	bufferCurrentSize = cDefaultBufferSize;
}

ByteBuffer::~ByteBuffer() {
	delete[] buffer;
}

void ByteBuffer::expandBuffer() {
	uint8_t* newBuffer = new uint8_t[bufferCurrentSize + cDefaultBufferSize];
	memcpy(newBuffer, buffer, bufferCurrentIter);
	delete[] buffer;
	buffer = newBuffer;
	bufferCurrentSize += cDefaultBufferSize;
}

void ByteBuffer::insert(uint8_t byte) {
	if (bufferCurrentIter + 1 >= bufferCurrentSize) {
		expandBuffer();
	}

	buffer[bufferCurrentIter++] = byte;
}

void ByteBuffer::insert(uint16_t word) {
	if (bufferCurrentIter + sizeof(uint16_t) >= bufferCurrentSize) {
		expandBuffer();
	}
	*((uint16_t*)&buffer[bufferCurrentIter]) = word;
	bufferCurrentIter += sizeof(uint16_t);
}

void ByteBuffer::insert(uint32_t num) {
	if (bufferCurrentIter + sizeof(uint32_t) >= bufferCurrentSize) {
		expandBuffer();
	}
	*((uint32_t*)&buffer[bufferCurrentIter]) = num;
	bufferCurrentIter += sizeof(uint32_t);
}