#ifndef _COREASM_PARSER_DEF_H_
#define _COREASM_PARSER_DEF_H_
#include "utils/bytebuffer.h"
#include "labeltable.h"
#include "tokens.h"
#include <string>
#include <vector>

using namespace std;

namespace Assembler {
	class Parser {
	private:
		vector<pair<size_t, string>> _unresolvedLabels;
		Tokeniser _tokeniser;
		LabelTable _labels;

		void resolveLabels(ByteBuffer& buffer);

		bool parseLabel(char const*& input, ByteBuffer& buffer);
		bool parseBlock(char const*& input, ByteBuffer& buffer);
		bool parseNoOp(char const*& input, ByteBuffer& buffer);
		bool parseJump(char const*& input, ByteBuffer& buffer);
		bool postParse(ByteBuffer& buffer);

	public:
		Parser();
		~Parser();

		bool parse(char const* input, ByteBuffer& buffer);
	};
}

#endif //_COREASM_PARSER_DEF_H_
