/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:06:57 by elel-bah          #+#    #+#             */
/*   Updated: 2025/03/01 16:44:24 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

void	report_error_b(char *str)
{
	int	i;

	i = -1;
	write(2, "Error: ", 7);
	while (str[++i])
		write(2, &str[i], 1);
	write(2, "\n", 1);
	gc_cleanup_b(&g_garbage_collector, g_garbage_collector);
	exit(1);
}

void	initialize_scene_fields_b(t_world *scene)
{
	scene->objs = NULL;
	scene->amb_light.light_count = 0;
	scene->camera.cam_count = 0;
	scene->light = NULL;
}

t_world	*allocate_scene_b(void)
{
	t_world	*scene;

	g_garbage_collector = NULL;
	scene = gc_malloc_b(&g_garbage_collector, sizeof(t_world));
	if (!scene)
		return (NULL);
	initialize_scene_fields_b(scene);
	return (scene);
}

void	init_object_vec_b(t_scene_element *object)
{
	reset_vec_b(&(object->color));
	reset_vec_b(&(object->center));
	reset_vec_b(&(object->direction));
	reset_vec_b(&(object->param));
}

t_scene_element	*allocate_object_b(t_world *scene)
{
	t_scene_element	*new_object;

	new_object = gc_malloc_b(&g_garbage_collector, sizeof(t_scene_element));
	if (!new_object)
		return (NULL);
	init_object_vec_b(new_object);
	new_object->next = scene->objs;
	scene->objs = new_object;
	return (new_object);
}
