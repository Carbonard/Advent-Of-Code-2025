#include "../libft/libft.h"
#include <fcntl.h>
#include <gmp.h>
#include <stdio.h>

static size_t	atoul(const char *nptr)
{
	size_t	num = 0;
	size_t	i = 0;

	if (!nptr)
		return (0);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + nptr[i] - '0';
		i++;
	}
	return (num);
}

static size_t	size_t_len(size_t n)
{
	size_t len = 0;

	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static size_t	big_pow(size_t base, size_t exp)
{
	size_t pow = 1;

	for (size_t i = 0; i < exp; i++)
	{
		pow *= base;
	}
	return (pow);
}

static void	sum_invalid_in_range(mpz_t sum, size_t min, size_t max)
{
	size_t	max_len;

	max_len = size_t_len(max);
	for (size_t mini_num_len = size_t_len(min) / 2; mini_num_len <= max_len / 2; mini_num_len++)
	{
		size_t start = 1;
		if (mini_num_len > 1)
			start = big_pow(10, mini_num_len - 1);
		for (size_t mini_num = start; mini_num < big_pow(10, mini_num_len); mini_num++)
		{
			size_t invalid_num = mini_num * big_pow(10, mini_num_len) + mini_num;
			if (invalid_num >= min && invalid_num <= max)
			{
				mpz_add_ui(sum, sum, invalid_num);
				printf("%lu, ", invalid_num);
			}
		}
	}
}

int main()
{
	size_t		fd = open("input.txt", O_RDONLY);
	char		*input;
	size_t		min;
	size_t		max;
	size_t		i = 0;
	mpz_t		sum_invalid_ids;

	input = get_next_line(fd);
	close(fd);
	if (!input)
	{
		ft_putendl_fd("Error reading file.", 2);
		return (1);
	}
	mpz_init_set_ui(sum_invalid_ids, 0);
	while (input[i])
	{
		min = atoul(input + i);
		if (min == 0)
		{
			ft_putendl_fd("Error reading number min", 2);
			return (1);
		}
		while (ft_isdigit(input[i]))
			i++;
		if (input[i] != '-')
		{
			ft_putendl_fd("Error finding '-'", 2);
			return (1);
		}
		else
			i++;
		max = atoul(input + i);
		if (max == 0)
		{
			ft_putendl_fd("Error reading number max", 2);
			return (1);
		}
		while (ft_isdigit(input[i]))
			i++;
		if (input[i] && input[i] != '\n' && input[i] != ',')
		{
			ft_putendl_fd("Error reading end of range", 2);
			return (1);
		}
		if (input[i])
			i++;
		ft_printf("\n\n%d-%d has the following invalid IDs:\n", min, max);
		sum_invalid_in_range(sum_invalid_ids, min, max);
	}
	free (input);
	gmp_printf("\n\nAdding up all the invalid IDs produces: %Zd\n", sum_invalid_ids);
	mpz_clear(sum_invalid_ids);
	return (0);
}


// size_t version (failed)

// static size_t	invalid_in_range(size_t min, size_t max)
// {
// 	size_t	invalid = 0;
// 	size_t	max_len;

// 	max_len = size_t_len(max);
// 	for (size_t mini_num_len = 1; mini_num_len <= max_len / 2; mini_num_len++)
// 	{
// 		for (size_t mini_num = ft_pow(10, mini_num_len - 1); mini_num < ft_pow(10, mini_num_len); mini_num++)
// 		{
// 			size_t invalid_num = 0;
// 			while (invalid_num < min)
// 			{
// 				invalid_num = invalid_num * ft_pow(10, mini_num_len) + mini_num;
// 			}
// 			while (invalid_num <= max)
// 			{
// 				invalid++;
// 				ft_printf("%d, ", invalid_num);
// 				invalid_num = invalid_num * ft_pow(10, mini_num_len) + mini_num;
// 			}
// 		}
// 	}
// 	return (invalid);
// }

// size_t main()
// {
// 	size_t		fd = open("input.txt", O_RDONLY);
// 	char		*input = get_next_line(fd);
// 	size_t		min;
// 	size_t		max;
// 	size_t		i = 0;
// 	size_t		sum_invalid_ids;
// 	size_t		new_sum_invalid;

// 	if (!input)
// 	{
// 		ft_putendl_fd("Error reading file.", 2);
// 		return (1);
// 	}
// 	while (input[i])
// 	{
// 		min = ft_atoul(input + i);
// 		if (min == 0)
// 		{
// 			ft_putendl_fd("Error reading number min", 2);
// 			return (1);
// 		}
// 		while (ft_isdigit(input[i]))
// 			i++;
// 		if (input[i] != '-')
// 		{
// 			ft_putendl_fd("Error finding '-'", 2);
// 			return (1);
// 		}
// 		else
// 			i++;
// 		max = ft_atoul(input + i);
// 		if (max == 0)
// 		{
// 			ft_putendl_fd("Error reading number max", 2);
// 			return (1);
// 		}
// 		while (ft_isdigit(input[i]))
// 			i++;
// 		if (input[i] && input[i] != '\n' && input[i] != ',')
// 		{
// 			ft_putendl_fd("Error reading end of range", 2);
// 			return (1);
// 		}
// 		if (input[i])
// 			i++;
// 		printf("\n\n%lu-%lu has the following invalid IDs:\n", min, max);
// 		sum_invalid_ids = sum_invalid_in_range(min, max);
// 	}
// 	printf("\n\nAdding up all the invalid IDs produces: %lu\n", sum_invalid_ids);
// 	return (0);
// }
