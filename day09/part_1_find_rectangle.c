#include "../libft/libft.h"
#include "../dynamic_arrays/src/ft_dynarray.h"
#include <fcntl.h>
#include <stdio.h>

typedef struct s_red_tiles
{
	size_t	x;
	size_t	y;
}	t_red_tiles;

#define ROWS 500
#define DEBUG 0

static void error(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(1);
}

static size_t	ul_diff(size_t a, size_t b)
{
	if (a > b)
		return (a - b);
	return (b - a);
}

int main()
{
	int				fd = open("input.txt", O_RDONLY);
	char			*input;
	t_red_tiles		*rows = malloc(ROWS * sizeof(t_red_tiles));
	size_t			i;
	size_t			j;
	size_t			current_area;
	size_t			max_area = 0;

	if (fd < 0)
		error("File error");

	i = 0;
	while ((input = get_next_line(fd)) && i < ROWS)
	{
		j = 0;
		rows[i].x = (size_t)ft_atoi(input);
		while (ft_isdigit(input[j]))
			j++;
		j++;
		rows[i].y = (size_t)ft_atoi(input + j);
		while (ft_isdigit(input[j]))
			j++;
		i++;
		free(input);
	}
	close (fd);

	for (size_t k = 0; k < i; k++)
	{
		for (size_t l = 250; l < 251; l++)
		{
			current_area = (ul_diff(rows[k].x, rows[l].x) + 1) * (ul_diff(rows[k].y, rows[l].y) + 1);
			if (DEBUG)
				printf("(%lu,%lu),(%lu,%lu), current %lu, max: %lu\n", rows[k].x, rows[k].y, rows[l].x, rows[l].y, current_area, max_area);
			if (current_area > max_area)
				max_area = current_area;
		}
	}

	printf("The largest rectangle you can make has area %lu.\n", max_area);

	free(rows);
	return(0);

}
