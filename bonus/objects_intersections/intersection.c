/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 21:39:46 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/28 17:04:54 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

t_inter_data	check_intersections_b(t_ray *ray, t_world *scene, \
	t_scene_element **closest_obj)
{
	t_inter_data	closest_inter;
	t_scene_element	*current_obj;
	t_inter_data	temp_inter;

	*closest_obj = NULL;
	closest_inter.t = -1.0;
	current_obj = scene->objs;
	while (current_obj)
	{
		temp_inter = closest_inter;
		if (current_obj->type == SPHERE)
			temp_inter = calc_sphere_normal_b(closest_inter, current_obj, ray);
		if (current_obj->type == PLAN)
			temp_inter = calc_plan_normal_b(closest_inter, current_obj, ray);
		if (current_obj->type == CYLINDER)
			temp_inter = calc_cylinder_normal_b(closest_inter, current_obj, ray);
		if (temp_inter.t > EPSILON && (closest_inter.t < 0 \
			|| temp_inter.t < closest_inter.t))
		{
			closest_inter = temp_inter;
			*closest_obj = current_obj;
		}
		current_obj = current_obj->next;
	}
	return (closest_inter);
}

t_inter_data	find_closest_intersection_b(t_ray *ray, t_world *scene)
{
	t_inter_data		closest_inter;
	t_scene_element		*closest_obj;

	closest_inter = check_intersections_b(ray, scene, &closest_obj);
	if (closest_obj && closest_inter.t > EPSILON)
	{
		if (closest_obj->texture.has_checkerboard)
			closest_inter.color = apply_checkerboard_b(&closest_inter, \
				&closest_obj->texture);
	}
	return (closest_inter);
}
