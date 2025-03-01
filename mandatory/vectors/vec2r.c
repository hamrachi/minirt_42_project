/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2r.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:58:52 by elel-bah          #+#    #+#             */
/*   Updated: 2025/03/01 19:27:54 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

void	reset_vec(t_point3d *v)
{
	v->x_coord = 0;
	v->y_coord = 0;
	v->z_coord = 0;
}

double	dot_product(t_point3d u, t_point3d v)
{
	return (u.x_coord * v.x_coord \
		+ u.y_coord * v.y_coord + u.z_coord * v.z_coord);
}

t_point3d	cross_product(t_point3d v1, t_point3d v2)
{
	t_point3d	new_vec;

	new_vec.x_coord = (v1.y_coord * v2.z_coord) - (v1.z_coord * v2.y_coord);
	new_vec.y_coord = (v1.z_coord * v2.x_coord) - (v1.x_coord * v2.z_coord);
	new_vec.z_coord = (v1.x_coord * v2.y_coord) - (v1.y_coord * v2.x_coord);
	return (new_vec);
}

t_point3d	mult_vec(t_point3d v, double a)
{
	v.x_coord = v.x_coord * a;
	v.y_coord = v.y_coord * a;
	v.z_coord = v.z_coord * a;
	return (v);
}

t_point3d	vec_addition(t_point3d v1, t_point3d v2)
{
	t_point3d	w;

	w.x_coord = v1.x_coord + v2.x_coord;
	w.y_coord = v1.y_coord + v2.y_coord;
	w.z_coord = v1.z_coord + v2.z_coord;
	return (w);
}
