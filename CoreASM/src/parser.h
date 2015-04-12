#ifndef _COREASM_PARSER_DEF_H_
#define _COREASM_PARSER_DEF_H_
#include "utils/bytebuffer.h"
#include "tokens.h"

namespace Assembler {
	class Parser {
	private:
		Tokeniser _tokeniser;
	public:
		Parser();
		~Parser();

		void parse(char const* input, ByteBuffer& buffer);
	};
}

#endif //_COREASM_PARSER_DEF_H_