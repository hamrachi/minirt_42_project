/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:59:02 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/28 17:04:05 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

double	calc_pl_ray_inter_b(t_ray *ray, t_scene_element *plane)
{
	t_point3d	ray_to_plane;
	t_point3d	plane_norm;
	double		hit_dist;
	double		denom;
	double		num;

	plane_norm = scale_to_one_b(plane->direction);
	ray_to_plane = sub_vec_b(ray->origin, plane->center);
	denom = dot_product_b(ray->direction, plane_norm);
	if (denom != 0)
	{
		num = dot_product_b(ray_to_plane, plane_norm);
		hit_dist = -num / denom;
		if (hit_dist < EPSILON)
			return (-1.0);
		return (hit_dist);
	}
	return (-1.0);
}

t_inter_data	calc_plan_normal_b(t_inter_data closest_hit, \
		t_scene_element *plane, t_ray *ray)
{
	t_inter_data	current_hit;

	current_hit.t = calc_pl_ray_inter_b(ray, plane);
	if ((closest_hit.t > current_hit.t || closest_hit.t == -1) \
		&& current_hit.t > EPSILON)
	{
		current_hit.color = plane->color;
		current_hit.hit_point = vec_addition_b(ray->origin,
				mult_vec_b(ray->direction, current_hit.t));
		current_hit.normal = plane->direction;
		if (dot_product_b(ray->direction, current_hit.normal) < EPSILON)
		{
			current_hit.normal = scale_to_one_b(
					mult_vec_b(plane->direction, -1));
		}
		closest_hit = current_hit;
	}
	return (closest_hit);
}
