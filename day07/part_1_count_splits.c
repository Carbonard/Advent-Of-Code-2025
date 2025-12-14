#include "../libft/libft.h"
#include "../dynamic_arrays/src/ft_dynarray.h"
#include <fcntl.h>

static void error(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(1);
}

static void	clear_screen()
{
	write(STDOUT_FILENO, "\e[1;1H\e[2J", 11);
}

static void	print_input(t_dyn_ptr *input)
{
	clear_screen();
	for (size_t i = 0; i < input->index; i++)
	{
		ft_putstr_fd(input->arr[i], 1);
	}
	usleep(50000);
}

int main()
{
	int			fd = open("input.txt", O_RDONLY);
	t_dyn_ptr	input;
	size_t		splits = 0;

	if (fd < 0)
		error("File error");

	init_dyn_ptr(&input, 16);
	while (add_ptr(&input, get_next_line(fd)));
	close (fd);

	print_input(&input);
	for (size_t i = 0; input.arr[0][i]; i++)
	{
		if (input.arr[0][i] == 'S')
		{
			if (input.arr[1][i] == '.')
				input.arr[1][i] = '|';
			else
				error("Unexpected file content");
		}
	}
	print_input(&input);

	for (size_t i = 2; i < input.index; i++)
	{
		for (size_t j = 0; input.arr[i][j]; j++)
		{
			if (input.arr[i][j] == '^' && input.arr[i-1][j] == '|')
			{
				splits++;
				if (j > 0 && input.arr[i][j-1] == '.')
					input.arr[i][j-1] = '|';
				if (input.arr[i][j+1] == '.')
					input.arr[i][j+1] = '|';
			}
			else if (input.arr[i][j] == '.' && input.arr[i-1][j] == '|')
				input.arr[i][j] = '|';
		}
		print_input(&input);
	}
	printf("\nThe tachyon beam is split a total of %lu times.\n", splits);
	free_dyn_ptr(&input);
}
