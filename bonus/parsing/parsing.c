/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:56:01 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/28 15:47:43 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

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
	obj->texture.has_checkerboard = 0;
	parse_checkerboard(&obj->texture, args, 6);
}

void	parse_sphere(t_world *scene, char **args)
{
	t_scene_element		*obj;
	int					arg_count;

	arg_count = 0;
	while (args[arg_count])
		arg_count++;
	if (arg_count != 4 && arg_count != 7)
		report_error("Invalid number of arguments for sphere. Use either:\nsp x,y,z diameter \
			r,g,b\nor\nsp x,y,z diameter r,g,b checker size r2,g2,b2");
	validate_sphere_input(args);
	obj = allocate_object(scene);
	obj->type = SPHERE;
	obj->center = get_vec(args[1]);
	obj->param.x_coord = ft_atod(args[2]);
	validate_sphere_diameter(obj->param.x_coord);
	obj->color = get_color(args[3]);
	if (arg_count == 7 && ft_strcmp(args[4], "checker") == 0)
	{
		obj->texture.has_checkerboard = 1;
		obj->texture.checker_size = ft_atod(args[5]);
		obj->texture.color2 = get_color(args[6]);
	}
	else if (arg_count == 7)
		report_error("Invalid sphere format. Use either:\nsp x,y,z diameter r,g,b\nor\nsp \
			x,y,z diameter r,g,b checker size r2,g2,b2");
}

void	parse_object(char *object_type, char **tokens, t_world *scene)
{
	if ((object_type[0] == 'A' && object_type[1] == '\0') \
		|| (object_type[0] == 'C' && object_type[1] == '\0') \
		|| (object_type[0] == 'L' && object_type[1] == '\0'))
		parse_scene_element(object_type[0], scene, tokens);
	else if ((ft_strcmp(object_type, "sp") == 0) \
		|| (ft_strcmp(object_type, "pl") == 0) \
		|| (ft_strcmp(object_type, "cy") == 0))
		parse_scene_shape(object_type, scene, tokens);
	else
		report_error("invalid object type");
}

void	process_scene_line(char **tokens, t_world *sc)
{
	if (*tokens)
		parse_object(*tokens, tokens, sc);
}

void	parse_scene_file(t_world *sc, int fd)
{
	char	**tokens;
	char	*current_line;

	sc->mlx = mlx_init();
	if (!sc->mlx)
		report_error("MLX initialization failed");
	while (1)
	{
		current_line = line(fd, &g_garbage_collector);
		if (current_line == NULL)
			break;
		tokens = ft_split(current_line, ' ', &g_garbage_collector);
		if (tokens == NULL)
			break;
		process_scene_line(tokens, sc);
	}
	close(fd);
}
