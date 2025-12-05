#include "../libft/libft.h"
#include <fcntl.h>

int get_joltage(char *bank)
{
	size_t		i;
	char	first_digit = 0;
	char	second_digit = 0;

	i = 0;
	if (!bank || !bank[i])
		return (0);
	while (bank[i+1] && bank[i+1] != '\n')
	{
		if (first_digit < bank[i])
		{
			first_digit = bank[i];
			second_digit = bank[i+1];
		}
		else if (second_digit < bank[i])
			second_digit = bank[i];
		i++;
	}
	if (bank[i + 1] == '\n')
	{
		if (second_digit < bank[i])
			second_digit = bank[i];
	}
	return ((first_digit - '0') * 10 + (second_digit - '0'));
}

int main()
{
	int		joltage;
	int		total_joltage = 0;
	int		fd = open("input.txt", O_RDONLY);
	char	*bank;

	if (fd < 0)
		return (1);

	bank = get_next_line(fd);
	while (bank)
	{
		joltage = get_joltage(bank);
		ft_printf("Bank: %sJoltage: %d\n\n", bank, joltage);
		total_joltage += joltage;
		free(bank);
		bank = get_next_line(fd);
	}
	close(fd);
	
	ft_printf("The total output joltage is %d\n", total_joltage);
	return (0);
}
