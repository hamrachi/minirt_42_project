/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2r1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:34:23 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/23 22:14:47 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

t_point3d	sub_vec(t_point3d u, t_point3d v)
{
	t_point3d	w;

	w.x_coord = u.x_coord - v.x_coord;
	w.y_coord = u.y_coord - v.y_coord;
	w.z_coord = u.z_coord - v.z_coord;
	return (w);
}

double	magnitude(t_point3d	v)
{
	return (sqrt(pow(v.x_coord, 2) + pow(v.y_coord, 2) + pow(v.z_coord, 2)));
}

t_point3d	div_vect(t_point3d v, double a)
{
	v.x_coord /= a;
	v.y_coord /= a;
	v.z_coord /= a;
	return (v);
}

t_point3d	create_vector(double x, double y, double z)
{
	t_point3d	vec;

	vec.x_coord = x;
	vec.y_coord = y;
	vec.z_coord = z;
	return (vec);
}
