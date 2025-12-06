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

static char	*read_num(char *row, size_t i)
{
	size_t	j = 0;

	while (!ft_isdigit(row[i]))
		i++;
	while (ft_isdigit(row[i+j]))
		j++;
	return (ft_substr(row, i, j));
}

int main()
{
	char		*rows[ROWS];
	char		op;
	char		*str_num;
	mpz_t		num_1;
	mpz_t		num_2;
	size_t		i;
	mpz_t		grand_total;

	read_input(rows);

	mpz_init(num_1);
	mpz_init(num_2);
	mpz_init_set_ui(grand_total, 0);
	i = 0;
	while (any_digit(rows,i))
	{
		op = read_op(rows[0]);

		str_num = read_num(rows[1], i);
		mpz_set_str(num_1, str_num, 10);
		free(str_num);
		gmp_printf("%Zd",  num_1);

		for (size_t k = 2; k < ROWS; k++)
		{
			str_num = read_num(rows[k], i);
			mpz_set_str(num_2, str_num, 10);
			free(str_num);

			if (op == '+')
				mpz_add(num_1, num_1, num_2);
			else if (op == '*')
				mpz_mul(num_1, num_1, num_2);
			gmp_printf(" %c %Zd", op, num_2);
		}
		gmp_printf(" = %Zd\n", num_1);

		mpz_add(grand_total, grand_total, num_1);
		
		while (any_digit(rows, i))
			i++;
		i++;
	}
	mpz_clear(num_1);
	mpz_clear(num_2);
	for (size_t k = 0; k < ROWS; k++)
		free(rows[k]);
	gmp_printf("\nThe grand total is %Zd\n", grand_total);
	mpz_clear(grand_total);
	return (0);
}
