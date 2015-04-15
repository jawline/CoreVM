#include "parser.h"
#include <CoreVM/instructions.h>
#include <CoreVM/registers.h>
#include <stdio.h>

using namespace Assembler;

Parser::Parser() {}
Parser::~Parser() {}

void Parser::handleLabelReference(char const* labelName, ByteBuffer& buffer) {
	size_t labelPosition = 0;
	if (!_labels.getLabel(labelName, labelPosition)) {
		_unresolvedLabels.push_back(pair<size_t, string>(buffer.current(), labelName));
	}
	buffer.insert((uint32_t)labelPosition);
}

bool Parser::parseLabel(char const*& input, ByteBuffer& buffer) {

	Token labelId = _tokeniser.nextToken(input);
	Token colon = _tokeniser.nextToken(input);

	if (colon.tokenId() != COLON) {
		printf("Expected colon at (%s) not (%s)\n", input, colon.tokenString());
		return false;
	}

	_labels.setLabel(labelId.tokenString(), buffer.current());

	printf("Set label %s at %li\n", labelId.tokenString(), buffer.current());
	resolveLabels(buffer);

	return true;
}

bool Parser::parseJump(char const*& input, ByteBuffer& buffer) {
	Token jump = _tokeniser.nextToken(input);
	Token location = _tokeniser.nextToken(input);

	if (location.tokenId() == ID) {
		buffer.insert((uint8_t) VM::JumpImmediate);
		handleLabelReference(location.tokenString(), buffer);
		printf("Jump to label %s\n", location.tokenString());
	} else {
		printf("Expected jump location (Adress or label) at %s, recieved %s\n", input, location.tokenString());
	}

	return true;
}

void Parser::resolveLabels(ByteBuffer& buffer) {
	size_t foundPos;
	size_t i = 0;

	while (i < _unresolvedLabels.size()) {
		if (_labels.getLabel(_unresolvedLabels[i].second, foundPos)) {
			buffer.insert((uint32_t) foundPos, _unresolvedLabels[i].first);
			_unresolvedLabels.erase(_unresolvedLabels.begin() + i);
		} else {
			i++;
		}
	}
}

bool Parser::parseNoOp(char const*& input, ByteBuffer& buffer) {
	Token noop = _tokeniser.nextToken(input);
	buffer.insert((uint8_t) VM::NoOp);
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
	} else if (next.tokenId() == NOOP) {
		if (!parseNoOp(input, buffer)) {
			return false;
		}
	}

	return true;
}

bool Parser::postParse(ByteBuffer& buffer) {
	if (_unresolvedLabels.size() != 0) {
		printf("Error: Unresolved labels exist\n");
		return false;
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
		return postParse(buffer);
	}
	
	return parse(input, buffer);
}
