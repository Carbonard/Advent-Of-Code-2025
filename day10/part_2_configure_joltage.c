#include "part_2.h"

// Save input data
static size_t read_input(t_machine machines[])
{
	int			fd = open("input.txt", O_RDONLY);
	char		*input;
	size_t		i;
	size_t		j;
	size_t		n_machines = 0;

	while ((input = get_next_line(fd)))
	{
		i = 0;
		while (input[i+1] != '(')
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
			machines[n_machines].buttons[k] = malloc((MAX_JOLTAGES+1) * sizeof(int));
			j = 0;
			while (input[i-1] != ')' && j < MAX_JOLTAGES)
			{
				machines[n_machines].buttons[k][j] = ft_atoi(input + i);
				j++;
				while (ft_isdigit(input[i]))
					i++;
				if (input[i] != ',' && input[i] != ')')
					puts("Wrong file content, ',' or ')' not found");
				i++;
				machines[n_machines].buttons[k][j] = -1;
			}
			machines[n_machines].n_buttons = k+1;
		}

		i++;
		if (input[i] != '{')
			puts("Wrong file content, '{' not found");
		i++;

		machines[n_machines].joltage = malloc((MAX_JOLTAGES) * sizeof(int));
		j = 0;
		while (j < MAX_JOLTAGES && input[i] != '}')
		{
			machines[n_machines].joltage[j] = ft_atoi(input + i);
			while (ft_isdigit(input[i]))
				i++;
			if (input[i] == ',')
				i++;
			j++;
		}
		machines[n_machines].n_joltage = j;

		n_machines++;
		free(input);
	}
	return (n_machines);
}

int joltage_in_button(int i_joltage, int *button)
{
	for (int i = 0; button[i] >= 0; i++)
	{
		if (i_joltage == button[i])
			return (1);
	}
	return (0);
}

// Translate the problem to a equation system
static size_t get_steps(t_machine *machine)
{
	t_eqsys	system;
	size_t		steps;

	system.n_eq = machine->n_joltage;
	system.n_var = machine->n_buttons;
	system.equations = malloc(system.n_eq * sizeof(int *));
	system.ind_terms = malloc (system.n_eq * sizeof(int));
	for (int eq = 0; eq < machine->n_joltage; eq++)
	{
		system.equations[eq] = malloc(system.n_var * sizeof(int));
		for (int coef = 0; coef < machine->n_buttons; coef++)
		{
			system.equations[eq][coef] = joltage_in_button(eq, machine->buttons[coef]);
		}
		system.ind_terms[eq] = machine->joltage[eq];
	}
	system.solution = malloc(system.n_var * sizeof(int));
	for (int i = 0; i < system.n_var; i++)
		system.solution[i] = -1;
	steps = solve_equation(&system);
	free_eq(&system);
	return (steps);
}

int main()
{
	t_machine	machines[MAX_MACHINES];
	size_t		n_machines;
	size_t		total_press = 0;

	n_machines = read_input(machines);

	size_t tmp;
	for (size_t m = 0; m < n_machines; m++)
	{
		tmp = (size_t)get_steps(&machines[m]);
		printf("\001\e[32m\002Machine %lu needs %lu button presses\001\e[0m\002\n", m, tmp);
		total_press += tmp;
	}
	printf("The fewest button presses required to correctly configure the indicator lights on all of the machines is %lu\n", total_press);

	for (size_t i = 0; i < n_machines; i++)
	{
		for (int j = 0; j < machines[i].n_buttons; j++)
			free(machines[i].buttons[j]);
		free(machines[i].buttons);
		free(machines[i].joltage);
	}
	return (0);
}
