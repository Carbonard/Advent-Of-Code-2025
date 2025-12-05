#include "../libft/libft.h"
#include <fcntl.h>
#include <gmp.h>
#include <stdio.h>
#include <errno.h>

#define RANGES 171

void error(char *str_error)
{
	ft_putendl_fd(str_error, 2);
	exit(errno);
}

int main()
{
	int			fd = open("input.txt", O_RDONLY);
	char		*input;
	char		*str_num;
	mpz_t		min[RANGES];
	mpz_t		max[RANGES];
	size_t		i;
	size_t		j;
	size_t		m = 0;
	size_t		avaiable_ingredients = 0;
	int			id_available;

	if (fd < 0)
	{
		ft_putendl_fd("Error reading file.", 2);
		return (1);
	}
	input = get_next_line(fd);
	while (input && input[0] != '\n')
	{
		if (m >= RANGES)
			error("Need more RANGES");

		i = 0;
		while (ft_isdigit(input[i]))
			i++;
		if (input[i] != '-')
			error("file format error");
		str_num = ft_substr(input, 0, i);
		if (!str_num)
			error("malloc error");
		mpz_init_set_str(min[m], str_num, 10);
		free(str_num);
		
		i++;
		
		j = 0;
		while (ft_isdigit(input[i + j]))
			j++;
		if (input[i + j] != '\n')
			error("file format error");
		str_num = ft_substr(input, i, i+j);
		if (!str_num)
			error("malloc error");
		mpz_init_set_str(max[m], str_num, 10);
		free(str_num);

		m++;
		free(input);
		input = get_next_line(fd);
	}

	mpz_t	id;
	mpz_init(id);
	free(input);
	input = get_next_line(fd);
	while (input && input[0] != '\n')
	{
		input[ft_strlen(input) - 1] = 0;
		mpz_set_str(id, input, 10);

		id_available = 0;
		for (size_t k = 0; k < m; k++)
		{
			if (mpz_cmp(id, min[k]) >= 0 && mpz_cmp(id, max[k]) <= 0)
			{
				id_available = 1;
				gmp_printf("Ingredient ID %Zd is fresh because it falls into range %Zd-%Zd\n", id, min[k], max[k]);
			}
		}
		if (id_available)
			avaiable_ingredients++;
		else
			gmp_printf("Ingredient ID %Zd is spoiled.\n", id);

		free(input);
		input = get_next_line(fd);
	}
	mpz_clear(id);
	close(fd);

	for (size_t k = 0; k < m; k++)
	{
		mpz_clear(min[k]);
		mpz_clear(max[k]);
	}

	printf("\n%lu of the available ingredient IDs are fresh.\n", avaiable_ingredients);
	return (0);
}
