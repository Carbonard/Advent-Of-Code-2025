/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dynamic_uint128.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 00:59:51 by rselva-2          #+#    #+#             */
/*   Updated: 2025/12/11 01:01:34 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dynarray.h"

int	add_ui128(t_dyn_uint128 *d_array, __uint128_t number)
{
	size_t	new_size;

	new_size = d_array->size;
	while (d_array->index >= new_size)
		new_size *= 2;
	if (new_size != d_array->size)
	{
		if (ft_realloc((void **)&(d_array->arr),
			d_array->size * sizeof(__uint128_t), new_size * sizeof(__uint128_t)))
			d_array->size = new_size;
		else
			return (0);
	}
	d_array->arr[d_array->index] = number;
	d_array->index++;
	return (1);
}

int	init_dyn_ui128(t_dyn_uint128 *d_array, size_t size)
{
	d_array->size = size;
	d_array->arr = malloc(d_array->size * sizeof(__uint128_t));
	if (!(d_array->arr))
	{
		d_array->size = 0;
		d_array->index = 0;
		return (0);
	}
	return (1);
}

void	free_dyn_ui128(t_dyn_uint128 *d_array)
{
	d_array->size = 0;
	d_array->index = 0;
	free(d_array->arr);
	d_array->arr = NULL;
}
