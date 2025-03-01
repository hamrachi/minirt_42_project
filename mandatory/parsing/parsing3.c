/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:49:29 by elel-bah          #+#    #+#             */
/*   Updated: 2025/03/01 16:43:09 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

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

	if (scene->light != NULL)
		report_error("Only one spotlight is allowed.");
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

void	parse_cylinder(t_world *scene, char **args)
{
	t_scene_element	*obj;

	validate_cylinder_input(args);
	obj = allocate_object(scene);
	obj->type = CYLINDER;
	obj->center = get_vec(args[1]);
	obj->direction = get_vec(args[2]);
	validate_cylinder_orientation(obj->direction);
	obj->param.x_coord = ft_atod(args[3]);
	obj->param.y_coord = ft_atod(args[4]);
	validate_cylinder_diameter(obj->param.x_coord, obj->param.y_coord);
	obj->color = get_color(args[5]);
}
