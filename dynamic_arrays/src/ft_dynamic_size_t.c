/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dynamic_size_t.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 22:34:40 by rselva-2          #+#    #+#             */
/*   Updated: 2025/12/07 22:34:42 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dynarray.h"

int	add_int(t_dyn_int *d_array, size_t index, size_t number)
{
	size_t	new_size;

	new_size = d_array->size;
	while (index >= new_size)
		new_size *= 2;
	if (new_size != d_array->size)
	{
		if (ft_realloc((void **)&(d_array->arr),
			d_array->size * sizeof(size_t), new_size * sizeof(size_t)))
			d_array->size = new_size;
		else
			return (0);
	}
	d_array->arr[index] = number;
	return (1);
}

int	init_dyn_int(t_dyn_int *d_array, size_t size)
{
	d_array->size = size;
	d_array->arr = malloc(d_array->size * sizeof(size_t));
	if (!(d_array->arr))
	{
		d_array->size = 0;
		return (0);
	}
	return (1);
}

void	free_dyn_int(t_dyn_int *d_array)
{
	d_array->size = 0;
	free(d_array->arr);
	d_array->arr = NULL;
}
