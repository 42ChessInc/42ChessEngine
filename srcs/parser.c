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
    t_piece	piece_type;

    switch (c)
    {
	case 'P' : piece_type = W_PAWN; return (piece_type) ;
	case 'N' : piece_type = W_KNIGHT; return (piece_type) ;
	case 'B' : piece_type = W_BISHOP; return (piece_type) ;
	case 'R' : piece_type = W_ROOK; return (piece_type) ;
	case 'Q' : piece_type = W_QUEEN; return (piece_type) ;
	case 'K' : piece_type = W_KING; return (piece_type) ;
	case 'p' : piece_type = B_PAWN; return (piece_type) ;
	case 'n' : piece_type = B_KNIGHT; return (piece_type) ;
	case 'b' : piece_type = B_BISHOP; return (piece_type) ;
	case 'r' : piece_type = B_ROOK; return (piece_type) ;
	case 'q' : piece_type = B_QUEEN; return (piece_type) ;
	case 'k' : piece_type = B_KING; return (piece_type) ;
	default : return (EMPTY) ;
    }
}

char	lookup_piece2fen(t_piece piece_type)
{
    char	c;

    c = '\0';
    switch (piece_type)
    {
	case W_PAWN : c = 'P'; return (c) ;
	case W_KNIGHT : c = 'N'; return (c) ;
	case W_BISHOP : c = 'B'; return (c) ;
	case W_ROOK : c = 'R'; return (c) ;
	case W_QUEEN : c = 'Q'; return (c) ;
	case W_KING : c = 'K'; return (c) ;
	case B_PAWN : c = 'p'; return (c) ;
	case B_KNIGHT : c = 'n'; return (c) ;
	case B_BISHOP : c = 'b'; return (c) ;
	case B_ROOK : c = 'r'; return (c) ;
	case B_QUEEN : c = 'q'; return (c) ;
	case B_KING : c = 'k'; return (c) ;
	default : return (c) ;
    }
}
