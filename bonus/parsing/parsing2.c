/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:15:50 by elel-bah          #+#    #+#             */
/*   Updated: 2025/03/01 19:31:28 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

void	parse_plane_b(t_world *scene, char **args)
{
	t_scene_element	*obj;

	validate_plane_input_b(args);
	obj = allocate_object_b(scene);
	obj->type = PLAN;
	obj->center = get_vec_b(args[1]);
	obj->direction = get_vec_b(args[2]);
	validate_plane_orientation_b(obj->direction);
	obj->color = get_color_b(args[3]);
	obj->texture.has_checkerboard = 0;
	parse_checkerboard_b(&obj->texture, args, 4);
}

t_point3d	get_color_b(char *str)
{
	char		**args;
	t_point3d	color;

	args = ft_split_b(str, ',', &g_garbage_collector);
	validate_color_input_b(args);
	color = (t_point3d){ft_atoi_b(args[0]), \
		ft_atoi_b(args[1]), ft_atoi_b(args[2])};
	validate_color_range_b(color);
	return (color);
}

t_point3d	get_vec_b(char *s)
{
	char		**args;
	t_point3d	cord;

	args = ft_split_b(s, ',', &g_garbage_collector);
	validate_vec_input_b(args);
	cord = create_vector_b(ft_atod_b(args[0]), \
		ft_atod_b(args[1]), ft_atod_b(args[2]));
	return (cord);
}

void	parse_scene_shape_b(const char *shape_type, t_world *scene, \
			char **tokens)
{
	if (ft_strcmp_b(shape_type, "sp") == 0)
		parse_sphere_b(scene, tokens);
	else if (ft_strcmp_b(shape_type, "pl") == 0)
		parse_plane_b(scene, tokens);
	else if (ft_strcmp_b(shape_type, "cy") == 0)
		parse_cylinder_b(scene, tokens);
	else
		report_error_b("invalid scene shape");
}

void	parse_scene_element_b(char element_type, t_world *scene, char **tokens)
{
	if (element_type == 'A')
		parse_ambient_b(scene, tokens);
	else if (element_type == 'C')
		parse_camera_b(scene, tokens);
	else if (element_type == 'L')
		parse_light_b(scene, tokens);
	else
		report_error_b("invalid scene element");
}
