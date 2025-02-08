/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:00:02 by elel-bah          #+#    #+#             */
/*   Updated: 2024/12/30 17:13:32 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

t_inter calc_sphere_normal(t_inter current_hit, t_objs *sphere, t_ray *ray)
{
    t_inter new_hit;

    // Calculate the intersection distance between the ray and the sphere
    new_hit.t = calc_sp_ray_inter(ray, sphere);

    // Check if this intersection is valid and closer than the current closest
    if ((current_hit.t > new_hit.t || current_hit.t == -1) && new_hit.t > EPSILON)
    {
        // Update the intersection details
        new_hit.color = sphere->color;
        new_hit.hit_point = vec_addition(ray->origin, mult_vec(ray->direction, new_hit.t));
        new_hit.normal = scale_to_one(sub_vec(new_hit.hit_point, sphere->center));
        
        // Update the closest intersection
        current_hit = new_hit;
    }
    return (current_hit);
}

double calc_sp_ray_inter(t_ray *ray, t_objs *sphere)
{
    t_sphere    calc;
    t_vec       ray_to_center;
    double      radius;

    ray_to_center = sub_vec(ray->origin, sphere->center); // Vector from ray origin to sphere center
    radius = sphere->p.x / 2.0; // Radius of the sphere

    calc.a = dot_product(ray->direction, ray->direction); // Ray direction magnitude squared
    calc.b = 2.0 * dot_product(ray_to_center, ray->direction); // Linear coefficient
    calc.c = dot_product(ray_to_center, ray_to_center) - (radius * radius); // Distance offset

    calc.discri = calc.b * calc.b - (4 * calc.a * calc.c); // Discriminant

    // If discriminant is negative, no intersection
    if (calc.discri < EPSILON)
        return (-1);

    // Compute possible intersection distances
    calc.t1 = (-calc.b - sqrt(calc.discri)) / (2.0 * calc.a);
    calc.t2 = (-calc.b + sqrt(calc.discri)) / (2.0 * calc.a);

    // Determine the closest valid intersection point
    if (calc.t1 * calc.t2 > EPSILON) // Both intersections are positive
    {
        if (calc.t1 > EPSILON)
            return (take_min(calc.t1, calc.t2));
        return (-1); // No valid intersection
    }

    if (calc.t1 > EPSILON) // First intersection is valid
        return (calc.t1);

    return (calc.t2); // Second intersection is valid
}
