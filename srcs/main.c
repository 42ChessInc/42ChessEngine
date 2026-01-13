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
	return (0);
}
