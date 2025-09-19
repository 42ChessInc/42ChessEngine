# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

typedef struct s_exp
{
	int	*explored;
	int	size;
}	t_exp;

// Driver functions
int		fib(int n);
int		ofib(int *explored, int n);
// Helper functions
int		isexplored(int *explored, int n);
int		init(t_exp **set, int size);
void	print_explored(int *explored, int size);
void	clean(t_exp **set);

int main(int argc, char **argv)
{
	t_exp	*set;
	int		target;
	int		result;

	if (argc != 2)
	{
		printf("Wrong number of arguments\n");
		return (-1);
	}
	// Recursive fibonacci sequence (raw)
	target = atoi(argv[1]);
	set = NULL;
	if (init(&set, target) < 0)
		return (-1);
	//result = fib(target);
	//printf("\nResult %d\n", result);
	// Recursive fibonacci sequence (improved searched states)
	result = ofib(set->explored, target);
	printf("\nResult %d\n", result);
	clean(&set);
	return (0);
}

int	init(t_exp **set, int size)
{
	*set = (t_exp *)malloc(sizeof(t_exp));
	if (!*set)
		return (-1);
	(*set)->explored = (int *)malloc(size * sizeof(int));
	if (!(*set)->explored)
		return (free(*set), -1);
	memset((*set)->explored, -1, size * sizeof(int));
	(*set)->size = size;
	(*set)->explored[0] = 1;
	(*set)->explored[1] = 1;
	return (0);
}

int	fib(int n)
{
	if (n == 1 || n == 2)
	{
		printf("f(%d) = 1 f(%d) = 1\n", 1, 2);
		return (1);
	}
	printf("f(%d) need f(%d), f(%d)\n", n, n - 1, n - 2);
	return (fib(n - 1) + fib(n - 2));
}

int	ofib(int *explored, int n)
{
	if (n <= 0)
		return (0);
	if (isexplored(explored, n))
	{
		printf("f(%d) = 1 f(%d) = 1\n", 1, 2);
		return (explored[n - 1]);
	}
	explored[n - 2] = ofib(explored, n - 1); 
	explored[n - 3] = ofib(explored, n - 2);
	printf("f(%d) need f(%d), f(%d)\n", n, n - 1, n - 2);
	return (explored[n - 2] + explored[n - 3]);
}

int	isexplored(int *explored, int n)
{
	if (explored[n - 1] > 0)
		return (1);
	return (0);
}

void	print_explored(int *explored, int size)
{
	int	i;

	i = 0;
	printf("Explored set: {");
	while (i < size)
	{
		if (i == size - 1)
			printf(" %d ", explored[i]);
		else
			printf(" %d ,", explored[i]);
		i++;
	}
	printf("}\n");
}

void	clean(t_exp **set)
{
	if (!*set)
		return ;
	if ((*set)->explored)
		free((*set)->explored);
	free(*set);
}
