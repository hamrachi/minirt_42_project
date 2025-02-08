/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:06:57 by elel-bah          #+#    #+#             */
/*   Updated: 2024/12/30 17:12:20 by elel-bah         ###   ########.fr       */
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
    gc_cleanup(&garbage_collector, garbage_collector);
	exit(1);
}

// Allocate scene

void initialize_scene_fields(t_scene *scene)
{
    scene->objs = NULL;
    scene->amb.count = 0;
    scene->cam.count = 0;
    scene->light = NULL;
}
t_scene *allocate_scene(void)//t+world
{
    t_scene *scene;

    garbage_collector = NULL;
    scene = gc_malloc(&garbage_collector, sizeof(t_scene));
    if (!scene)
        return (NULL);
    initialize_scene_fields(scene);
    return (scene);
}

// Allocate object

void init_object_vec(t_objs *object)
{
    reset_vec(&(object->color));
    reset_vec(&(object->center));
    reset_vec(&(object->direction));
    reset_vec(&(object->p));//
}

t_objs *allocate_object(t_scene *scene)
{
    t_objs *new_object;

    new_object = gc_malloc(&garbage_collector, sizeof(t_objs));
    if (!new_object)
        return (NULL);
    init_object_vec(new_object);
    new_object->next = scene->objs;
    scene->objs = new_object;
    return (new_object);
}
