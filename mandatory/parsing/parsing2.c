/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:56:01 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/23 18:12:55 by elel-bah         ###   ########.fr       */
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

	args = ft_split(str, ',');
	validate_color_input(args);
	color = (t_point3d){ft_atoi(args[0]), ft_atoi(args[1]), ft_atoi(args[2])};
	validate_color_range(color);
	free_split(args);
	return (color);
}

t_point3d	get_vec(char *s)
{
	char		**args;
	t_point3d	cord;

	args = ft_split(s, ',');
	validate_vec_input(args);
	cord = create_vector(ft_atod(args[0]), ft_atod(args[1]), ft_atod(args[2]));
	free_split(args);
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

// void	parse_object(char *object_type, char **tokens, t_world *scene)
// {
// 	if ((object_type[0] == 'A' && object_type[1] == '\0') \
// 		|| (object_type[0] == 'C' && object_type[1] == '\0') \
// 		|| (object_type[0] == 'L' && object_type[1] == '\0'))
// 		parse_scene_element(object_type[0], scene, tokens);
// 	else if ((ft_strcmp(object_type, "sp") == 0) \
// 		|| (ft_strcmp(object_type, "pl") == 0) \
// 		|| (ft_strcmp(object_type, "cy") == 0))
// 		parse_scene_shape(object_type, scene, tokens);
// 	else
// 		report_error("invalid object type");
// }

// void	process_scene_line(char **tokens, t_world *sc)
// {
// 	if (*tokens)
// 		parse_object(*tokens, tokens, sc);
// }

// void	parse_scene_file(t_world *sc, int fd)
// {
// 	char	**tokens;

// 	while (1)
// 	{
// 		tokens = ft_split(line(fd), ' ');
// 		if (tokens == NULL)
// 			break ;
// 		process_scene_line(tokens, sc);
// 		free_split(tokens);
// 	}
// 	close(fd);
// }
