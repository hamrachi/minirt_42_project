/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 21:39:46 by elel-bah          #+#    #+#             */
/*   Updated: 2025/03/01 19:40:25 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

t_inter_data	check_intersections_b(t_ray *ray, t_world *scene, \
	t_scene_element **closest_obj)
{
	t_inter_data	closest_inter;
	t_scene_element	*curent_obj;
	t_inter_data	temp_inter;

	*closest_obj = NULL;
	closest_inter.t = -1.0;
	curent_obj = scene->objs;
	while (curent_obj)
	{
		temp_inter = closest_inter;
		if (curent_obj->type == SPHERE)
			temp_inter = calc_sphere_normal_b(closest_inter, curent_obj, ray);
		if (curent_obj->type == PLAN)
			temp_inter = calc_plan_normal_b(closest_inter, curent_obj, ray);
		if (curent_obj->type == CYLINDER)
			temp_inter = calc_cylinder_normal_b(closest_inter, curent_obj, ray);
		if (temp_inter.t > EPSILON && (closest_inter.t < 0 \
			|| temp_inter.t < closest_inter.t))
		{
			closest_inter = temp_inter;
			*closest_obj = curent_obj;
		}
		curent_obj = curent_obj->next;
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
