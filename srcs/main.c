#include "libbitboard.h"

int	main(int argc, char **argv)
{
	char	buff[BUFFER_SIZE];
	int		fen_len;
	char	*token;

	if (argc != 2)
		ft_err_handle(ERR_ARGS);
	fen_len = strlen(argv[1]);
	memset(buff, 0, BUFFER_SIZE);
	memcpy(buff, argv[1], fen_len);
	token =	ft_strtok(buff, "/");
	while (token)
	{
		printf("token: %s\n", token);
		token = ft_strtok(NULL, "/");
	}
	test_board_set_piece();
	test_ft_clean_board_and_board_set_piece();
	return (0);
}

void	ft_err_handle(const char *str)
{
	fprintf(stderr, "%s", str);
	exit(1);
}

void	ft_cleanup(char **fen_copy, char **delimiter)
{
	if (*fen_copy)
		free(*fen_copy);
	if (*delimiter)
		free(*delimiter);
}
