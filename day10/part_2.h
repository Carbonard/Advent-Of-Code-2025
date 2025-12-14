#include "../libft/libft.h"
#include "../dynamic_arrays/src/ft_dynarray.h"
#include <fcntl.h>
#include <stdio.h>

#define MAX_JOLTAGES 10
#define MAX_BUTTONS 20
#define MAX_MACHINES 200
#define DEBUG 0

typedef struct s_machine
{
	int			*joltage;
	int			n_joltage;
	int			**buttons;
	int			n_buttons;
}	t_machine;

typedef struct s_eqsys
{
	int		**equations;
	int		*ind_terms;
	int		n_eq;
	int		n_var;
	int		*solution;
}	t_eqsys;


size_t	solve_equation(t_eqsys *eqs);
// Utils
void	print_solution(int *arr, int size);
void	print_eqs(t_eqsys *eqs);
t_eqsys	*copy_eq(t_eqsys *eqs);
void	free_eq(t_eqsys *eqs);
int		arr_leq(int *arr1, int *arr2, int size);
int		zeros(int *arr, int size);
int		just_one_coef(int *eq, int size);
int		non_negative(int *arr, int size);
int		solvable(t_eqsys *eqs);
size_t	sum_sol(int *sol, int size);
int		last_coef(t_eqsys *eqs, int eq, int coef);
int		zeros_col(t_eqsys *eqs, int coef);
int		min_ind(t_eqsys *eqs, int coef);