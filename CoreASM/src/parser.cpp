#include "parser.h"
#include <stdio.h>

using namespace Assembler;

Parser::Parser() {}
Parser::~Parser() {}

bool Parser::parseLabel(char const*& input, ByteBuffer& buffer) {
	return false;
}

bool Parser::parseBlock(char const*& input, ByteBuffer& buffer) {
	Token next = _tokeniser.peekToken(input);
	
	if (next.tokenId() == ID) {
		if (!parseLabel(input, buffer)) {
			return false;
		}
	}

	return true;
}

bool Parser::parse(char const* input, ByteBuffer& buffer) {
	
	if (!parseBlock(input, buffer)) {
		return false;
	}

	Token next = _tokeniser.peekToken(input);
	
	if (next.tokenId() == INVALID_TOKEN) {
		return false;
	}
	
	if (next.tokenId() == TOKEN_EOF) {
		return true;
	}
	
	return parse(input, buffer);
}
