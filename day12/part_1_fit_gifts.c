#include "../libft/libft.h"
#include "../dynamic_arrays/src/ft_dynarray.h"
#include <fcntl.h>
#include <stdio.h>

#define GIFTS 6
#define PROBLEMS 1000

typedef struct s_problem
{
	int	width;
	int	height;
	int	n_gifts[GIFTS];
}	t_problems;

int main()
{
	int			fd = open("input.txt", O_RDONLY);
	t_dyn_ptr	input;
	t_problems	problems[PROBLEMS];

	init_dyn_ptr(&input, 1032);
	while(add_ptr(&input, get_next_line(fd)));

	for (size_t i = 0; i < PROBLEMS; i++)
	{
		problems[i].width = ft_atoi(input.arr[i+30]);
		problems[i].height = ft_atoi(input.arr[i+30]+3);
		for (int j = 0; j < GIFTS; j++)
		{
			problems[i].n_gifts[j] = ft_atoi(input.arr[i+30] + 7 + 3 * j);
		}
	}
	free_dyn_ptr(&input);

	for (int i = 0; i < PROBLEMS; i++)
	{
		printf("Size: %dx%d\nGifts: ", problems[i].width, problems[i].height);
		for (int j = 0; j < GIFTS; j++)
		{
			printf("%d ", problems[i].n_gifts[j]);
		}
		printf("\n");
	}

	int	gift_area[] = {7, 5, 7, 7, 7, 6};
	int	g_area;
	int	t_area;
	int	correct = 0;
	for (int i = 0; i < PROBLEMS; i++)
	{
		g_area = 1;
		for (int j = 0; j < GIFTS; j++)
		{
			g_area += gift_area[j] * problems[i].n_gifts[j];
		}
		t_area = problems[i].width * problems[i].height;
		if (t_area >= g_area)
		{
			correct++;
			printf("\e[32mOK \e[0m");
		}
		else if (t_area < g_area)
			printf("\e[31mKO \e[0m");
	}
	printf("\nNot more than %d trees are rigth.\n", correct);

	return (0);
}