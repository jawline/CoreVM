#ifndef _COREASM_PARSER_DEF_H_
#define _COREASM_PARSER_DEF_H_
#include <regexpm/parser.h>
#include "utils/bytebuffer.h"

namespace Assembler {
	class Parser {
	private:
		regex idRegex;
		regex intRegex;

	public:
		Parser();
		~Parser();

		void parse(char const* input, ByteBuffer& buffer);
	};
}

#endif //_COREASM_PARSER_DEF_H_