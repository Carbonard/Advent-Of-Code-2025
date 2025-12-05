/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dynamic_ptr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:06:30 by rselva-2          #+#    #+#             */
/*   Updated: 2025/12/04 10:19:02 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dynarray.h"

int	add_ptr(t_dyn_ptr *d_array, void *str)
{
	if (!str)
		return (0);
	if (d_array->index >= d_array->size)
	{
		if (ft_realloc2((void ***)&(d_array->arr),
			d_array->size, d_array->size * 2))
			d_array->size *= 2;
		else
			return (0);
	}
	d_array->arr[d_array->index] = str;
	d_array->index++;
	return (1);
}

int	init_dyn_ptr(t_dyn_ptr *d_array, size_t size)
{
	d_array->size = size;
	d_array->index = 0;
	d_array->arr = malloc(d_array->size * sizeof(void *));
	if (!(d_array->arr))
	{
		d_array->size = 0;
		return (0);
	}
	return (1);
}

void	free_dyn_ptr(t_dyn_ptr *d_array)
{
	size_t	i;

	i = 0;
	while (i < d_array->index)
	{
		free(d_array->arr[i]);
		i++;
	}
	free(d_array->arr);
}
