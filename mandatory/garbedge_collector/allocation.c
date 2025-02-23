/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:06:57 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/23 22:23:20 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

void	report_error(char *str)
{
	int	i;

	i = -1;
	write(2, "Error: ", 7);
	while (str[++i])
		write(2, &str[i], 1);
	write(2, "\n", 1);
	gc_cleanup(&g_garbage_collector, g_garbage_collector);
	exit(1);
}

void	initialize_scene_fields(t_world *scene)
{
	scene->objs = NULL;
	scene->amb_light.light_count = 0;
	scene->camera.cam_count = 0;
	scene->light = NULL;
}

t_world	*allocate_scene(void)
{
	t_world	*scene;

	g_garbage_collector = NULL;
	scene = gc_malloc(&g_garbage_collector, sizeof(t_world));
	if (!scene)
		return (NULL);
	initialize_scene_fields(scene);
	return (scene);
}

void	init_object_vec(t_scene_element *object)
{
	reset_vec(&(object->color));
	reset_vec(&(object->center));
	reset_vec(&(object->direction));
	reset_vec(&(object->param));
}

t_scene_element	*allocate_object(t_world *scene)
{
	t_scene_element	*new_object;

	new_object = gc_malloc(&g_garbage_collector, sizeof(t_scene_element));
	if (!new_object)
		return (NULL);
	init_object_vec(new_object);
	new_object->next = scene->objs;
	scene->objs = new_object;
	return (new_object);
}
