/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:05:18 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/23 20:37:01 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

t_point3d	calculate_light_reflection_vector(t_point3d hit, t_point3d normal,
	t_point3d light_pos, t_point3d cam_pos)
{
	t_point3d	light_dir;
	t_point3d	view_dir;
	double		dot_prod;

	light_dir = scale_to_one(sub_vec(light_pos, hit));
	view_dir = scale_to_one(sub_vec(hit, cam_pos));
	dot_prod = dot_product(normal, light_dir);
	return (sub_vec(mult_vec(normal, 2 * dot_prod), light_dir));
}

t_point3d	specular(t_world *scene, t_inter_data inter,
	t_light_source *light)
{
	t_point3d	reflection;
	t_point3d	view_dir;
	double		intensity;

	reflection = calculate_light_reflection_vector(inter.hit_point, \
		inter.normal, light->position, scene->camera.origin);
	view_dir = scale_to_one(sub_vec(inter.hit_point, scene->camera.origin));
	intensity = pow(dot_product(reflection, view_dir), 50.0) \
			* light->brightness * 0.5;
	return (mult_vec(light->light_color, intensity));
}
