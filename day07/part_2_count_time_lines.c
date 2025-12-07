#include "../libft/libft.h"
#include "../dynamic_arrays/src/ft_dynarray.h"
#include <fcntl.h>
#include <gmp.h>

static void error(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(1);
}

static void	clear_screen()
{
	write(STDOUT_FILENO, "\e[1;1H\e[2J", 11);
}

void put_ul(unsigned long n)
{
	if (n)
	{
		put_ul(n/10);
		ft_putchar_fd(n % 10 + '0', 1);
	}
}

int main()
{
	int					fd = open("input.txt", O_RDONLY);
	t_dyn_ptr			input;
	t_dyn_size_t_ptr	multiverse;
	size_t				time_lines = 0;

	if (fd < 0)
		error("File error");

	init_dyn_ptr(&input, 16);
	init_dyn_st_ptr(&multiverse, 16);
	while (add_ptr(&input, get_next_line(fd)))
	{
		add_st_ptr(&multiverse, calloc(ft_strlen(input.arr[input.index - 1]), sizeof(size_t)));
	}

	for (size_t i = 0; input.arr[0][i]; i++)
	{
		if (input.arr[0][i] == 'S')
		{
			if (input.arr[1][i] == '.')
			{
				input.arr[1][i] = '|';
				multiverse.arr[1][i] = 1;
			}
			else
				error("Unexpected file content");
		}
	}

	for (size_t i = 2; i < input.index; i++)
	{
		for (size_t j = 0; input.arr[i][j]; j++)
		{
			if (input.arr[i][j] == '^' && input.arr[i-1][j] == '|')
			{
				if (j > 0 && (input.arr[i][j-1] == '.' || input.arr[i][j-1] == '|'))
				{
					input.arr[i][j-1] = '|';
					multiverse.arr[i][j-1] += multiverse.arr[i-1][j];
				}
				if ((input.arr[i][j+1] == '.' || input.arr[i][j+1] == '|'))
				{
					input.arr[i][j+1] = '|';
					multiverse.arr[i][j+1] += multiverse.arr[i-1][j];
				}
			}
			else if ((input.arr[i][j] == '.' || input.arr[i][j] == '|') && input.arr[i-1][j] == '|')
			{
				input.arr[i][j] = '|';
				multiverse.arr[i][j] += multiverse.arr[i-1][j];
			}
		}
	}

	for (size_t i = 0; input.arr[input.index-1][i]; i++)
	{
		if (input.arr[input.index-1][i] == '|')
			time_lines += multiverse.arr[input.index-1][i];
	}

	printf("The tachyon beam is split a total of %lu times.\n", time_lines);
	return (0);
}
