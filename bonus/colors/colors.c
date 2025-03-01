/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:54:58 by elel-bah          #+#    #+#             */
/*   Updated: 2025/03/01 16:44:16 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

t_point3d	compute_lighting_b(t_world *scene, \
	t_inter_data intersection, t_point3d ambient_color)
{
	t_light_source	*current_light;
	t_point3d		final_color;
	t_point3d		light_direction;
	double			diffuse_factor;

	final_color = create_vector_b(0, 0, 0);
	current_light = scene->light;
	while (current_light)
	{
		if (!is_point_in_shadow_b(scene, intersection, current_light))
		{
			light_direction = sub_vec_b(current_light->position, \
				intersection.hit_point);
			diffuse_factor = dot_product_b(scale_to_one_b(light_direction), \
				intersection.normal);
			if (diffuse_factor > 0)
				final_color = blend_colors_b(final_color, \
					diffuse_b(intersection, current_light, diffuse_factor));
			final_color = blend_colors_b(final_color, \
				specular_b(scene, intersection, current_light));
		}
		current_light = current_light->next;
	}
	final_color = blend_colors_b(final_color, ambient_color);
	return (final_color);
}

t_point3d	scale_and_combine_colors_b(t_point3d base_color, \
			t_point3d light_color, double intensity_ratio)
{
	t_point3d	result_color;

	result_color.x_coord = base_color.x_coord \
		* (light_color.x_coord / 255) * intensity_ratio;
	result_color.y_coord = base_color.y_coord \
		* (light_color.y_coord / 255) * intensity_ratio;
	result_color.z_coord = base_color.z_coord \
		* (light_color.z_coord / 255) * intensity_ratio;
	return (result_color);
}

t_point3d	blend_colors_b(t_point3d color_a, t_point3d color_b)
{
	t_point3d	blended_color;

	blended_color = vec_addition_b(color_a, color_b);
	if (blended_color.x_coord > 255)
		blended_color.x_coord = 255;
	if (blended_color.y_coord > 255)
		blended_color.y_coord = 255;
	if (blended_color.z_coord > 255)
		blended_color.z_coord = 255;
	return (blended_color);
}

t_point3d	ray_color_b(t_ray *ray, t_world *sc)
	{
	t_inter_data	inter;
	t_point3d		px_col;
	t_point3d		amb;

	inter = find_closest_intersection_b(ray, sc);
	if (inter.t > EPSILON)
	{
		amb = scale_and_combine_colors_b(inter.color, \
			sc->amb_light.light_color, sc->amb_light.intensity);
		if (ray_is_inside_b(ray->direction, inter.normal))
			inter.normal = mult_vec_b(inter.normal, -1);
		px_col = compute_lighting_b(sc, inter, amb);
		return (px_col);
	}
	return (mult_vec_b(sc->amb_light.light_color, sc->amb_light.intensity));
}

int	create_rgb_b(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}
