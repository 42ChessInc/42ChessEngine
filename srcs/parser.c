#include "libbitboard.h"

char	**ft_fen2arr( const char *fen_str, const char *sep)
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
    // set the strtok internal pointer to FEN copy
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

int	fen_to_board(const char *fen_str, t_board *b)
{
    char	**args;
    char	*p;
    int		base_sq;
    int		rank;
    int		file;
    int		empty;
    t_piece	piece_type;

    if (!fen_str || !b)
    {
	fprintf(stderr, "%s\n", "Not expected NULL value.");
	return (-1);
    }
    args = ft_fen2arr(fen_str, " ");
    if (!args || !*args)
    {
	fprintf(stderr, "%s\n", "Failed to parser FEN.");
	return (-1);
    }
    p = *args;
    ft_clean_board(b); // Reset board
    rank = 7;
    while (rank >= 0) 
    {
	file = 0;
	base_sq = rank * 8;
	while (file < 8)
	{
	    if (*p == '\0')
	    {
		fprintf(stderr, "%s\n", "FEN too short.");
		cleanup(args, NULL);
		return (-1);
	    }
	    if (*p == '/')
	    {
		p++; // Go to next character in FEN string
		break ; // Go to next rank
	    }
	    if (*p <= '8' && *p >= '1')
	    {
		empty = *p - '0';
		if (empty > 8)
		{
		    fprintf(stderr, "%s\n", "Invalid FEN.");
		    cleanup(args, NULL);
		    return (-1);
		}
		file += empty; // Skip empty files
		p++; // Go to next character in FEN (can only be a letter or '/')
	    }
	    else
	    {
		piece_type = lookup_fen2piece(*p);
		if (piece_type == EMPTY)
		{
		    fprintf(stderr, "Invalid piece in FEN: '%c'\n", *p);
		    cleanup(args, NULL);
		    return (-1);
		}
		board_set_piece(b, base_sq + file, piece_type);
		file++;
		p++;
	    }
	}
	if (file != 8)
	{
	    fprintf(stderr, "Invalid FEN: rank %d has %d squares (expected 8)\n", 8 - rank, file);
	    cleanup(args, NULL);
	    return (-1);
	}
	rank--;
    }
    return (0);
}

t_piece	lookup_fen2piece(char c)
{
    switch (c)
    {
	case 'P' : return (W_PAWN) ;
	case 'N' : return (W_KNIGHT) ;
	case 'B' : return (W_BISHOP) ;
	case 'R' : return (W_ROOK) ;
	case 'Q' : return (W_QUEEN) ;
	case 'K' : return (W_KING) ;
	case 'p' : return (B_PAWN) ;
	case 'n' : return (B_KNIGHT) ;
	case 'b' : return (B_BISHOP) ;
	case 'r' : return (B_ROOK) ;
	case 'q' : return (B_QUEEN) ;
	case 'k' : return (B_KING) ;
	default : return (EMPTY) ;
    }
}

char	lookup_piece2fen(t_piece piece_type)
{
    char	c;

    c = '\0';
    switch (piece_type)
    {
	case W_PAWN : return ('P');
	case W_KNIGHT : return ('N');
	case W_BISHOP : return ('B');
	case W_ROOK : return ('R');
	case W_QUEEN : return ('Q');
	case W_KING : return ('K');
	case B_PAWN : return ('p');
	case B_KNIGHT : return ('n');
	case B_BISHOP : return ('b');
	case B_ROOK : return ('r');
	case B_QUEEN : return ('q');
	case B_KING : return ('k');
	default : return (NULL) ;
    }
}
