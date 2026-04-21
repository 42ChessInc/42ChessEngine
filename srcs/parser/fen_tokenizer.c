#include "fen_tokenizer.h"
#include <ctype.h>
#include <string.h>

/*
* @brief: Trim spaces from start and end of a string
*
* @param: str
* @param: len
*
* @return: const char pointer to offseted start
*
* */
const char	*fen_trim(const char *str, size_t *len)
{
	const char	*start;
	const char	*end;

	if (!str)
		return NULL;
	start = str;
	while (*start && isspace((unsigned char)*start))
		start++;
	end = start + strlen(start) - 1;
	while (end > start && isspace((unsigned char)*end))
		end--;
	*len = (end - start) + 1;
	return start;
}

token_err_t	fen_tokenize(const char *input, fen_tokens_t *out)
{
	const char	*trimmed;
	size_t		len;
	char		*p;
	int			idx;

	if (!input || !out)
		return (TOK_NULL_INPUT);
	trimmed = fen_trim(input, &len);
	if (len == 0)
		return (TOK_NULL_INPUT);
	if (len > MAX_FEN_LEN)
		return (TOK_TOO_LONG);

	memcpy(out->buffer, trimmed, len);
	out->buffer[len] = '\0';
	idx = 0;
	out->fields[idx++] = out->buffer;
	p = out->buffer;
	while (*p)
	{
		if (*p == ' ')
		{
			*p = '\0';
			if (*(p + 1) == 91 || (*(p + 1) > 72 && *(p + 1) < 78))
				return (TOK_EXTRA_SPACES);
			if (idx >= FEN_FIELD_COUNT)
				return (TOK_EXTRA_FIELDS);
			out->fields[idx++] = p + 1;
		}
		p++;
	}
	if (idx != FEN_FIELD_COUNT)
		return TOK_FAIL;
	return (TOK_OK);
}
