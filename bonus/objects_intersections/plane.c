/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:59:02 by elel-bah          #+#    #+#             */
/*   Updated: 2025/01/01 12:07:01 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

double calc_pl_ray_inter(t_ray *ray, t_objs *plane)
{
    t_vec ray_to_plane;
    t_vec plane_norm;
    double hit_dist;
    double denom;
    double num;

    // Normalize the plane's normal vector
    plane_norm = scale_to_one(plane->direction);

    // Compute the vector from ray origin to the plane's center
    ray_to_plane = sub_vec(ray->origin, plane->center);

    // Compute the denominator (dot product of ray direction and plane normal)
    denom = dot_product(ray->direction, plane_norm);

    // Check if the ray is parallel to the plane
    if (denom != 0)
    {
        // Compute the numerator (dot product of ray-to-plane vector and plane normal)
        num = dot_product(ray_to_plane, plane_norm);

        // Calculate the intersection distance
        hit_dist = -num / denom;

        // Check if the intersection is valid
        if (hit_dist < EPSILON)
            return (-1.0);

        return (hit_dist);
    }

    // If the ray is parallel, return no intersection
    return (-1.0);
}

t_inter calc_plan_normal(t_inter closest_hit, t_objs *plane, t_ray *ray)
{
    t_inter current_hit;
    t_inter new_hit;
    // Calculate the intersection of the ray with the plane
    current_hit.t = calc_pl_ray_inter(ray, plane);

    // Check if this intersection is valid and closer than the current closest
    if ((closest_hit.t > current_hit.t || closest_hit.t == -1) && current_hit.t > EPSILON)
    {
        // Update the intersection details
        current_hit.color = plane->color;
        current_hit.hit_point = vec_addition(ray->origin, 
                                    mult_vec(ray->direction, current_hit.t));
        current_hit.normal = plane->direction;

        // Flip the normal if it faces the same direction as the ray
        if (dot_product(ray->direction, current_hit.normal) > __DBL_EPSILON__)
        {
            current_hit.normal = scale_to_one(
                                    mult_vec(plane->direction, -1));
        }
        new_hit.obj_type = PLAN;
        // Update the closest intersection with this plane
        closest_hit = current_hit;
    }

    return (closest_hit);
}
