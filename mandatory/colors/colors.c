/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:54:58 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/18 15:23:26 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

t_point3d	compute_lighting(t_world *sc, t_inter_data inter, t_point3d ambclor)
{
	t_light_source	*current_light;
	t_point3d		final_color;
	t_point3d		light_derec;
	double			diffuse_factor;

	final_color = create_vector(0, 0, 0);
	current_light = sc->light;
	if (!current_light)
		return (ambclor);
	if (is_point_in_shadow(sc, inter, current_light))
		final_color = blend_colors(final_color, ambclor);
	else
	{
		light_derec = sub_vec(current_light->position, inter.hit_point);
		diffuse_factor = dot_product(scale_to_one(light_derec), inter.normal);
		final_color = blend_colors(final_color, ambclor);
		if (diffuse_factor > 0)
			final_color = blend_colors(final_color, \
				diffuse(inter, current_light, diffuse_factor));
	}
	return (final_color);
}

t_point3d	scale_and_combine_colors(t_point3d base_color, \
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

t_point3d	blend_colors(t_point3d color_a, t_point3d color_b)
{
	t_point3d	blended_color;

	blended_color = vec_addition(color_a, color_b);
	if (blended_color.x_coord > 255)
		blended_color.x_coord = 255;
	if (blended_color.y_coord > 255)
		blended_color.y_coord = 255;
	if (blended_color.z_coord > 255)
		blended_color.z_coord = 255;
	return (blended_color);
}

t_point3d	ray_color(t_ray *ray, t_world *sc)
	{
	t_inter_data	inter;
	t_point3d		px_col;
	t_point3d		amb;

	inter = find_closest_intersection(ray, sc);
	if (inter.t > EPSILON)
	{
		amb = scale_and_combine_colors(inter.color, \
			sc->amb_light.light_color, sc->amb_light.intensity);
		if (ray_is_inside(ray->direction, inter.normal))
			inter.normal = mult_vec(inter.normal, -1);
		px_col = compute_lighting(sc, inter, amb);
		return (px_col);
	}
	return (mult_vec(sc->amb_light.light_color, sc->amb_light.intensity));
}

int	create_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}
