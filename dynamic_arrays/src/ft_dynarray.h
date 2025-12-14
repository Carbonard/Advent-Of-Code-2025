/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dynarray.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 01:14:42 by rselva-2          #+#    #+#             */
/*   Updated: 2025/12/11 01:51:45 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct s_dyn_int
{
	int		*arr;
	size_t	size;
	size_t	index;
}	t_dyn_int;

typedef struct s_dyn_char
{
	char	*arr;
	size_t	size;
}	t_dyn_char;

typedef struct s_dyn_ptr
{
	char	**arr;
	size_t	size;
	size_t	index;
}	t_dyn_ptr;

typedef struct s_dyn_int_ptr
{
	int		**arr;
	size_t	size;
	size_t	index;
}	t_dyn_int_ptr;

typedef struct s_dyn_uint128
{
	__uint128_t	*arr;
	size_t		size;
	size_t		index;
}	t_dyn_uint128;

typedef struct s_dyn_size_t
{
	size_t	*arr;
	size_t	size;
	size_t	index;
}	t_dyn_size_t;

typedef struct s_dyn_size_t_ptr
{
	size_t	**arr;
	size_t	size;
	size_t	index;
}	t_dyn_size_t_ptr;

// realloc
int		ft_realloc(void **ptr, size_t old_size, size_t new_size);
int		ft_realloc2(void ***ptr, size_t old_size, size_t new_size);
// Int
int		add_int(t_dyn_int *d_array, int number);
int		init_dyn_int(t_dyn_int *d_array, size_t size);
void	free_dyn_int(t_dyn_int *d_array);
// Char
int		add_char(t_dyn_char *d_array, size_t index, char c);
int		init_dyn_char(t_dyn_char *d_array, size_t size);
void	free_dyn_char(t_dyn_char *d_array);
// Ptr
int		add_ptr(t_dyn_ptr *d_array, char *str);
int		init_dyn_ptr(t_dyn_ptr *d_array, size_t size);
void	free_dyn_ptr(t_dyn_ptr *d_array);
// Size_t ptr
int		add_st_ptr(t_dyn_size_t_ptr *d_array, size_t *str);
int		init_dyn_st_ptr(t_dyn_size_t_ptr *d_array, size_t size);
void	free_dyn_st_ptr(t_dyn_size_t_ptr *d_array);
// Size_t
int		add_st(t_dyn_size_t *d_array, size_t number);
int		init_dyn_st(t_dyn_size_t *d_array, size_t size);
void	free_dyn_st(t_dyn_size_t *d_array);
// uint128
int		add_ui128(t_dyn_uint128 *d_array, __uint128_t number);
int		init_dyn_ui128(t_dyn_uint128 *d_array, size_t size);
void	free_dyn_ui128(t_dyn_uint128 *d_array);
// int ptr
int		add_int_ptr(t_dyn_int_ptr *d_array, int *str);
int		init_dyn_int_ptr(t_dyn_int_ptr *d_array, size_t size);
void	free_dyn_int_ptr(t_dyn_int_ptr *d_array);