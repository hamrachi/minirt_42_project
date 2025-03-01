/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:56:01 by elel-bah          #+#    #+#             */
/*   Updated: 2025/03/01 16:43:06 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

void	parse_plane(t_world *scene, char **args)
{
	t_scene_element	*obj;

	validate_plane_input(args);
	obj = allocate_object(scene);
	obj->type = PLAN;
	obj->center = get_vec(args[1]);
	obj->direction = get_vec(args[2]);
	validate_plane_orientation(obj->direction);
	obj->color = get_color(args[3]);
}

t_point3d	get_color(char *str)
{
	char		**args;
	t_point3d	color;

	args = ft_split(str, ',', &g_garbage_collector);
	validate_color_input(args);
	color = (t_point3d){ft_atoi(args[0]), ft_atoi(args[1]), ft_atoi(args[2])};
	validate_color_range(color);
	return (color);
}

t_point3d	get_vec(char *s)
{
	char		**args;
	t_point3d	cord;

	args = ft_split(s, ',', &g_garbage_collector);
	validate_vec_input(args);
	cord = create_vector(ft_atod(args[0]), ft_atod(args[1]), ft_atod(args[2]));
	return (cord);
}

void	parse_scene_shape(const char *shape_type, t_world *scene, char **tokens)
{
	if (ft_strcmp(shape_type, "sp") == 0)
		parse_sphere(scene, tokens);
	else if (ft_strcmp(shape_type, "pl") == 0)
		parse_plane(scene, tokens);
	else if (ft_strcmp(shape_type, "cy") == 0)
		parse_cylinder(scene, tokens);
	else
		report_error("invalid scene shape");
}

void	parse_scene_element(char element_type, t_world *scene, char **tokens)
{
	if (element_type == 'A')
		parse_ambient(scene, tokens);
	else if (element_type == 'C')
		parse_camera(scene, tokens);
	else if (element_type == 'L')
		parse_light(scene, tokens);
	else
		report_error("invalid scene element");
}
