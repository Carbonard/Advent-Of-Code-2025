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

void fix_overlaps(mpz_t min[], mpz_t max[], size_t m)
{
	for (size_t i = 0; i < m; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			if (mpz_cmp(min[i], min[j]) >= 0 && mpz_cmp(min[i], max[j]) <= 0 && i != j)
			{
				mpz_add_ui(min[i], max[j], 1);
			}
			if (mpz_cmp(max[i], min[j]) >= 0 && mpz_cmp(max[i], max[j]) <= 0 && i != j)
			{
				mpz_sub_ui(max[i], min[j], 1);
			}
		}
		if (mpz_cmp(min[i], max[i]) > 0)
		{
			mpz_set_ui(min[i], 1);
			mpz_set_ui(max[i], 0);
		}
	}
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
	mpz_t		available_ids;
	mpz_t		id_in_range;

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
	free(input);
	close(fd);

	fix_overlaps(min, max, m);

	mpz_init(id_in_range);
	mpz_init_set_d(available_ids, 0);
	for (size_t k = 0; k < m; k++)
	{
		mpz_sub(id_in_range, max[k], min[k]);
		mpz_add_ui(id_in_range, id_in_range, 1);
		gmp_printf("in range %Zu-%Zu are %Zu\n", min[k], max[k], id_in_range);
		mpz_add(available_ids, available_ids, id_in_range);
	}
	mpz_clear(id_in_range);

	for (size_t k = 0; k < m; k++)
	{
		mpz_clear(min[k]);
		mpz_clear(max[k]);
	}

	gmp_printf("\nThe fresh ingredient ID ranges consider a total of %Zd ingredient IDs to be fresh.\n", available_ids);
	mpz_clear(available_ids);
	return (0);
}
