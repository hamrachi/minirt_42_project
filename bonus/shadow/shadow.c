/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:52:56 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/28 17:10:06 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

int	ray_is_inside_b(t_point3d ray, t_point3d s_norm)
{
	if (dot_product_b(ray, s_norm) > 0)
		return (1);
	return (0);
}

int	is_point_in_shadow_b(t_world *scene, t_inter_data intersection, \
	t_light_source *light_source)
{
	t_point3d		vector_to_light;
	t_ray			shadow_ray;
	t_inter_data	shadow_hit;
	t_point3d		vector_to_shadow_hit;

	vector_to_light = sub_vec_b(light_source->position, intersection.hit_point);
	shadow_ray.origin = intersection.hit_point;
	shadow_ray.direction = scale_to_one_b(vector_to_light);
	shadow_hit = find_closest_intersection_b(&shadow_ray, scene);
	vector_to_shadow_hit = sub_vec_b(shadow_hit.hit_point, shadow_ray.origin);
	if (shadow_hit.t > EPSILON && (magnitude_b(vector_to_light) \
		> magnitude_b(vector_to_shadow_hit)))
		return (1);
	return (0);
}

t_point3d	diffuse_b(t_inter_data inter, t_light_source *light, double d)
{
	t_point3d	diff;

	diff = scale_and_combine_colors_b(inter.color, \
		light->light_color, d * light->brightness);
	return (diff);
}
