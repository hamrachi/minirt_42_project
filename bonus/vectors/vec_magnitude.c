/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_magnitude.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:07:23 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/28 17:01:37 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

t_point3d	scale_to_one_b(t_point3d v)
{
	double		length;
	t_point3d	normalized;

	length = sqrt(v.x_coord * v.x_coord \
		+ v.y_coord * v.y_coord + v.z_coord * v.z_coord);
	if (length == 0)
		return (v);
	normalized.x_coord = v.x_coord / length;
	normalized.y_coord = v.y_coord / length;
	normalized.z_coord = v.z_coord / length;
	return (normalized);
}
