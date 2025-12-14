#include "../libft/libft.h"
#include "../dynamic_arrays/src/ft_dynarray.h"
#include <fcntl.h>
#include <stdio.h>
#include <gmp.h>

typedef struct s_junction_box
{
	int	x;
	int	y;
	int	z;
	size_t	circuit;
}	t_junction_box;

#define BOXES 1000
#define PAIRS 1000
#define DEBUG 0

static void error(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(1);
}

void	join_circuits(size_t c_1, size_t c_2, t_junction_box *j_boxes, size_t size, t_dyn_int *circuits)
{
	if (c_1 > c_2)
	{
		join_circuits(c_2, c_1, j_boxes, size, circuits);
		return;
	}
	for (size_t i = 0; i < size; i++)
	{
		if (j_boxes[i].circuit == c_2)
			j_boxes[i].circuit = c_1;
	}
	circuits->arr[c_1] += circuits->arr[c_2];
	circuits->arr[c_2] = 0;
}

void	connect(t_junction_box *j_boxes, size_t i, size_t j, size_t size, t_dyn_int *circuits)
{
	if (j_boxes[i].circuit == j_boxes[j].circuit && j_boxes[i].circuit != BOXES)
		return;
	if (j_boxes[i].circuit == BOXES && j_boxes[j].circuit != BOXES)
	{
		j_boxes[i].circuit = j_boxes[j].circuit;
		circuits->arr[j_boxes[j].circuit]++;
	}
	else if (j_boxes[i].circuit != BOXES && j_boxes[j].circuit == BOXES)
	{
		j_boxes[j].circuit = j_boxes[i].circuit;
		circuits->arr[j_boxes[i].circuit]++;
	}
	else if (j_boxes[i].circuit == BOXES && j_boxes[j].circuit == BOXES)
	{
		j_boxes[i].circuit = circuits->index;
		j_boxes[j].circuit = circuits->index;
		add_int(circuits, 2);
	}
	else if (j_boxes[i].circuit != BOXES && j_boxes[j].circuit != BOXES)
		join_circuits(j_boxes[i].circuit, j_boxes[j].circuit, j_boxes, size, circuits);
}

void print_uint(__uint128_t n)
{
	if (n)
	{
		print_uint(n/10);
		putchar(n % 10 + '0');
	}
}

__uint128_t	dist(t_junction_box *box_1, t_junction_box *box_2)
{
	__uint128_t dist;

	dist = (__uint128_t)(box_1->x - box_2->x) * (__uint128_t)(box_1->x - box_2->x);
	dist += (__uint128_t)(box_1->y - box_2->y) * (__uint128_t)(box_1->y - box_2->y);
	dist += (__uint128_t)(box_1->z - box_2->z) * (__uint128_t)(box_1->z - box_2->z);

	return (dist);
}

void	find_shortest(t_junction_box *j_boxes, t_dyn_int *circuits, size_t size, int two_x[2])
{
	size_t				best_i;
	size_t				best_j;
	__uint128_t			aux_dist;
	__uint128_t			shortest_dist = 0;
	static __uint128_t	last_dist;

	for (size_t i = 0; i < size-1; i++)
	{
		for (size_t j = i+1; j < size; j++)
		{
			aux_dist = dist(j_boxes + i, j_boxes + j);
			if (aux_dist > last_dist && (aux_dist < shortest_dist || shortest_dist == 0))
			{
				shortest_dist = aux_dist;
				best_i = i;
				best_j = j;
			}
		}
	}

	if (shortest_dist)
	{
		last_dist = shortest_dist;
		two_x[0] = j_boxes[best_i].x;
		two_x[1] = j_boxes[best_j].x;
		if (DEBUG)
			printf("The shortest are: (%d,%d,%d) and (%d,%d,%d)\n", j_boxes[best_i].x, j_boxes[best_i].y, j_boxes[best_i].z, j_boxes[best_j].x, j_boxes[best_j].y, j_boxes[best_j].z);
		connect(j_boxes, best_i, best_j, size, circuits);
	}
	// else if (DEBUG)
	else
		printf("This should not happen\n");
}

int	all_in_one(t_dyn_int *circuits, size_t circuits_size, size_t size)
{
	for (size_t i = 0; i < circuits_size; i++)
	{
		if (circuits->arr[i] == (int)size)
			return (1);
	}
	return (0);
}

int get_max(t_dyn_int *circuits)
{
	int max = 0;

	for (size_t i = 0; i < circuits->index; i++)
	{
		if (max < circuits->arr[i])
			max = circuits->arr[i];
	}
	return (max);
}

int main()
{
	int				fd = open("input.txt", O_RDONLY);
	char			*input;
	t_junction_box	*j_boxes = malloc(BOXES * sizeof(t_junction_box));
	size_t			n_boxes;
	size_t			j;
	t_dyn_int		circuits;

	if (fd < 0)
		error("File error");

	n_boxes = 0;
	while ((input = get_next_line(fd)) && n_boxes < BOXES)
	{
		j = 0;
		j_boxes[n_boxes].x = ft_atoi(input);
		while (ft_isdigit(input[j]))
			j++;
		j++;
		j_boxes[n_boxes].y = ft_atoi(input + j);
		while (ft_isdigit(input[j]))
			j++;
		j++;
		j_boxes[n_boxes].z = ft_atoi(input + j);
		j_boxes[n_boxes].circuit = BOXES; // unreachable number meaning that not belongs to any other circuit
		n_boxes++;
		free(input);
	}
	close (fd);
	if (DEBUG)
	{
		for (size_t k = 0; k<n_boxes; k++)
		{
			printf("(%d, %d, %d). Circuit: %ld\n", j_boxes[k].x, j_boxes[k].y, j_boxes[k].z, j_boxes[k].circuit);
		}
		putchar('\n');
		putchar('\n');
	}
	
	init_dyn_int(&circuits, 1024);
	int	last_two_x[2];
	int max = 0;
	for (size_t k = 0; max < (int)n_boxes; k++)
	{
		printf("Computing solution... %lu%%\r", max*100/n_boxes);

		find_shortest(j_boxes, &circuits, n_boxes, last_two_x);

		if (DEBUG)
		{
			for (size_t i = 0; i < circuits.index; i++)
			{
				if (circuits.arr[i])
					printf("Now, there are %d boxes in the circuit %ld\n", circuits.arr[i], i);
			}
			putchar('\n');
		}
		max = get_max(&circuits);
	}

	printf("If you multiply together the X coordinates of the last two junction boxes you need to connect, you get %ld.\n", (size_t)last_two_x[0] * (size_t)last_two_x[1]);
	free(j_boxes);
	free_dyn_int(&circuits);
}
