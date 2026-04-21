#include "fen_tokenizer.h"
#include <string.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	if (argc != 2)
		return 1;

	fen_tokens_t	toks;
	int				i;
	
	memset(&toks, 0, sizeof(fen_tokens_t));
	fen_tokenize(argv[1], &toks);
	i = 0;
	while (toks.fields[i])
	{
		printf("FIELD %d -> %s\n", i + 1, toks.fields[i]);
		i++;
	}
	return 0;
}
