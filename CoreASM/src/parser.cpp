#include "parser.h"
#include <CoreVM/instructions.h>
#include <CoreVM/registers.h>
#include <stdio.h>

using namespace Assembler;

Parser::Parser() {}
Parser::~Parser() {}

bool Parser::handleAddress(Token const& address, char const* input, ByteBuffer& buffer) {
	size_t labelPosition = 0;

	if (address.tokenId() == NUM) {
		labelPosition = address.tokenInt();
	} else if (address.tokenId() == ID) {
		if (!_labels.getLabel(address.tokenString(), labelPosition)) {
			_unresolvedLabels.push_back(pair<size_t, string>(buffer.current(), address.tokenString()));
		}
	} else {
		printf("Expected valid address (NUM or label ID) near %s and not %s\n", input, address.tokenString());
		return false;
	}

	buffer.insert((uint32_t)labelPosition);
	return true;
}

bool Parser::parseLabel(char const*& input, ByteBuffer& buffer) {
	Token labelId = _tokeniser.nextToken(input);
	Token colon = _tokeniser.nextToken(input);

	if (colon.tokenId() != COLON) {
		printf("Expected colon at (%s) not (%s)\n", input, colon.tokenString());
		return false;
	}

	_labels.setLabel(labelId.tokenString(), buffer.current());
	resolveLabels(buffer);
	return true;
}

bool Parser::parseInterrupt(char const*& input, ByteBuffer& buffer) {
	Token intToken = _tokeniser.nextToken(input);
	Token intNum = _tokeniser.nextToken(input);

	if (intNum.tokenId() != NUM) {
		printf("Expected interrupt number near %s not %s\n", input, intNum.tokenString());
		return false;
	}
	
	buffer.insert((uint8_t) VM::Interrupt);
	buffer.insert((uint8_t) intNum.tokenInt());
	return true;
}

bool Parser::parseConditionalJump(char const*& input, ByteBuffer& buffer) {
	Token jumpType = _tokeniser.nextToken(input);
	Token regToken = _tokeniser.nextToken(input);

	VM::RegisterID reg = VM::RegisterUtils::getRegisterId(regToken.tokenString());
	if (reg == VM::InvalidRegister) {
		printf("Register %s is not a valid register near %s\n", regToken.tokenString(), input);
	}

	Token comparedToken = _tokeniser.nextToken(input);
	VM::RegisterID comparedId = VM::RegisterUtils::getRegisterId(comparedToken.tokenString());
	bool immediateComparison = comparedId == VM::InvalidRegister;

	Token addressToken = _tokeniser.nextToken(input);
	VM::RegisterID addressId = VM::RegisterUtils::getRegisterId(addressToken.tokenString());
	bool immediateAddress = addressId == VM::InvalidRegister;

	switch (jumpType.tokenId()) {
		case JUMP_EQUALS:
			if (immediateComparison) {
				if (immediateAddress) {
					buffer.insert((uint8_t) VM::JumpEqualImmediateImmediate);
				} else {
					buffer.insert((uint8_t) VM::JumpEqualImmediateRegister);
				}
			} else {
				if (immediateAddress) {
					buffer.insert((uint8_t) VM::JumpEqualRegisterImmediate);
				} else {
					buffer.insert((uint8_t) VM::JumpEqualRegisterRegister);
				}
			}
			break;
		case JUMP_NOT_EQUALS:
			if (immediateComparison) {
				if (immediateAddress) {
					buffer.insert((uint8_t) VM::JumpNotEqualImmediateImmediate);
				} else {
					buffer.insert((uint8_t) VM::JumpNotEqualImmediateRegister);
				}
			} else {
				if (immediateAddress) {
					buffer.insert((uint8_t) VM::JumpNotEqualRegisterImmediate);
				} else {
					buffer.insert((uint8_t) VM::JumpNotEqualRegisterRegister);
				}
			}
			break;
		default:
			printf("Error, not expecting %s at %s\n", jumpType.tokenString(), input);
			return false;
	}

	buffer.insert((uint8_t) reg);

	if (immediateComparison) {
		if (!handleAddress(comparedToken, input, buffer)) {
			return false;
		}
	} else {
		buffer.insert((uint8_t) comparedId);
	}

	if (immediateAddress) {
		if (!handleAddress(addressToken, input, buffer)) {
			return false;
		}
	} else {
		buffer.insert((uint8_t) addressId);
	}

	return true;
}

