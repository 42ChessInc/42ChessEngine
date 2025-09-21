#include "../include/libbitboard.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Wrong number of arguments.");
		exit(1);
	}
	printf("%s\n", argv[1]);
	return (0);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*internal_ptr;

	if (str != NULL)
		internal_ptr = str;
	if (internal_ptr == NULL)
		return (NULL);
	while (*internal_ptr != '\0' && strchr(internal_ptr, delim))
		internal_ptr++;
	
}
