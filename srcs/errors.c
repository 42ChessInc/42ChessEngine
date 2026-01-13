#include "libbitboard.h"

void	ft_err_handle(const char *str)
{
	fprintf(stderr, "%s", str);
	exit(1);
}

size_t	ft_count_args(const char *fen_str, const char *sep)
{
    char	*fen_copy;
    char	*tmp_token;
    size_t	i;

    if (!fen_str)
	return (-1);
    i = 0;
    fen_copy = strdup(fen_str);
    if (!fen_copy)
	return (-1);
    tmp_token = ft_strtok(fen_copy, sep);
    while (tmp_token)
    {
	i++;
	tmp_token = ft_strtok(NULL, sep);
    }
    free(fen_copy);
    fen_copy = NULL;
    return (i);
}

void	cleanup(char **args, char *fen_copy)
{
    if (fen_copy)
	free(fen_copy);
    fen_copy = NULL;
    free_args(args);
}

void	free_args(char **args)
{
    size_t	i;

    i = 0;
    if (args)
    {
	while (args[i])
	{
	    free(args[i]);
	    args[i] = NULL;
	    i++;
	}
	free(args);
	args = NULL;
    }
}
