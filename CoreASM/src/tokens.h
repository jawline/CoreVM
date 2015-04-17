#ifndef _COREVM_PARSER_TOKENS_DEF_H_
#define _COREVM_PARSER_TOKENS_DEF_H_
#include <cstddef>
#include <string>

extern "C" {
	#include <regexpm/parser.h>
}

namespace Assembler {
	typedef enum {
		ID,
		NUM,
		JUMP,
		LOAD,
		GET,
		SET,
		MOVE,
		NOOP,
		COLON,
		ADD,
		SUBTRACT,
		MULTIPLY,
		DIVIDE,
		GREATER_THAN,
		LESS_THAN,
		TOKEN_EOF,
		INVALID_TOKEN
	} TOKEN_ID;

	class Token {
	private:
		TOKEN_ID _id;
		std::string _data;

	public:
		Token(TOKEN_ID id);
		Token(TOKEN_ID id, char const* input, size_t len);
		~Token();

		TOKEN_ID tokenId() const;
		char const* tokenString() const;
	};

	class Tokeniser {
	private:
		regex idRegex;
		regex intRegex;

		char const* skipWhite(char const* input);
	public:
		Tokeniser();
		~Tokeniser();
		Token peekToken(char const* input, size_t& len);
		Token peekToken(char const* input);
		Token nextToken(char const*& input);
	};
}

#endif //_COREVM_PARSER_TOKENS_DEF_H_
