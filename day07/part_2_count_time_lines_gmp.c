#include "../libft/libft.h"
#include "../dynamic_arrays/src/ft_dynarray.h"
#include <fcntl.h>
#include <gmp.h>

static void error(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(1);
}

int main()
{
	int				fd = open("input.txt", O_RDONLY);
	t_dyn_ptr		input;
	t_dyn_ptr		multiverse;
	mpz_t			new_mpz;
	mpz_t			time_lines;

	if (fd < 0)
		error("File error");

	init_dyn_ptr(&input, 16);
	init_dyn_ptr(&multiverse, 16);
	while (add_ptr(&input, get_next_line(fd)))
	{
		add_ptr(&multiverse, malloc(ft_strlen(input.arr[input.index - 1]) * sizeof(mpz_t)));
		for (size_t k = 0; k < ft_strlen(input.arr[input.index - 1]); k++)
			mpz_init_set_ui(((mpz_t *)(multiverse.arr[multiverse.index-1]))[k], 0);
	}
	close (fd);

	for (size_t i = 0; input.arr[0][i]; i++)
	{
		if (input.arr[0][i] == 'S')
		{
			if (input.arr[1][i] == '.')
			{
				input.arr[1][i] = '|';
				mpz_set_ui(((mpz_t *)(multiverse.arr[1]))[i], 1);
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
					mpz_add(((mpz_t *)(multiverse.arr[i]))[j-1], ((mpz_t *)(multiverse.arr[i]))[j-1], ((mpz_t *)(multiverse.arr[i-1]))[j]);
				}
				if ((input.arr[i][j+1] == '.' || input.arr[i][j+1] == '|'))
				{
					input.arr[i][j+1] = '|';
					mpz_add(((mpz_t *)(multiverse.arr[i]))[j+1], ((mpz_t *)(multiverse.arr[i]))[j+1], ((mpz_t *)(multiverse.arr[i-1]))[j]);
				}
			}
			else if ((input.arr[i][j] == '.' || input.arr[i][j] == '|') && input.arr[i-1][j] == '|')
			{
				input.arr[i][j] = '|';
				mpz_add(((mpz_t *)(multiverse.arr[i]))[j], ((mpz_t *)(multiverse.arr[i]))[j], ((mpz_t *)(multiverse.arr[i-1]))[j]);
			}
		}
	}

	mpz_init_set_ui(time_lines, 0);
	for (size_t i = 0; input.arr[input.index-1][i]; i++)
	{
		if (input.arr[input.index-1][i] == '|'){
			mpz_add(time_lines, time_lines, ((mpz_t *)multiverse.arr[input.index-1])[i]);
		gmp_printf("%Zd\n", time_lines);}
	}

	for (size_t i = 0; i < input.index; i++)
	{
		for (size_t k = 0; k < ft_strlen(input.arr[input.index - 1]); k++)
			mpz_clear(((mpz_t *)(multiverse.arr[i]))[k]);
	}
	free_dyn_ptr(&input);
	free_dyn_ptr(&multiverse);
	gmp_printf("The tachyon beam is split a total of %Zd times.\n", time_lines);
	mpz_clear(time_lines);
}
