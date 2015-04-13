#include "parser.h"
#include <stdio.h>

using namespace Assembler;

Parser::Parser() {}
Parser::~Parser() {}

bool Parser::parseLabel(char const*& input, ByteBuffer& buffer) {

	Token labelId = _tokeniser.nextToken(input);
	Token colon = _tokeniser.nextToken(input);

	if (colon.tokenId() != COLON) {
		printf("Expected colon at (%s) not (%s)\n", input, colon.tokenString());
		return false;
	}

	_labels.setLabel(labelId.tokenString(), buffer.current());

	printf("Set label %s at %li\n", labelId.tokenString(), buffer.current());

	return true;
}

bool Parser::parseJump(char const*& input, ByteBuffer& buffer) {
	Token jump = _tokeniser.nextToken(input);
	Token location = _tokeniser.nextToken(input);

	if (location.tokenId() == ID) {
		printf("Jumping to %s\n", location.tokenString());
	} else {
		printf("Expected jump location (Adress or label) at %s, recieved %s\n", input, location.tokenString());
	}

	return true;
}

bool Parser::parseBlock(char const*& input, ByteBuffer& buffer) {
	Token next = _tokeniser.peekToken(input);
	
	if (next.tokenId() == ID) {
		if (!parseLabel(input, buffer)) {
			return false;
		}
	} else if (next.tokenId() == JUMP) {
		if (!parseJump(input, buffer)) {
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
		printf("Expected EOF or a block at %s\n", next.tokenString());
		return false;
	}
	
	if (next.tokenId() == TOKEN_EOF) {
		printf("Parse complete\n");
		return true;
	}
	
	return parse(input, buffer);
}
