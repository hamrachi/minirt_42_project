/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:52:56 by elel-bah          #+#    #+#             */
/*   Updated: 2024/12/30 17:14:25 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

int	ray_is_inside(t_vec ray, t_vec s_norm)
{
	if (dot_product(ray, s_norm) > 0)
		return (1);
	return (0);
}

int	is_point_in_shadow(t_scene *scene, t_inter intersection, t_light *light_source)
{ 
	t_vec		vector_to_light;
	t_ray		shadow_ray;
	t_inter		shadow_hit;
	t_vec		vector_to_shadow_hit;

	// Calculate the vector from the intersection point to the light source
	vector_to_light = sub_vec(light_source->src, intersection.hit_point);
	// Configure the shadow ray with its origin at the intersection point and direction toward the light source
	shadow_ray.origin = intersection.hit_point;
	shadow_ray.direction = scale_to_one(vector_to_light);
	// Find the closest object intersected by the shadow ray
	shadow_hit = find_closest_intersection(&shadow_ray, scene);
	// Calculate the vector from the shadow ray's origin to the point of intersection (if any)
	vector_to_shadow_hit = sub_vec(shadow_hit.hit_point, shadow_ray.origin);
	// Determine if the light source is blocked
	if (shadow_hit.t > EPSILON && (magnitude(vector_to_light) > magnitude(vector_to_shadow_hit)))
		return (1); // The point is in shadow
	return (0); // The point is not in shadow
}

t_vec	diffuse(t_inter inter, t_light *light, double d)
{
	t_vec	diff;

	diff = scale_and_combine_colors(inter.color, light->col, d * light->ratio);
	return (diff);
}