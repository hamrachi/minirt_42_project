/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:49:29 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/28 17:03:20 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

void	parse_checkerboard_b(t_texture *texture, char **args, int start_idx)
{
	if (!args[start_idx])
		return ;
	if (!args[start_idx + 1] || !args[start_idx + 2])
		report_error_b("Invalid checkerboard parameters");
	texture->has_checkerboard = 1;
	texture->checker_size = ft_atod_b(args[start_idx + 1]);
	texture->color2 = get_color_b(args[start_idx + 2]);
	if (texture->checker_size <= 0)
		report_error_b("Checker size must be positive");
}

t_light_source	*alloc_light_b(t_world *sc)
{
	t_light_source	*new_light;

	new_light = malloc(sizeof(t_light_source));
	if (!new_light)
		report_error_b("allocation failed\n");
	new_light->next = sc->light;
	sc->light = new_light;
	return (new_light);
}

void	parse_light_b(t_world *scene, char **args)
{
	t_light_source	*new;

	validate_light_input_b(args);
	new = alloc_light_b(scene);
	new->position = get_vec_b(args[1]);
	new->brightness = ft_atod_b(args[2]);
	validate_light_ratio_b(new->brightness);
	new->light_color = get_color_b(args[3]);
}

void	parse_camera_b(t_world *scene, char **args)
{
	validate_camera_input_b(args, scene);
	scene->camera.cam_count++;
	scene->camera.origin = get_vec_b(args[1]);
	scene->camera.orientation = get_vec_b(args[2]);
	validate_camera_orientation_b(scene->camera.orientation);
	scene->camera.f_o_v = ft_atod_b(args[3]);
	validate_camera_fov_b(scene->camera.f_o_v);
}

void	parse_ambient_b(t_world *scene, char **args)
{
	validate_ambient_input_b(args, scene);
	scene->amb_light.light_count++;
	scene->amb_light.intensity = ft_atod_b(args[1]);
	validate_ambient_ratio_range_b(scene->amb_light.intensity);
	scene->amb_light.light_color = get_color_b(args[2]);
}
