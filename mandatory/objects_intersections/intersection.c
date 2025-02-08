/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 21:39:46 by elel-bah          #+#    #+#             */
/*   Updated: 2025/01/30 20:13:07 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

t_inter_data	find_closest_intersection(t_ray *ray, t_world *scene)//without else
{
	t_inter_data	closest_inter; // Holds the closest intersection details
	t_scene_element	*current_obj;      // Pointer to traverse the objects in the scene

	closest_inter.t = -1.0; // Initialize to no intersection
	current_obj = scene->objs; // Start with the first object in the scene

	while (current_obj) // Loop through all objects in the scene
	{
		// Check the type of the current object and find intersections accordingly
		if (current_obj->type == SPHERE)
			closest_inter = calc_sphere_normal(closest_inter, current_obj, ray);
		if (current_obj->type == PLAN)
			closest_inter = calc_plan_normal(closest_inter, current_obj, ray);
		if (current_obj->type == CYLINDER)
			closest_inter =  calc_cylinder_normal(closest_inter, current_obj, ray);

		// Move to the next object in the linked list
		current_obj = current_obj->next;
	}

	return closest_inter; // Return the closest intersection found
}
