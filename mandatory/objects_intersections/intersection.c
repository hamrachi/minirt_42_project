/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 21:39:46 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/23 17:18:46 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

t_inter_data	find_closest_intersection(t_ray *ray, t_world *scene)
{
	t_inter_data	closest_inter;
	t_scene_element	*current_obj;

	closest_inter.t = -1.0;
	current_obj = scene->objs;
	while (current_obj)
	{
		if (current_obj->type == SPHERE)
			closest_inter = calc_sphere_normal(closest_inter, \
			current_obj, ray);
		if (current_obj->type == PLAN)
			closest_inter = calc_plan_normal(closest_inter, \
			current_obj, ray);
		if (current_obj->type == CYLINDER)
			closest_inter = calc_cylinder_normal(closest_inter, \
				current_obj, ray);
		current_obj = current_obj->next;
	}
	return (closest_inter);
}
