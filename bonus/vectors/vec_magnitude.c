/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_magnitude.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:07:23 by elel-bah          #+#    #+#             */
/*   Updated: 2024/12/23 16:52:29 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

t_vec	scale_to_one(t_vec v)
{
	double	length;
	t_vec	normalized;

	length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (length == 0)
		return (v);
	normalized.x = v.x / length;
	normalized.y = v.y / length;
	normalized.z = v.z / length;
	return (normalized);
}