#include "part_2.h"

// Substract some equations to others avoiding negative coefficients
int reduce_eq(int eq, t_eqsys *eqs)
{
	int	reduced = 0;
	for (int i = 0; i < eqs->n_eq; i++)
	{
		if (i != eq && arr_leq(eqs->equations[i], eqs->equations[eq], eqs->n_var) && !zeros(eqs->equations[i], eqs->n_var))
		{
			reduced = 1;
			for (int coef = 0; coef < eqs->n_var; coef++)
			{
				eqs->equations[eq][coef] -= eqs->equations[i][coef];
			}
			eqs->ind_terms[eq] -= eqs->ind_terms[i];
		}
	}
	return (reduced);
}

// Apply basic equations systems's reductions
void reduce_sys(t_eqsys *eqs)
{
	int	sys_reductible = 1;
	int	eq_reductible;

	while (sys_reductible)
	{
		sys_reductible = 0;
		// If any variable is solved, remove it from equations
		for (int eq = 0; eq < eqs->n_eq; eq++)
		{
			for(int c = 0; c < eqs->n_var; c++)
			{
				if (eqs->equations[eq][c] && eqs->solution[c] >= 0)
				{
					eqs->ind_terms[eq] -= eqs->equations[eq][c] * eqs->solution[c];
					eqs->equations[eq][c] = 0;
					sys_reductible = 1;
				}
			}
		}
		if (DEBUG)
		{
			printf("Resolved variables removed:\n");
			print_eqs(eqs);
		}
		// Gauss reduction
		eq_reductible = 1;
		while (eq_reductible)
		{
			eq_reductible = 0;
			for (int eq = 0; eq < eqs->n_eq; eq++)
				eq_reductible += reduce_eq(eq, eqs);
			if (eq_reductible)
				sys_reductible = 1;
		}
		if (DEBUG)
		{
			printf("Gauss-reducted:\n");
			print_eqs(eqs);
		}
		// If any equation have just one coefficient, resolve variable
		int	i;
		for (int eq = 0; eq < eqs->n_eq; eq++)
		{
			i = just_one_coef(eqs->equations[eq], eqs->n_var);
			if (i >= 0)
			{
				eqs->solution[i] = eqs->ind_terms[eq];
				eqs->equations[eq][i] = 0;
				eqs->ind_terms[eq] = 0;
				sys_reductible = 1;
			}
		}
	}
}

// Recursively look for the minimum valid solution
size_t brute_force(t_eqsys *eqs, int var, size_t *best_steps)
{
	size_t	steps;
	int		m;
	
	if (var >= eqs->n_var)
	{
		steps = sum_sol(eqs->solution, eqs->n_var);
		if (steps < *best_steps && non_negative(eqs->solution, eqs->n_var) && non_negative(eqs->ind_terms, eqs->n_eq) && solvable(eqs))
			*best_steps = steps;
		return (*best_steps);
	}
	if (zeros_col(eqs, var))
		return (brute_force(eqs, var+1, best_steps));
	m = min_ind(eqs, var);
	for (int i = 0; i <= m; i++)
	{
		eqs->solution[var] = i;
		t_eqsys *copy = copy_eq(eqs);
		reduce_sys(copy);
		reduce_sys(copy);
		steps = brute_force(copy, var+1, best_steps);
		free_eq(copy);
		free(copy);
		if (steps < *best_steps)
			*best_steps = steps;
	}
	return (*best_steps);
}

size_t keep_solving(t_eqsys *original_eqs)
{
	size_t steps = 100000000;
	return (brute_force(original_eqs, 0, &steps));
}

// First Gauss-reduction and, if not enough, calls the recursive function
size_t solve_equation(t_eqsys *eqs)
{
	int	reducible = 1;

	if (DEBUG)
	{
		printf("Original equation system:\n");
		print_eqs(eqs);
	}
	// Gauss-reduction
	while (reducible)
	{
		reducible = 0;
		for (int eq = 0; eq < eqs->n_eq; eq++)
		{
			reducible += reduce_eq(eq, eqs);
		}
	}
	if (DEBUG)
	{
		printf("Gauss-reducted:\n");
		print_eqs(eqs);
	}
	// If any variable is solved, remove it from equations
	int	i;
	for (int eq = 0; eq < eqs->n_eq; eq++)
	{
		i = just_one_coef(eqs->equations[eq], eqs->n_var);
		if (i >= 0)
		{
			eqs->solution[i] = eqs->ind_terms[eq];
			eqs->equations[eq][i] = 0;
			eqs->ind_terms[eq] = 0;
		}
	}
	if (DEBUG)
	{
		printf("Resolved variables removed:\n");
		print_eqs(eqs);
	}
	if (non_negative(eqs->solution, eqs->n_var))
		return (sum_sol(eqs->solution, eqs->n_var));
	size_t steps = keep_solving(eqs);
	return (steps);
}
