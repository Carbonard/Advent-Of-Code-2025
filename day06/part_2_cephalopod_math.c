#include "../libft/libft.h"
#include <fcntl.h>
#include <gmp.h>
#include <stdio.h>
#include <errno.h>

#define ROWS 5

static void	read_input(char *rows[])
{
	int			fd = open("input.txt", O_RDONLY);

	if (fd < 0)
	{
		ft_putendl_fd("Error reading file.", 2);
		exit(1);
	}
	for (size_t k = 1; k < ROWS; k++)
	{
		rows[k] = get_next_line(fd);
	}
	rows[0] = get_next_line(fd);
	close (fd);
	for (size_t k = 0; k < ROWS; k++)
	{
		if (!rows[k])
		{
			for (size_t l = 0; l < ROWS; l++)
				free(rows[k]);
			ft_putendl_fd("Error reading file.", 2);
			exit(1);
		}
	}
}

static int	any_digit(char *rows[], size_t i)
{
	int any_digit = 0;

	for (size_t k = 1; k < ROWS; k++)
	{
		any_digit += ft_isdigit(rows[k][i]);
	}
	return (any_digit);
}

static char	read_op(char *operations)
{
	static size_t	i;

	while(operations[i] && operations[i] != '+' && operations[i] != '*')
		i++;
	i++;
	return (operations[i-1]);
}

static size_t	read_num(char *rows[], size_t i)
{
	size_t	num = 0;
	size_t	pow = 0;

	for (int k = 1; k < ROWS; k++)
	{
		if (ft_isdigit(rows[k][i]))
		{
			if (!pow)
				pow = 1;
			num = num*pow + (rows[k][i] - '0');
			pow = 1;
		}
		pow *= 10;
	}
	return (num);
}

int main()
{
	char		*rows[ROWS];
	char		op;
	size_t		num;
	mpz_t		big_num;
	size_t		i;
	mpz_t		grand_total;

	read_input(rows);

	mpz_init(big_num);
	mpz_init_set_ui(grand_total, 0);
	i = 0;
	while (rows[1][i])
	{
		op = read_op(rows[0]);

		num = read_num(rows, i);
		mpz_set_ui(big_num, num);
		gmp_printf("%Zd", big_num);

		i++;
		while (any_digit(rows, i))
		{
			num = read_num(rows, i);
			if (op == '+')
				mpz_add_ui(big_num, big_num, num);
			else if (op == '*')
				mpz_mul_ui(big_num, big_num, num);
			printf(" %c %lu", op, num);
			i++;
		}
		gmp_printf(" = %Zd\n", big_num);
		mpz_add(grand_total, grand_total, big_num);
		i++;
	}
	gmp_printf("\nThe grand total is %Zd\n", grand_total);
	for (size_t k = 0; k < 5; k++)
	{
		free(rows[k]);
	}
	mpz_clear(big_num);
	mpz_clear(grand_total);
	return (0);
}