bool Parser::parseDataByte(char const*& input, ByteBuffer& buffer) {
	//Discard the db
	_tokeniser.nextToken(input);

	Token numTk = _tokeniser.nextToken(input);
	if (numTk.tokenId() != NUM) {
		printf("Expected num near %s not %s\n", input, numTk.tokenString());
		return false;
	}

	int num = numTk.tokenInt();
	
	for (int i = 0; i < num; i++) {
		buffer.insert((uint8_t) 0);
	}

	return true;
}

bool Parser::parseMove(char const*& input, ByteBuffer& buffer) {
	Token move = _tokeniser.nextToken(input);
	Token dstName = _tokeniser.nextToken(input);

	VM::RegisterID dst = VM::RegisterUtils::getRegisterId(dstName.tokenString());
	if (dst == VM::InvalidRegister) {
		printf("Register %s is not a valid register near %s\n", dstName.tokenString(), input);
	}

	Token srcName = _tokeniser.nextToken(input);

	VM::RegisterID src = VM::RegisterUtils::getRegisterId(srcName.tokenString());
	if (src == VM::InvalidRegister) {
		printf("Register %s is not a valid register near %s\n", srcName.tokenString(), input);
		return false;
	}

	buffer.insert((uint8_t)  VM::Move);
	buffer.insert((uint8_t)  dst);
	buffer.insert((uint8_t)  src);

	return true;
}

bool Parser::parseMemoryOp(char const*& input, ByteBuffer& buffer) {
	
	Token memoryOp = _tokeniser.nextToken(input);
	Token regName = _tokeniser.nextToken(input);

	VM::RegisterID reg = VM::RegisterUtils::getRegisterId(regName.tokenString());
	if (reg == VM::InvalidRegister) {
		printf("Register %s is not a valid register near %s\n", regName.tokenString(), input);
	}

	Token addressToken = _tokeniser.nextToken(input);
	VM::RegisterID address = VM::RegisterUtils::getRegisterId(addressToken.tokenString());
	bool immediate = address == VM::InvalidRegister;

	switch (memoryOp.tokenId()) {
		case GET:
			buffer.insert((uint8_t) (immediate ? VM::GetMemoryInt : VM::GetMemoryIntRegister));
			break;
		case SET:
			buffer.insert((uint8_t) (immediate ? VM::SetMemoryInt : VM::SetMemoryIntRegister));
			break;
		default:
			printf("Expected GET or SET\n");
			return false;
	}

	buffer.insert((uint8_t) reg);

	if (immediate) {
		if (!handleAddress(addressToken, input, buffer)) {
			return false;
		}
	} else {
		buffer.insert((uint8_t) address);
	}
		
	return true;
}

bool Parser::parseLoad(char const*& input, ByteBuffer& buffer) {
	Token load = _tokeniser.nextToken(input);
	Token registerName = _tokeniser.nextToken(input);
	
	if (registerName.tokenId() != ID) {
		printf("Expected ID near %s and not %s\n", input, registerName.tokenString());
		return false;
	}
	
	VM::RegisterID id = VM::RegisterUtils::getRegisterId(registerName.tokenString());
	if (id == VM::InvalidRegister) {
		printf("Register %s is not a valid register near %s\n", registerName.tokenString(), input);
		return false;
	}
	
	Token value = _tokeniser.nextToken(input);
	
	buffer.insert((uint8_t)  VM::LoadImmediate);
	buffer.insert((uint8_t)  id);

	//Allows load to load either a label location or a number
	if (!handleAddress(value, input, buffer)) {
		return false;
	}
	
	return true;
}

