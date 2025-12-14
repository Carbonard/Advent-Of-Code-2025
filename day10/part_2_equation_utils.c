#include "part_2.h"

// Displays the solutions obtained so far
void print_solution(int *arr, int size)
{
	printf("(");
	for (int i = 0; i + 1 < size; i++)
	{
		if (arr[i] >= 0)
			printf("%d", arr[i]);
		printf(" ,");
	}
	if (arr[size-1] >= 0)
		printf("%d)\n", arr[size-1]);
	else
		printf(")\n");
}

// Displays the eq. system omiting all-zero equations
void print_eqs(t_eqsys *eqs)
{
	for (int i = 0; i < eqs->n_eq; i++)
	{
		if (!zeros(eqs->equations[i], eqs->n_var))
		{
			printf("( ");
			for (int coef = 0; coef < eqs->n_var; coef++)
			{
				printf("%d ", eqs->equations[i][coef]);
			}
			printf(") = %d\n", eqs->ind_terms[i]);
		}
	}
	printf("Solution: ");
	print_solution(eqs->solution, eqs->n_var);
	printf("----------------------------\n");
}

// Returns a pointer to a copy of the eq. system
t_eqsys *copy_eq(t_eqsys *eqs)
{
	t_eqsys *copy = malloc(sizeof(t_eqsys));

	copy->equations = malloc(eqs->n_eq * sizeof(int *));
	for (int eq = 0; eq < eqs->n_eq; eq++)
	{
		copy->equations[eq] = malloc(eqs->n_var * sizeof(int));
		ft_memcpy(copy->equations[eq], eqs->equations[eq], eqs->n_var * sizeof(int));
	}
	copy->ind_terms = malloc(eqs->n_eq * sizeof(int *));
	ft_memcpy(copy->ind_terms, eqs->ind_terms, eqs->n_eq * sizeof(int));
	copy->solution = malloc(eqs->n_var * sizeof(int *));
	ft_memcpy(copy->solution, eqs->solution, eqs->n_var * sizeof(int));
	copy->n_eq = eqs->n_eq;
	copy->n_var = eqs->n_var;
	return (copy);
}

void free_eq(t_eqsys *eqs)
{
	for (int eq = 0; eq < eqs->n_eq; eq++)
	{
		free(eqs->equations[eq]);
	}
	free(eqs->equations);
	free(eqs->ind_terms);
	free(eqs->solution);
}

// Check if first array is lesser or equal to second (element to element)
int arr_leq(int *arr1, int *arr2, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (arr1[i] > arr2[i])
			return (0);
	}
	return (1);
}

// Check if the array has only zeros
int	zeros(int *arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] != 0)
			return (0);
	}
	return (1);
}

// If there is just one coefficient in the equation return the index, otherwise, return -1
int	just_one_coef(int *eq, int size)
{
	int	index = -1;

	for (int i = 0; i < size; i++)
	{
		if (eq[i] && index == -1)
			index = i;
		else if (eq[i])
			return (-1);
	}
	if (index == -1)
		return (-1);
	return (index);
}

// Check if every item is non-negative
int non_negative(int *arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] < 0)
			return (0);
	}
	return (1);
}

// Check if the given system is compatible (if all coefficients are zero, independent term must be zero as well)
int	solvable(t_eqsys *eqs)
{
	for (int eq = 0; eq < eqs->n_eq; eq++)
	{
		if (zeros(eqs->equations[eq], eqs->n_var) && eqs->ind_terms[eq] != 0)
			return (0);
	}
	return (1);
}

// Calculate the sum of the obtained variables
size_t sum_sol(int *sol, int size)
{
	size_t	sum = 0;

	for (int i = 0; i < size; i++)
	{
		if (sol[1] >= 0)
			sum += sol[i];
	}
	return (sum);
}

// Check if it's the last non-zero coefficient of the equation (among the non-solved columns)
int	last_coef(t_eqsys *eqs, int eq, int coef)
{
	for (int i = coef + 1; i < eqs->n_var; i++)
	{
		if (eqs->equations[eq][i] && eqs->solution[i] < 0)
			return (0);
	}
	return (1);
}

// Check if the columns is all zeros and hence useless
int zeros_col(t_eqsys *eqs, int coef)
{
	for (int eq = 0; eq < eqs->n_eq; eq++)
	{
		if (eqs->equations[eq][coef])
			return (0);
	}
	return (1);
}

// Finds the minimum independent term among the equations such that have non-zero coefficient on the specified column
int min_ind(t_eqsys *eqs, int coef)
{
	int min = 10000000;

	for (int eq = 0; eq < eqs->n_eq; eq++)
	{
		if (eqs->equations[eq][coef] && eqs->ind_terms[eq] < min)
			min = eqs->ind_terms[eq];
	}
	return (min);
}
