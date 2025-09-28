#include "libbitboard.h"

char	**ft_fen2arr(char *fen_str, const char *sep)
{
    char	**args;
    char	*fen_copy;
    char	*tmp_arg;
    size_t	count;
    size_t	i;

    if (!fen_str)
	return (NULL);

    // Count the number of arguments in string separeted by space
    count = ft_count_args(fen_str, sep);
    if (count <= 0)
	return (NULL);

    // Copy the original FEN string
    fen_copy = strdup(fen_str);
    if (!fen_copy)
	return (NULL);

    // Allocate space for the arguments
    args = (char **)calloc(count + 1, sizeof(char *));
    if (!args)
	return (cleanup(NULL, fen_copy), NULL);

    // Pass the FEN copy to strtok for it to modify it
    tmp_arg = ft_strtok(fen_copy, sep);
    if (!tmp_arg)
	return (cleanup(args, fen_copy), NULL);

    // Get the first argument and
    // set the strtok internal pointer in FEN copy
    i = 0;
    args[i] = strdup(tmp_arg);
    if (!args[i])
	return (cleanup(args, fen_copy), NULL);

    // Loop through the arguments and save them into char **args
    while (++i < count)
    {
	tmp_arg = ft_strtok(NULL, sep);
	if (!tmp_arg)
	    break ;
	args[i] = strdup(tmp_arg);
	if (!args[i])
	    return (cleanup(args, fen_copy), NULL);
    }
    free(fen_copy);
    return (args);
}