bool Parser::parseJump(char const*& input, ByteBuffer& buffer) {
	Token jump = _tokeniser.nextToken(input);
	Token location = _tokeniser.nextToken(input);

	VM::RegisterID id = VM::RegisterUtils::getRegisterId(location.tokenString());
	bool immediate = id == VM::InvalidRegister;

	if (immediate) {
		buffer.insert((uint8_t) VM::JumpImmediate);
	} else {
		buffer.insert((uint8_t) VM::JumpRegister);
	}

	if (immediate) {
		if (!handleAddress(location, input, buffer)) {
			return false;
		}
	} else {
		buffer.insert((uint8_t) id);	
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
	//Discard the noOp token
	_tokeniser.nextToken(input);
	buffer.insert((uint8_t) VM::NoOp);
	return true;
}

bool Parser::parseBlock(char const*& input, ByteBuffer& buffer) {
	Token next = _tokeniser.peekToken(input);
	
	switch (next.tokenId()) {
		case NOOP:
			return parseNoOp(input, buffer);
		case ID:
			return parseLabel(input, buffer);
		case JUMP:
			return parseJump(input, buffer);
		case LOAD:
			return parseLoad(input, buffer);
		case MOVE:
			return parseMove(input, buffer);
		case DATA_BYTE:
			return parseDataByte(input, buffer);
		case INTERRUPT:
			return parseInterrupt(input, buffer);
		case GET:
		case SET:
			return parseMemoryOp(input, buffer);
		case GREATER_THAN:
		case LESS_THAN:
		case ADD:
		case SUBTRACT:
		case DIVIDE:
		case MULTIPLY:
			return parseArithmetic(input, buffer);
		case JUMP_EQUALS:
		case JUMP_NOT_EQUALS:
			return parseConditionalJump(input, buffer);
		default:
			printf("Expected instruction or label near %s and not %s", input, next.tokenString());
			return false;
	}

	//Note: Not reachable
	return false;
}

bool Parser::parseArithmetic(char const*& input, ByteBuffer& buffer) {
	Token instr = _tokeniser.nextToken(input);
	
	Token registerName = _tokeniser.nextToken(input);
	if (registerName.tokenId() != ID) {
		printf("Expected register ID near %s not %s\n", input, registerName.tokenString());
		return false;
	}

	VM::RegisterID id = VM::RegisterUtils::getRegisterId(registerName.tokenString());
	if (id == VM::InvalidRegister) {
		printf("Register %s is not a valid register near %s\n", registerName.tokenString(), input);
		return false;
	}

	Token value = _tokeniser.nextToken(input);
	if (value.tokenId() != NUM && value.tokenId() != ID) {
		printf("Expected NUM or ID near %s not %s\n", input, value.tokenString());
		return false;
	}

	//If value is a NUM then its an immediate value if value is an ID then it is a register name
	bool immediate = value.tokenId() == NUM;

	switch (instr.tokenId()) {
		case ADD:
			buffer.insert((uint8_t) (immediate ? VM::AddImmediate : VM::AddRegister));
			break;
		case SUBTRACT:
			buffer.insert((uint8_t) (immediate ? VM::SubtractImmediate : VM::SubtractRegister));
			break;
		case MULTIPLY:
			buffer.insert((uint8_t) (immediate ? VM::MultiplyImmediate : VM::MultiplyRegister));
			break;
		case DIVIDE:
			buffer.insert((uint8_t) (immediate ? VM::DivideImmediate : VM::DivideRegister));
			break;
		case GREATER_THAN:
			buffer.insert((uint8_t) (immediate ? VM::GreaterThanImmediate : VM::GreaterThanRegister));
			break;
		case LESS_THAN:
			buffer.insert((uint8_t) (immediate ? VM::LessThanImmediate : VM::LessThanRegister));
			break;
		default:
			printf("Expected arithmetic, not %s\n", instr.tokenString());
			return false;
	}

	buffer.insert((uint8_t) id);

	if (immediate) {
		buffer.insert((uint32_t) value.tokenInt());
	} else {
		VM::RegisterID valueId = VM::RegisterUtils::getRegisterId(value.tokenString());
		if (valueId == VM::InvalidRegister) {
			printf("Register %s is not a valid register near %s\n", value.tokenString(), input);
			return false;
		}
		buffer.insert((uint8_t) valueId);
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
		return postParse(buffer);
	}
	
	return parse(input, buffer);
}
