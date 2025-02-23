/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:49:29 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/23 21:45:14 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

void	parse_checkerboard(t_texture *texture, char **args, int start_idx)
{
	if (!args[start_idx])
		return ;
	if (!args[start_idx + 1] || !args[start_idx + 2])
		report_error("Invalid checkerboard parameters");
	texture->has_checkerboard = 1;
	texture->checker_size = ft_atod(args[start_idx + 1]);
	texture->color2 = get_color(args[start_idx + 2]);
	if (texture->checker_size <= 0)
		report_error("Checker size must be positive");
}

t_light_source	*alloc_light(t_world *sc)
{
	t_light_source	*new_light;

	new_light = malloc(sizeof(t_light_source));
	if (!new_light)
		report_error("allocation failed\n");
	new_light->next = sc->light;
	sc->light = new_light;
	return (new_light);
}

void	parse_light(t_world *scene, char **args)
{
	t_light_source	*new;

	validate_light_input(args);
	new = alloc_light(scene);
	new->position = get_vec(args[1]);
	new->brightness = ft_atod(args[2]);
	validate_light_ratio(new->brightness);
	new->light_color = get_color(args[3]);
}

void	parse_camera(t_world *scene, char **args)
{
	validate_camera_input(args, scene);
	scene->camera.cam_count++;
	scene->camera.origin = get_vec(args[1]);
	scene->camera.orientation = get_vec(args[2]);
	validate_camera_orientation(scene->camera.orientation);
	scene->camera.f_o_v = ft_atod(args[3]);
	validate_camera_fov(scene->camera.f_o_v);
}

void	parse_ambient(t_world *scene, char **args)
{
	validate_ambient_input(args, scene);
	scene->amb_light.light_count++;
	scene->amb_light.intensity = ft_atod(args[1]);
	validate_ambient_ratio_range(scene->amb_light.intensity);
	scene->amb_light.light_color = get_color(args[2]);
}
