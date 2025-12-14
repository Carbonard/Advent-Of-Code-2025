#include "../libft/libft.h"
#include "../dynamic_arrays/src/ft_dynarray.h"
#include <fcntl.h>
#include <stdio.h>

#define MAX_LIGHTS 10
#define MAX_BUTTONS 20
#define MAX_MACHINES 200

typedef struct s_machine
{
	char		*lights;
	int			n_light;
	int			**buttons;
	int			n_buttons;
}	t_machine;

void print_int_arr(int *arr, int size)
{
	printf("(");
	for (int i = 0; i + 1 < size; i++)
	{
		printf("%d, ", arr[i]);
	}
	printf("%d)\n", arr[size-1]);
}

int light_in_button(int i_light, int *button)
{
	for (int i = 0; button[i] >= 0; i++)
	{
		if (i_light == button[i])
			return (1);
	}
	return (0);
}

int check(t_machine *mach, int arr[])
{
	int		cnt;
	// int	current_light[mach->n_light];

	// for (int i = 0; i < mach->n_light; i++)
	// 	current_light[i] = 0;
	for (int i_light = 0; i_light < mach->n_light; i_light++)
	{
		cnt = 0;
		for (int i_button = 0; i_button < mach->n_buttons; i_button++)
		{
			if (light_in_button(i_light, mach->buttons[i_button]))
				cnt += arr[i_button];
		}
		if (cnt%2 == 0 && mach->lights[i_light] != '.')
			return (0);
		if (cnt%2 == 1 && mach->lights[i_light] != '#')
			return (0);
	}
	return (1);
}

static int get_puls(t_machine *mach, int arr[], int to_fill, int sum, int total_sum)
{
	if (to_fill == mach->n_buttons - 1)
	{
		arr[to_fill] = total_sum - sum;
		// print_int_arr(arr, mach->n_buttons);
		return (check(mach, arr));
	}
	for (int i = 0; sum + i <= total_sum; i++)
	{
		arr[to_fill] = i;
		if (get_puls(mach, arr, to_fill + 1, sum + i, total_sum))
			return (1);
	}
	return (0);
}

int main()
{
	int			fd = open("input.txt", O_RDONLY);
	char		*input;
	size_t		i;
	size_t		j;
	t_machine	machines[MAX_MACHINES];
	size_t		n_machines = 0;
	size_t		total_press = 0;

	while ((input = get_next_line(fd)))
	{
		i = 0;
		if (input[i] != '[')
			puts("Wrong file content, '[' not found");
		i++;

		machines[n_machines].lights = malloc((MAX_LIGHTS + 1) * sizeof(char));
		j = 0;
		while (input[i] == '.' || input[i] == '#')
		{
			machines[n_machines].lights[j] = input[i];
			j++;
			i++;
		}
		machines[n_machines].lights[j] = 0;
		machines[n_machines].n_light = j;
		if (input[i] != ']')
			puts("Wrong file content, ']' not found");
		i++;

		machines[n_machines].buttons = malloc(MAX_BUTTONS * sizeof(int *));
		
		for (int k = 0; k < MAX_BUTTONS && input[i+1] != '{'; k++)
		{
			if (input[i] != ' ')
				puts("Wrong file content, ' ' not found");
			i++;
			if (input[i] != '(')
				puts("Wrong file content, '(' not found");
			i++;
			// printf("k:%lu\n", k);
			machines[n_machines].buttons[k] = malloc((MAX_LIGHTS+1) * sizeof(int));
			j = 0;
			while (input[i-1] != ')' && j < MAX_LIGHTS)
			{
				// printf("1.%s", input + i);
				machines[n_machines].buttons[k][j] = ft_atoi(input + i);
				j++;
				while (ft_isdigit(input[i]))
					i++;
				// printf("2.%s", input + i);
				if (input[i] != ',' && input[i] != ')')
					puts("Wrong file content, ',' or ')' not found");
				i++;
				machines[n_machines].buttons[k][j] = -1;
			}
			machines[n_machines].n_buttons = k+1;
		}
		n_machines++;
		free(input);
	}

	for (size_t i = 0; i < n_machines; i++)
	{
		printf("machine %lu:\n", i);
		printf("\tlights: [%s]\n", machines[i].lights);
		printf("\tbuttons:\n");
		for(int j = 0; j < machines[i].n_buttons; j++)
		{
			printf("\t\t");
			size_t len = 0;
			while (machines[i].buttons[j][len] >= 0)
				len++;
			print_int_arr(machines[i].buttons[j], len);
		}
	}

	for (size_t i = 0; i < n_machines; i++)
	{
		int	arr[(machines[i].n_buttons)];
		int n_sum = 1;
		while (!get_puls(machines + i, arr, 0, 0, n_sum))
			n_sum++;
		printf("For the machine %lu, is needed %i buttons pressed: ", i, n_sum);
		print_int_arr(arr, machines[i].n_buttons);
		total_press += (size_t)n_sum;
	}
	printf("The fewest button presses required to correctly configure the indicator lights on all of the machines is %lu\n", total_press);

	for (size_t i = 0; i < n_machines; i++)
	{
		for (int j = 0; j < machines[i].n_buttons; j++)
			free(machines[i].buttons[j]);
		free(machines[i].buttons);
		free(machines[i].lights);
	}
	return (0);
}