#include "../libft/libft.h"
#include "../dynamic_arrays/src/ft_dynarray.h"
#include <fcntl.h>

int main()
{
	t_dyn_ptr	rows;
	size_t		accessible;
	size_t		total_accessible = 0;
	size_t		adjaccent;
	int			fd = open("input.txt", O_RDONLY);

	if (fd < 0)
		return (1);
	init_dyn_ptr(&rows, 128);
	while (add_ptr(&rows, get_next_line(fd)));
	close(fd);
	
	for (size_t i = 0; i < rows.index; i++)
		ft_printf("%s", rows.arr[i]);

	do
	{
		accessible = 0;
		for (int i = 0; i < (int)rows.index; i++)
		{
			for (int j = 0; rows.arr[i][j] && rows.arr[i][j] != '\n'; j++)
			{
				adjaccent = 0;
				for (int r = -1; r < 2; r++)
				{
					for (int c = -1; c < 2; c++)
					{
						if (rows.arr[i][j] == '@'
							&& ((r != 0) || (c != 0))
							&& (i + r >= 0) && (i + r < (int)rows.index) && (j + c >= 0)
							&& (rows.arr[i+r][j + c] && rows.arr[i+r][j + c] != '\n')
							&& (rows.arr[i + r][j + c] == '@' || rows.arr[i + r][j + c] == 'x'))
							adjaccent++;
					}
				}
				if (rows.arr[i][j] == '@' && adjaccent < 4)
				{
					accessible++;
					rows.arr[i][j] = 'x';
				}
			}
		}
		total_accessible += accessible;
		for (int i = 0; i < (int)rows.index; i++)
		{
			for (int j = 0; rows.arr[i][j] && rows.arr[i][j] != '\n'; j++)
			{
				if (rows.arr[i][j] == 'x')
					rows.arr[i][j] = '.';
			}
		}
	} while (accessible > 0);

	ft_putchar_fd('\n', 1);
	for (size_t i = 0; i < rows.index; i++)
		ft_printf("%s", rows.arr[i]);
	free_dyn_ptr(&rows);
	ft_printf("\nThere are %d rolls of paper that can be accessed by a forklift (marked with x)\n", total_accessible);
	return (0);
}

