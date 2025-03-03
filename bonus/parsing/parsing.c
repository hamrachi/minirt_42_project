/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:56:01 by elel-bah          #+#    #+#             */
/*   Updated: 2025/03/01 16:45:43 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

void	parse_cylinder_b(t_world *scene, char **args)
{
	t_scene_element	*obj;

	validate_cylinder_input_b(args);
	obj = allocate_object_b(scene);
	obj->type = CYLINDER;
	obj->center = get_vec_b(args[1]);
	obj->direction = get_vec_b(args[2]);
	validate_cylinder_orientation_b(obj->direction);
	obj->param.x_coord = ft_atod_b(args[3]);
	obj->param.y_coord = ft_atod_b(args[4]);
	validate_cylinder_diameter_b(obj->param.x_coord, obj->param.y_coord);
	obj->color = get_color_b(args[5]);
	obj->texture.has_checkerboard = 0;
	parse_checkerboard_b(&obj->texture, args, 6);
}

void	parse_sphere_b(t_world *scene, char **args)
{
	t_scene_element		*obj;
	int					arg_count;

	arg_count = 0;
	while (args[arg_count])
		arg_count++;
	if (arg_count != 4 && arg_count != 7)
		report_error_b("Invalid number of arguments for sphere. Use either:\nsp x,y,z diameter \
			r,g,b\nor\nsp x,y,z diameter r,g,b checker size r2,g2,b2");
	validate_sphere_input_b(args);
	obj = allocate_object_b(scene);
	obj->type = SPHERE;
	obj->center = get_vec_b(args[1]);
	obj->param.x_coord = ft_atod_b(args[2]);
	validate_sphere_diameter_b(obj->param.x_coord);
	obj->color = get_color_b(args[3]);
	if (arg_count == 7 && ft_strcmp_b(args[4], "checker") == 0)
	{
		obj->texture.has_checkerboard = 1;
		obj->texture.checker_size = ft_atod_b(args[5]);
		obj->texture.color2 = get_color_b(args[6]);
	}
	else if (arg_count == 7)
		report_error_b("Invalid sphere format. Use either:\nsp x,y,z diameter r,g,b\nor\nsp \
			x,y,z diameter r,g,b checker size r2,g2,b2");
}

void	parse_object_b(char *object_type, char **tokens, t_world *scene)
{
	if ((object_type[0] == 'A' && object_type[1] == '\0') \
		|| (object_type[0] == 'C' && object_type[1] == '\0') \
		|| (object_type[0] == 'L' && object_type[1] == '\0'))
		parse_scene_element_b(object_type[0], scene, tokens);
	else if ((ft_strcmp_b(object_type, "sp") == 0) \
		|| (ft_strcmp_b(object_type, "pl") == 0) \
		|| (ft_strcmp_b(object_type, "cy") == 0))
		parse_scene_shape_b(object_type, scene, tokens);
	else
		report_error_b("invalid object type");
}

void	process_scene_line_b(char **tokens, t_world *sc)
{
	if (*tokens)
		parse_object_b(*tokens, tokens, sc);
}

void	parse_scene_file_b(t_world *sc, int fd)
{
	char	**tokens;
	char	*current_line;

	sc->mlx = mlx_init();
	if (!sc->mlx)
		report_error_b("MLX initialization failed");
	while (1)
	{
		current_line = line_b(fd, &g_garbage_collector);
		if (current_line == NULL)
			break ;
		tokens = ft_split_b(current_line, ' ', &g_garbage_collector);
		if (tokens == NULL)
			break ;
		process_scene_line_b(tokens, sc);
	}
	close(fd);
}
