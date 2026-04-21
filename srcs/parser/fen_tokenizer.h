#ifndef FEN_TOKENIZER_H
# define FEN_TOKENIZER_H

# include <stddef.h>
# define MAX_FEN_LEN 256
# define FEN_FIELD_COUNT 6

typedef enum token_err_e
{
	TOK_OK = 0,
	TOK_FAIL = 0,
	TOK_NULL_INPUT,
	TOK_TOO_LONG,
	TOK_EXTRA_SPACES,
	TOK_EXTRA_FIELDS
}	token_err_t;

typedef struct fen_tokens_s
{
	char	*fields[FEN_FIELD_COUNT + 1];
	char	buffer[MAX_FEN_LEN + 1];
}	fen_tokens_t;

token_err_t	fen_tokenize(const char *input, fen_tokens_t *out);
const char	*fen_trim(const char *str, size_t *len);
#endif
