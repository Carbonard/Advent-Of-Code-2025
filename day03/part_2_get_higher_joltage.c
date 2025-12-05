#include "../libft/libft.h"
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>

#define DIGITS 12

static __uint128_t	large_pow(__uint128_t base, size_t exp)
{
	__uint128_t	pow = 1;

	while (exp)
	{
		pow *= base;
		exp--;
	}
	return (pow);
}

static void	ui_putnbr(__uint128_t n)
{
	if (n)
	{
		ui_putnbr(n / 10);
		ft_putnbr_fd(n % 10, 1);
	}
}

static __uint128_t get_joltage(char *bank, size_t first, size_t last, size_t lenght, __uint128_t digit)
{
	size_t		i = first;
	size_t		next_first = 0;
	int			max = 0;

	while (i < last)
	{
		if (bank[i] - '0' > max)
		{
			max = bank[i] - '0';
			next_first = i;
		}
		i++;
	}
	if (last == lenght)
		return (max);
	return (max * large_pow(10, digit - 1) + get_joltage(bank, next_first + 1, last + 1, lenght, digit-1));
}

int main()
{
	__uint128_t	joltage;
	__uint128_t	total_joltage = 0;
	size_t		length;
	char		*bank;
	int			fd = open("input.txt", O_RDONLY);

	if (fd < 0)
		return (1);

	bank = get_next_line(fd);
	while (bank)
	{
		length = ft_strlen(bank);
		if (bank[length - 1] == '\n')
		{
			bank[length - 1] = 0;
			length--;
		}
		joltage = get_joltage(bank, 0, length - DIGITS + 1, length, DIGITS);
		ft_printf("Bank: %s\nJoltage: ", bank);
		ui_putnbr(joltage);
		ft_printf("\n");
		total_joltage += joltage;
		free(bank);
		bank = get_next_line(fd);
	}
	close(fd);
	
	ft_printf("The total output joltage is ");
	ui_putnbr(total_joltage);
	ft_printf("\n");
	return (0);
}
