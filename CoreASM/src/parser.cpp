#include "parser.h"
#include <stdio.h>

using namespace Assembler;

Parser::Parser() {}
Parser::~Parser() {}

bool Parser::parseLabel(char const*& input, ByteBuffer& buffer) {}
bool Parser::parseBlock(char const*& input, ByteBuffer& buffer) {}

bool Parser::parse(char const* input, ByteBuffer& buffer) {
	
	parseBlock(input, buffer);
	
	Token next = _tokeniser.peekToken(input);
	
	if (_tokeniser.tokenId() == INVALID_TOKEN) {
		return false;
	}
	
	if (_tokeniser.tokenId() == TOKEN_EOF) {
		return true;
	}
	
	return parse(input, buffer);
}
