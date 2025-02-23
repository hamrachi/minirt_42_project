/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:59:02 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/23 20:58:49 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

double	calc_pl_ray_inter(t_ray *ray, t_scene_element *plane)
{
	t_point3d	ray_to_plane;
	t_point3d	plane_norm;
	double		hit_dist;
	double		denom;
	double		num;

	plane_norm = scale_to_one(plane->direction);
	ray_to_plane = sub_vec(ray->origin, plane->center);
	denom = dot_product(ray->direction, plane_norm);
	if (denom != 0)
	{
		num = dot_product(ray_to_plane, plane_norm);
		hit_dist = -num / denom;
		if (hit_dist < EPSILON)
			return (-1.0);
		return (hit_dist);
	}
	return (-1.0);
}

t_inter_data	calc_plan_normal(t_inter_data closest_hit, \
		t_scene_element *plane, t_ray *ray)
{
	t_inter_data	current_hit;

	current_hit.t = calc_pl_ray_inter(ray, plane);
	if ((closest_hit.t > current_hit.t || closest_hit.t == -1) \
		&& current_hit.t > EPSILON)
	{
		current_hit.color = plane->color;
		current_hit.hit_point = vec_addition(ray->origin,
				mult_vec(ray->direction, current_hit.t));
		current_hit.normal = plane->direction;
		if (dot_product(ray->direction, current_hit.normal) < EPSILON)
		{
			current_hit.normal = scale_to_one(
					mult_vec(plane->direction, -1));
		}
		closest_hit = current_hit;
	}
	return (closest_hit);
}
