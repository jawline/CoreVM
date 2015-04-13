#ifndef _COREASM_PARSER_DEF_H_
#define _COREASM_PARSER_DEF_H_
#include "utils/bytebuffer.h"
#include "tokens.h"

namespace Assembler {
	class Parser {
	private:
		Tokeniser _tokeniser;
		bool parseLabel(char const*& input, ByteBuffer& buffer);
		bool parseBlock(char const*& input, ByteBuffer& buffer);

	public:
		Parser();
		~Parser();

		bool parse(char const* input, ByteBuffer& buffer);
	};
}

#endif //_COREASM_PARSER_DEF_H_
