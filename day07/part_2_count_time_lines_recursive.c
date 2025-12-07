#include "../libft/libft.h"
#include "../dynamic_arrays/src/ft_dynarray.h"
#include <fcntl.h>

static void error(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(1);
}

// static void	clear_screen()
// {
// 	write(STDOUT_FILENO, "\e[1;1H\e[2J", 11);
// }

// static void	print_input(t_dyn_ptr *input)
// {
// 	clear_screen();
// 	for (size_t i = 0; i < input->index; i++)
// 	{
// 		ft_putstr_fd(input->arr[i], 1);
// 	}
// 	// usleep(30000);
// }

static size_t split_time_line(t_dyn_ptr *input, size_t i, size_t j);

static size_t follow_time_line(t_dyn_ptr *input, size_t i)
{
	size_t	cnt = 0;

	if (i == input->index)
	{
		// print_input(input);
		return (1);
	}

	for (size_t j = 0; input->arr[i][j]; j++)
	{
		if (input->arr[i][j] == '^' && input->arr[i-1][j] == '|')
			cnt += (split_time_line(input, i, j));
		else if (input->arr[i][j] == '.' && (input->arr[i-1][j] == '|' || input->arr[i-1][j] == 'S'))
		{
			input->arr[i][j] = '|';
			cnt +=follow_time_line(input, i+1);
			input->arr[i][j] = '.';
		}
	}
	if (cnt == 0)
		return (follow_time_line(input, i+1));
	return (cnt);
}

static size_t split_time_line(t_dyn_ptr *input, size_t i, size_t j)
{
	size_t	cnt = 0;

	if (j > 0 && input->arr[i][j-1] == '.')
	{
		input->arr[i][j-1] = '|';
		cnt += follow_time_line(input, i+1);
		input->arr[i][j-1] = '.';
	}
	if (input->arr[i][j+1] == '.')
	{
		input->arr[i][j+1] = '|';
		cnt += follow_time_line(input, i+1);
		input->arr[i][j+1] = '.';
	}
	return (cnt);
}

int main()
{
	int			fd = open("input.txt", O_RDONLY);
	t_dyn_ptr	input;
	size_t		time_lines = 0;

	if (fd < 0)
		error("File error");

	init_dyn_ptr(&input, 16);
	while (add_ptr(&input, get_next_line(fd)));

	// print_input(&input);
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

	// for (size_t i = 2; i < input.index && !time_lines; i++)
	// {
	// 	for (size_t j = 0; input.arr[i][j]; j++)
	// 	{
	// 		if (input.arr[i][j] == '.' && input.arr[i-1][j] == '|')
	// 			input.arr[i][j] = '|';
	// 		else if (input.arr[i][j] == '^')
	// 			time_lines = split_time_lines(&input, i, j);
	// 	}
	// }
	time_lines = follow_time_line(&input, 1);
	// for (size_t i = 2; i < input.index; i++)
	// {
	// 	for (size_t j = 0; input.arr[i][j]; j++)
	// 	{
	// 		if (input.arr[i][j] == '^' && input.arr[i-1][j] == '|')
	// 		{
	// 			splits++;
	// 			if (j > 0 && input.arr[i][j-1] == '.')
	// 				input.arr[i][j-1] = '|';
	// 			if (input.arr[i][j+1] == '.')
	// 				input.arr[i][j+1] = '|';
	// 		}
	// 		else if (input.arr[i][j] == '.' && input.arr[i-1][j] == '|')
	// 			input.arr[i][j] = '|';
	// 	}
	// }
	printf("\nThe tachyon beam is split a total of %lu times.\n", time_lines);
	free_dyn_ptr(&input);
}
