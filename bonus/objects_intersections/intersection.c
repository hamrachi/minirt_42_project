/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 21:39:46 by elel-bah          #+#    #+#             */
/*   Updated: 2025/01/04 17:20:54 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

t_inter find_closest_intersection(t_ray *ray, t_scene *scene)
{
    t_inter closest_inter;
    t_objs *current_obj;
    t_objs *closest_obj = NULL;
    double u, v;

    closest_inter.t = -1.0;
    current_obj = scene->objs;

    while (current_obj)
    {
        t_inter temp_inter = closest_inter;

        if (current_obj->type == SPHERE)
            temp_inter = calc_sphere_normal(closest_inter, current_obj, ray);
        if (current_obj->type == PLAN)
            temp_inter = calc_plan_normal(closest_inter, current_obj, ray);
        if (current_obj->type == CYLINDER)
            temp_inter = calc_cylinder_normal(closest_inter, current_obj, ray);
        if (current_obj->type == CONE)
            temp_inter = cone_normal(closest_inter, current_obj, ray);

        if (temp_inter.t > EPSILON && (closest_inter.t < 0 || temp_inter.t < closest_inter.t))
        {
            closest_inter = temp_inter;
            closest_obj = current_obj;
        }

        current_obj = current_obj->next;
    }

    // Apply texture only if we found an intersection and have a valid object
    if (closest_obj && closest_inter.t > EPSILON)
    {
        // Calculate texture coordinates based on object type
        calculate_texture_coords(&closest_inter, closest_obj, &u, &v);

        // Apply texture if present
        if (closest_obj->texture.has_image && closest_obj->texture.has_image)
        {
            // Apply image texture using calculated UV coordinates
            closest_inter.color = get_texture_color(&closest_obj->texture, u, v);
        }
        else if (closest_obj->texture.has_checkerboard)
        {
            // Apply checkerboard texture
            closest_inter.color = apply_checkerboard(&closest_inter, &closest_obj->texture);
        }
    }

    return closest_inter;
}

// t_inter find_closest_intersection(t_ray *ray, t_scene *scene)//last_one
// {
//     t_inter closest_inter;
//     t_objs *current_obj;
//     t_objs *closest_obj = NULL;  // Keep track of the closest object

//     closest_inter.t = -1.0; // Initialize with no intersection
//     current_obj = scene->objs; // Start traversing objects

//     while (current_obj)
//     {
//         t_inter temp_inter = closest_inter;  // Store current intersection

//         if (current_obj->type == SPHERE)
//             temp_inter = calc_sphere_normal(closest_inter, current_obj, ray);
//         if (current_obj->type == PLAN)
//             temp_inter = calc_plan_normal(closest_inter, current_obj, ray);
//         if (current_obj->type == CYLINDER)
//             temp_inter = calc_cylinder_normal(closest_inter, current_obj, ray);
//         if (current_obj->type == CONE)
//             temp_inter = cone_normal(closest_inter, current_obj, ray);

//         // Update closest intersection if we found a closer one
//         if (temp_inter.t > EPSILON && (closest_inter.t < 0 || temp_inter.t < closest_inter.t))
//         {
//             closest_inter = temp_inter;
//             closest_obj = current_obj;  // Remember which object was closest
//         }

//         current_obj = current_obj->next;
//     }
//     // Apply texture only for the closest object
//     if (closest_obj && closest_inter.t > EPSILON)
//     {
//         closest_inter.has_checkerboard = closest_obj->texture.has_checkerboard;
//         if (closest_obj->texture.has_checkerboard)
//             closest_inter.color = apply_checkerboard(&closest_inter, &closest_obj->texture);
//     }

//     return (closest_inter);
// }

// t_inter find_closest_intersection(t_ray *ray, t_scene *scene)
// {
//     t_inter closest_inter;
//     t_objs *current_obj;

//     closest_inter.t = -1.0; // Initialize with no intersection
//     current_obj = scene->objs; // Start traversing objects

//     while (current_obj)
//     {
//         if (current_obj->type == SPHERE)
//             closest_inter = calc_sphere_normal(closest_inter, current_obj, ray);
//         if (current_obj->type == PLAN)
//             closest_inter = calc_plan_normal(closest_inter, current_obj, ray);
//         if (current_obj->type == CYLINDER)
//             closest_inter = calc_cylinder_normal(closest_inter, current_obj, ray);
//         if (current_obj->type == CONE)
//             closest_inter = cone_normal(closest_inter, current_obj, ray);

//         // Assign checkerboard texture if the intersection is valid
//         if (closest_inter.t > EPSILON)
//         {
//             closest_inter.has_checkerboard = current_obj->texture.has_checkerboard;
//             closest_inter.color = apply_checkerboard(&closest_inter, &current_obj->texture);
//         }

//         current_obj = current_obj->next; // Move to the next object
//     }
//     return (closest_inter);
// }


// t_inter	find_closest_intersection(t_ray *ray, t_scene *scene)//without else
// {
// 	t_inter	closest_inter; // Holds the closest intersection details
// 	t_objs	*current_obj;      // Pointer to traverse the objects in the scene

// 	closest_inter.t = -1.0; // Initialize to no intersection
// 	current_obj = scene->objs; // Start with the first object in the scene

// 	while (current_obj) // Loop through all objects in the scene
// 	{
// 		// Check the type of the current object and find intersections accordingly
// 		if (current_obj->type == SPHERE)
// 			closest_inter = calc_sphere_normal(closest_inter, current_obj, ray);
// 		if (current_obj->type == PLAN)
// 			closest_inter = calc_plan_normal(closest_inter, current_obj, ray);
// 		if (current_obj->type == CYLINDER)
// 			closest_inter =  calc_cylinder_normal(closest_inter, current_obj, ray);
//         if (current_obj->type == CONE)
// 			closest_inter =  cone_normal(closest_inter, current_obj, ray);
// 		// Move to the next object in the linked list
// 		current_obj = current_obj->next;
// 	}

// 	return closest_inter; // Return the closest intersection found
// }
