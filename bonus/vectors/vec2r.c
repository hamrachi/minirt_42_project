/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2r.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:58:52 by elel-bah          #+#    #+#             */
/*   Updated: 2024/12/23 16:52:33 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

void	reset_vec(t_vec *v)
{
	v->x = 0;
	v->y = 0;
	v->z = 0;
}

double	dot_product(t_vec u, t_vec v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vec	cross_product(t_vec v1, t_vec v2)
{
	t_vec	new_vec;

	new_vec.x = (v1.y * v2.z) - (v1.z * v2.y);
	new_vec.y = (v1.z * v2.x )- (v1.x * v2.z);
	new_vec.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (new_vec);
}

t_vec	mult_vec(t_vec v, double a)
{
	v.x = v.x * a;
	v.y = v.y * a;
	v.z = v.z * a;
	return (v);
}

t_vec	vec_addition(t_vec v1, t_vec v2)
{
	t_vec	w;

	w.x = v1.x + v2.x;
	w.y = v1.y + v2.y;
	w.z = v1.z + v2.z;
	return (w);
}
