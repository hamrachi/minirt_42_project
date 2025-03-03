/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:52:56 by elel-bah          #+#    #+#             */
/*   Updated: 2025/03/01 16:43:17 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

int	ray_is_inside(t_point3d ray, t_point3d s_norm)
{
	if (dot_product(ray, s_norm) > 0)
		return (1);
	return (0);
}

int	is_point_in_shadow(t_world *scene, t_inter_data intersection, \
	t_light_source *light_source)
{
	t_point3d		vector_to_light;
	t_ray			shadow_ray;
	t_inter_data	shadow_hit;
	t_point3d		vector_to_shadow_hit;

	vector_to_light = sub_vec(light_source->position, intersection.hit_point);
	shadow_ray.origin = intersection.hit_point;
	shadow_ray.direction = scale_to_one(vector_to_light);
	shadow_hit = find_closest_intersection(&shadow_ray, scene);
	vector_to_shadow_hit = sub_vec(shadow_hit.hit_point, shadow_ray.origin);
	if (shadow_hit.t > EPSILON && (magnitude(vector_to_light) \
		> magnitude(vector_to_shadow_hit)))
		return (1);
	return (0);
}

t_point3d	diffuse(t_inter_data inter, t_light_source *light, double d)
{
	t_point3d	diff;

	diff = scale_and_combine_colors(inter.color, \
		light->light_color, d * light->brightness);
	return (diff);
}
