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

void	join_circuits(size_t c_1, size_t c_2, t_junction_box *j_boxes, size_t size, t_dyn_int *circuits, size_t *c_size)
{
	if (c_1 > c_2)
	{
		join_circuits(c_2, c_1, j_boxes, size, circuits, c_size);
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

void	connect(t_junction_box *j_boxes, size_t i, size_t j, size_t size, t_dyn_int *circuits, size_t *c_size)
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
		j_boxes[i].circuit = *c_size;
		j_boxes[j].circuit = *c_size;
		circuits->arr[*c_size] = 2;
		(*c_size)++;
	}
	else if (j_boxes[i].circuit != BOXES && j_boxes[j].circuit != BOXES)
		join_circuits(j_boxes[i].circuit, j_boxes[j].circuit, j_boxes, size, circuits, c_size);
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

void	find_shortest(t_junction_box *j_boxes, t_dyn_int *circuits, size_t size, size_t *c_size)
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
		connect(j_boxes, best_i, best_j, size, circuits, c_size);
	}
}

int main()
{
	int				fd = open("input.txt", O_RDONLY);
	char			*input;
	t_junction_box	*j_boxes = malloc(BOXES * sizeof(t_junction_box));
	size_t			i;
	size_t			j;
	t_dyn_int		circuits;
	size_t			circuits_size = 0;

	if (fd < 0)
		error("File error");

	i = 0;
	while ((input = get_next_line(fd)) && i < BOXES)
	{
		j = 0;
		j_boxes[i].x = ft_atoi(input);
		while (ft_isdigit(input[j]))
			j++;
		j++;
		j_boxes[i].y = ft_atoi(input + j);
		while (ft_isdigit(input[j]))
			j++;
		j++;
		j_boxes[i].z = ft_atoi(input + j);
		j_boxes[i].circuit = BOXES; // unreachable number meaning that not belongs to any other circuit
		i++;
		free(input);
	}
	close (fd);
	if (DEBUG)
	{
		for (size_t k = 0; k<i; k++)
		{
			printf("(%d, %d, %d). Circuit: %ld\n", j_boxes[k].x, j_boxes[k].y, j_boxes[k].z, j_boxes[k].circuit);
		}
		putchar('\n');
		putchar('\n');
	}
	
	init_dyn_int(&circuits, 1024);
	for (size_t k = 0; k < PAIRS; k++)
	{
		printf("Computing solution... %lu%%\r", k*100/PAIRS);

		find_shortest(j_boxes, &circuits, i, &circuits_size);

		if (DEBUG)
		{
			for (size_t i = 0; i < circuits_size; i++)
			{
				if (circuits.arr[i])
					printf("Now, there are %d boxes in the circuit %ld\n", circuits.arr[i], i);
			}
			putchar('\n');
		}
	}

	free(j_boxes);
	for (size_t i = 0; i < circuits_size; i++)
	{
		if (circuits.arr[i]>10)
		printf("There are %d boxes in the circuit %ld\n", circuits.arr[i], i);
	}
	int	max_1 = circuits.arr[0], max_2 = circuits.arr[0], max_3 = circuits.arr[0];
	for (size_t i = 0; i < circuits_size; i++)
	{
		if (circuits.arr[i] > max_1)
		{
			max_3 = max_2;
			max_2 = max_1;
			max_1 = circuits.arr[i];
		}
		else if (circuits.arr[i] > max_2)
		{
			max_3 = max_2;
			max_2 = circuits.arr[i];
		}
		else if (circuits.arr[i] > max_3)
		{
			max_3 = circuits.arr[i];
		}
	}
	printf("\nIf you multiply together the sizes of the three largest circuits you obtain %d\n", max_1 * max_2 * max_3);
	free_dyn_int(&circuits);
}
