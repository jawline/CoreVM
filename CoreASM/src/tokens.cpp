#include "tokens.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>

extern "C" {
	#include <regexpm/match.h>
}

using namespace Assembler;

Token::Token(TOKEN_ID id) {
	_id = id;
	_data = "";
}

Token::Token(TOKEN_ID id, char const* input, size_t len) {
	_id = id;
	_data = std::string(input, len);
}

Token::~Token() {}

TOKEN_ID Token::tokenId() const {
	return _id;
}

char const* Token::tokenString() const {
	return _data.c_str();
}

Tokeniser::Tokeniser() {
	regexParse(&idRegex, "[a-zA-Z][a-zA-Z0-9_]*");
	regexParse(&intRegex, "-?[0-9]+");
}

Tokeniser::~Tokeniser() {
	regexFree(&idRegex);
	regexFree(&intRegex);
}

char const* Tokeniser::skipWhite(char const* input) {
  for (; *input && isspace(*input); input++) {}
  return input;
}

Token Tokeniser::nextToken(char const*& input) {
	input = skipWhite(input);
	size_t len;
	Token next = peekToken(input, len);
	input += len;
	return next;
}

Token Tokeniser::peekToken(char const* input) {
	input = skipWhite(input);
	size_t len;
	return peekToken(input, len);
}

Token Tokeniser::peekToken(char const* input, size_t& len) {
	Token result = Token(INVALID_TOKEN);
	input = skipWhite(input);

	if (*input == '\0') {
		result = Token(TOKEN_EOF);
		len = 0;
	} else if (strncmp(input, ":", 1) == 0) {
		result = Token(COLON, input, 1);
		len = 1;
	} else if (strncmp(input, "jmp", 3) == 0) {
		result = Token(JUMP, input, 3);
		len = 3;
	} else if (strncmp(input, "load", 4) == 0) {
		result = Token(LOAD, input, 4);
		len = 4;
	} else if (strncmp(input, "nop", 3) == 0) {
		result = Token(NOOP, input, 4);
		len = 3;
	} else if (strncmp(input, "add", 3) == 0) {
		result = Token(ADD, input, 3);
		len = 3;
	} else if (strncmp(input, "sub", 3) == 0) {
		result = Token(SUBTRACT, input, 3);
		len = 3;
	} else if (strncmp(input, "mul", 3) == 0) {
		result = Token(MULTIPLY, input, 3);
		len = 3;
	} else if (strncmp(input, "div", 3) == 0) {
		result = Token(DIVIDE, input, 3);
		len = 3;
	} else if (strncmp(input, "gt", 2) == 0) {
		result = Token(GREATER_THAN, input, 2);
		len = 2;
	} else if (strncmp(input, "lt", 2) == 0) {
		result = Token(LESS_THAN, input, 2);
		len = 2;
	} else if (strncmp(input, "set", 3) == 0) {
		result = Token(SET, input, 3);
		len = 3;
	} else if (strncmp(input, "get", 3) == 0) {
		result = Token(GET, input, 3);
		len = 3;
	} else if (strncmp(input, "mov", 3) == 0) {
		result = Token(MOVE, input, 3);
		len = 3;
	} else if (strncmp(input, "jeq", 3) == 0) {
		result = Token(JUMP_EQUALS, input, 3);
		len = 3;
	} else if (strncmp(input, "jne", 3) == 0) {
		result = Token(JUMP_NOT_EQUALS, input, 3);
		len = 3;
	} else if (strncmp(input, "int", 3) == 0) {
		result = Token(INTERRUPT, input, 3);
		len = 3;
	} else if (strncmp(input, "db", 2) == 0) {
		result = Token(DATA_BYTE, input, 2);
		len = 2;
	} else if ((len = nfaMatches(idRegex.start, input)) > 0) {
		result = Token(ID, input, len);
	} else if ((len = nfaMatches(intRegex.start, input)) > 0) {
		result = Token(NUM, input, len);
	}

	return result;
}
