/*
Basic lexer that lexes operators and numbers
Didn't have enough time to add symbols
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int len;
	char *data;
} Str;

#define STR(data) ((Str){sizeof(data), data})

typedef enum {
	TK_Add,
	TK_Sub,
	TK_Mul,
	TK_Div,
	TK_Symbol,
	TK_Number,
} TokenKind;

const char *TK_names[] = {
	"TK_Add", "TK_Sub", "TK_Mul", "TK_Div", "TK_Symbol", "TK_Number",
};

typedef struct {
	int kind;
	union {
		int valuei32;
	};
} Token;

typedef struct {
	Str str;
	int strIndex;
	Token *tokens;
	int tokenIndex;
} Lexer;

bool isSpace(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r'; }
bool isNum(char c) { return c >= '0' && c <= '9'; }
int numVal(char c) { return c - 48; }

char lexer_current(Lexer l) { return (l.strIndex < l.str.len) ? l.str.data[l.strIndex] : '\0'; }
char lexer_peek(Lexer l, int off)
{
	int i = l.strIndex + off;
	return (i < l.str.len) ? l.str.data[i] : '\0';
}
void lexer_skip_whitespace(Lexer *l)
{
	while (isSpace(lexer_current(*l))) {
		(*l).strIndex++;
	}
}

void lexer_push_token(Lexer *l, Token t) { l->tokens[(*l).tokenIndex++] = t; }

void lexer_lex(Lexer *lexer, Str input)
{
	Lexer l = *lexer;
	l.str = input;
	l.strIndex = 0;
	while (l.strIndex < l.str.len) {
		lexer_skip_whitespace(&l);
		switch (lexer_current(l)) {
		case '\0': l.strIndex++; break;
		case '+':
			lexer_push_token(&l, (Token){TK_Add});
			l.strIndex++;
			break;
		case '-':
			lexer_push_token(&l, (Token){TK_Sub});
			l.strIndex++;
			break;
		case '/':
			lexer_push_token(&l, (Token){TK_Div});
			l.strIndex++;
			break;
		case '*':
			lexer_push_token(&l, (Token){TK_Mul});
			l.strIndex++;
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': {
			int val = 0;
			while (isNum(lexer_current(l))) {
				val *= 10;
				val += numVal(lexer_current(l));
				l.strIndex++;
			}
			lexer_push_token(&l, (Token){TK_Number, .valuei32 = val});
		} break;
		default: {
			printf("Unexpected character %c", lexer_current(l));
			exit(1);
		}
		}
	}

	*lexer = l;
}

void main()
{
	Lexer l = {0};
	l.tokens = malloc(sizeof(Token) * 512);

	lexer_lex(&l, STR("10 + 20 "));
	for (int i = 0; i < l.tokenIndex; i++) {
		printf("%s %d\n", TK_names[l.tokens[i].kind], l.tokens[i].valuei32);
	}
}
