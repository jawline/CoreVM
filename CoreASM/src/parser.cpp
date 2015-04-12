#include "parser.h"
#include <stdio.h>

using namespace Assembler;

Parser::Parser() {
}

Parser::~Parser() {
}

void Parser::parse(char const* input, ByteBuffer& buffer) {
	printf("parsing %s\n", input);
}