#include "../libft/libft.h"
#include "../dynamic_arrays/src/ft_dynarray.h"
#include <fcntl.h>
#include <stdio.h>
#include <gmp.h>

typedef struct s_red_tiles
{
	size_t	x;
	size_t	y;
}	t_red_tiles;

#define ROWS 500
#define SHOW_MAP 0
#define DEBUG 0

static void error(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(1);
}

size_t	ul_diff(size_t a, size_t b)
{
	if (a > b)
		return (a - b);
	return (b - a);
}

size_t	ul_min(size_t a, size_t b)
{
	if (a > b)
		return (b);
	return (a);
}

size_t	ul_max(size_t a, size_t b)
{
	if (a > b)
		return (a);
	return (b);
}

int is_in_h_edge(t_red_tiles *red_tiles, size_t k, size_t x, size_t y, size_t size)
{
	if (x == red_tiles[k].x
		&& y < ul_max(red_tiles[k].y, red_tiles[(k+1)%size].y)
		&& y >= ul_min(red_tiles[k].y, red_tiles[(k+1)%size].y))
		return (1);
	return (0);
}

int is_inside(size_t y, size_t x, t_red_tiles *red_tiles, size_t size)
{
	size_t walls = 0;

	for (size_t k = 0; k < size; k++)
	{
		if (y == red_tiles[k].y && y == red_tiles[(k+1)%size].y  && (x >= ul_min(red_tiles[k].x, red_tiles[(k+1)%size].x) && x <= ul_max(red_tiles[k].x, red_tiles[(k+1)%size].x)))
			return (1);
		if (x == red_tiles[k].x && x == red_tiles[(k+1)%size].x  && (y >= ul_min(red_tiles[k].y, red_tiles[(k+1)%size].y) && y <= ul_max(red_tiles[k].y, red_tiles[(k+1)%size].y)))
			return (1);
	}

	for (size_t i = 0; i < x; i++)
	{
		for (size_t k = 0; k < size; k++)
		{
			if (red_tiles[k].x == red_tiles[(k+1)%size].x && is_in_h_edge(red_tiles, k, i, y, size))
			{
				walls++;
			}
		}
	}
	return(walls%2);
}

int is_in_range(size_t n, size_t a, size_t b)
{
	if (n>a && n<b)
		return (1);
	return(0);
}

int valid_sqr(t_red_tiles  *red_tiles, size_t size, size_t k, size_t l)
{
	// Check if any edge intersect the square
	for (size_t i = 0; i < size; i++)
	{
		if(red_tiles[i].x == red_tiles[(i+1)%size].x
			&& is_in_range(red_tiles[i].x, ul_min(red_tiles[k].x, red_tiles[l].x), ul_max(red_tiles[k].x, red_tiles[l].x))
			&& !(ul_max(red_tiles[i].y, red_tiles[(i+1)%size].y) <= ul_min(red_tiles[k].y, red_tiles[l].y)
				||ul_min(red_tiles[i].y, red_tiles[(i+1)%size].y) >= ul_max(red_tiles[k].y, red_tiles[l].y)))
			return (0);
		if(red_tiles[i].y == red_tiles[(i+1)%size].y
			&& is_in_range(red_tiles[i].y, ul_min(red_tiles[k].y, red_tiles[l].y), ul_max(red_tiles[k].y, red_tiles[l].y))
			&& !(ul_max(red_tiles[i].x, red_tiles[(i+1)%size].x) <= ul_min(red_tiles[k].x, red_tiles[l].x)
				||ul_min(red_tiles[i].x, red_tiles[(i+1)%size].x) >= ul_max(red_tiles[k].x, red_tiles[l].x)))
			return (0);
	}
	
	// Check if an inner point (and hence every point) of the square is inside the valid region
	size_t x = (red_tiles[k].x + red_tiles[l].x)/2;
	size_t y = (red_tiles[k].y + red_tiles[l].y)/2;
	return(is_inside(y, x, red_tiles, size));
}

int checked(size_t k, size_t l, size_t *max_win_k, size_t *max_win_l, size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		if (k == max_win_k[i] && l == max_win_l[i])
			return (1);
	}
	return (0);
}

t_red_tiles *read_input(size_t *n_red_tiles, size_t *max_x, size_t *max_y)
{
	t_red_tiles		*red_tiles = malloc(ROWS * sizeof(t_red_tiles)); // To save input

	int				fd = open("input.txt", O_RDONLY);
	char			*input;
	size_t			j;
	if (fd < 0)
		error("File error");

	*n_red_tiles = 0;
	while ((input = get_next_line(fd)) && *n_red_tiles < ROWS)
	{
		j = 0;
		red_tiles[*n_red_tiles].x = (size_t)ft_atoi(input);
		while (ft_isdigit(input[j]))
			j++;
		j++;
		red_tiles[*n_red_tiles].y = (size_t)ft_atoi(input + j);
		while (ft_isdigit(input[j]))
			j++;
		if (red_tiles[*n_red_tiles].x > *max_x)
			*max_x = red_tiles[*n_red_tiles].x;
		if (red_tiles[*n_red_tiles].y > *max_y)
			*max_y = red_tiles[*n_red_tiles].y;
		(*n_red_tiles)++;
		free(input);
	}
	close (fd);
	return (red_tiles);
}

size_t	get_area(t_red_tiles *red_tiles, size_t n_red_tiles)
{
	size_t			current_area;
	size_t			max_area = 0;
	size_t			last_max_area = 4730114840; // Based on the area found in part_1
	size_t			max_k=0;
	size_t			max_l=0;
	size_t			max_win_k[1000];
	size_t			max_win_l[1000];
	size_t			n_checked=0;

	while (last_max_area > 1)
	{
		for (size_t k = 0; k < n_red_tiles; k++)
		{
			for (size_t l = k; l < n_red_tiles; l++)
			{
				// Calculate area of the current rectangle
				current_area = (ul_diff(red_tiles[k].x, red_tiles[l].x) + 1) * (ul_diff(red_tiles[k].y, red_tiles[l].y) + 1);
				//	current < big but invalid sqr or current equal to area of invalid but a different rectangle
				if ((current_area < last_max_area || (current_area == last_max_area && !checked(k, l, max_win_k, max_win_l, n_checked))) && current_area > max_area)
				{
					max_area = current_area;
					max_k = k;
					max_l = l;
				}
			}
		}
		if (valid_sqr(red_tiles, n_red_tiles, max_k, max_l))
		{
			if (DEBUG)
				printf("%lu, %lu, from(%lu,%lu) to(%lu,%lu)\n", max_k, max_l, red_tiles[max_k].x, red_tiles[max_k].y, red_tiles[max_l].x, red_tiles[max_l].y);
			break;
		}
		if (last_max_area != max_area)
		{
			n_checked = 0;
		}
		last_max_area = max_area;
		max_area = 0;
		max_win_k[n_checked]= max_k;
		max_win_l[n_checked]= max_l;
		n_checked++;
		if (DEBUG)
			printf("Invalid rectangle's area: %lu\n", last_max_area);
	}
	return (max_area);
}

int main()
{
	t_red_tiles		*red_tiles; // To save input
	size_t			n_red_tiles; // length of input
	size_t			max_x = 0;
	size_t			max_y = 0;

	red_tiles = read_input(&n_red_tiles, &max_x, &max_y);

	if (SHOW_MAP)
	{
		for (size_t i = 0; i < max_y+2; i++)
		{
			printf("%3lu ", i);
			for (size_t j = 0; j < max_x+3; j++)
			{
				if (is_inside(i, j, red_tiles, n_red_tiles))
					putchar('x');
				else
					putchar('.');
			}
			putchar('\n');
		}
	}

	size_t max_area = get_area(red_tiles, n_red_tiles);
	printf("The largest rectangle you can make has area %lu.\n", max_area);

	free(red_tiles);
	return(0);

}
