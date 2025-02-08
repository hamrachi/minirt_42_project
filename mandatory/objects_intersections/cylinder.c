/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:20:33 by elel-bah          #+#    #+#             */
/*   Updated: 2025/01/01 17:31:54 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

double calculate_cylinder_intersection(t_cylinder cylinder_calc, t_ray *ray, t_objs *cylinder)
{
    double t1 = (-cylinder_calc.quad_b + sqrt(cylinder_calc.discri)) / (2 * cylinder_calc.quad_a);
    double t2 = (-cylinder_calc.quad_b - sqrt(cylinder_calc.discri)) / (2 * cylinder_calc.quad_a);
    
    // Calculate intersection heights
    t_vec axis = scale_to_one(cylinder->direction);
    double y1 = dot_product(ray->direction, axis) * t1 
                + dot_product(cylinder_calc.ray_to_center, axis);
    double y2 = dot_product(ray->direction, axis) * t2 
                + dot_product(cylinder_calc.ray_to_center, axis);

    // Check height bounds for closest intersection point
    if (t2 > EPSILON && y2 >= 0 && y2 <= cylinder->p.y)
        return t2;
    if (t1 > EPSILON && y1 >= 0 && y1 <= cylinder->p.y)
        return t1;

    return (-1.0);
}

double find_cylinder_intersection(t_ray *ray, t_objs *cylinder)
{
    t_cylinder calc;
    
    calc.axis = scale_to_one(cylinder->direction);
    calc.ray_to_center = sub_vec(ray->origin, cylinder->center);

    double dot_dir_axis = dot_product(ray->direction, calc.axis);
    double dot_oc_axis = dot_product(calc.ray_to_center, calc.axis);
    
    calc.quad_a = dot_product(ray->direction, ray->direction) 
                  - (dot_dir_axis * dot_dir_axis);
    calc.quad_b = 2 * (dot_product(ray->direction, calc.ray_to_center) 
                  - (dot_dir_axis * dot_oc_axis));
    calc.quad_c = dot_product(calc.ray_to_center, calc.ray_to_center)
                  - (dot_oc_axis * dot_oc_axis) 
                  - pow(cylinder->p.x / 2, 2);

    calc.discri = calc.quad_b * calc.quad_b - 4 * calc.quad_a * calc.quad_c;

    if (calc.discri < EPSILON || calc.quad_a == 0)
        return (-1.0);

    return calculate_cylinder_intersection(calc, ray, cylinder);
}
t_inter calc_cylinder_normal(t_inter closest_hit, t_objs *cylinder, t_ray *ray)
{
    t_inter current_hit;
    double hit_height;
    t_vec cyl_axis;

    // Compute the intersection of the ray with the cylinder
    current_hit.t = find_cylinder_intersection(ray, cylinder);
    if ((closest_hit.t > current_hit.t || closest_hit.t == -1) && current_hit.t > EPSILON)
    {
        // Update the current intersection details
        current_hit.color = cylinder->color;
        current_hit.hit_point = vec_addition(ray->origin, mult_vec(ray->direction, current_hit.t));
        
        // Calculate the cylinder's normalized axis vector
        cyl_axis = scale_to_one(cylinder->direction);
        
        // Determine the intersection height along the cylinder axis
        hit_height = dot_product(ray->direction, mult_vec(cyl_axis, current_hit.t))
            + dot_product(sub_vec(ray->origin, cylinder->center), cyl_axis);
        
        // Compute the normal vector at the intersection point
        current_hit.normal = scale_to_one(sub_vec(sub_vec(current_hit.hit_point, cylinder->center),
                    mult_vec(cyl_axis, hit_height)));
        
        // Update the closest intersection
        closest_hit = current_hit;
    }
    return (closest_hit);
}

// t_inter calc_cylinder_normal(t_inter closest_hit, t_objs *cylinder, t_ray *ray)
// {
//     t_inter current_hit;
//     double hit_height;
//     t_vec cyl_axis;

//     // Compute the intersection of the ray with the cylinder
//     current_hit.t = find_cylinder_intersection(ray, cylinder);
//     if ((closest_hit.t > current_hit.t || closest_hit.t == -1) && current_hit.t > EPSILON)
//     {
//         // Update the current intersection details
//         current_hit.color = cylinder->color;
//         current_hit.hit_point = vec_addition(ray->origin, mult_vec(ray->direction, current_hit.t));
        
//         // Calculate the cylinder's normalized axis vector
//         cyl_axis = scale_to_one(cylinder->direction);
        
//         // Determine the intersection height along the cylinder axis
//         hit_height = dot_product(ray->direction, mult_vec(cyl_axis, current_hit.t))
//             + dot_product(sub_vec(ray->origin, cylinder->center), cyl_axis);
        
//         // Compute the normal vector at the intersection point
//         current_hit.normal = scale_to_one(sub_vec(sub_vec(current_hit.hit_point, cylinder->center),
//                     mult_vec(cyl_axis, hit_height)));
        
//         // Update the closest intersection
//         closest_hit = current_hit;
//     }
//     return (closest_hit);
// }

// double calculate_cylinder_intersection(t_cylinder cylinder_calc, t_ray *ray, t_objs *cylinder)
// {
//     // Calculate the two intersection distances (t1 and t2)
//     cylinder_calc.t1 = (-cylinder_calc.quad_b + sqrt(cylinder_calc.discri)) / (2 * cylinder_calc.quad_a);
//     cylinder_calc.t2 = (-cylinder_calc.quad_b - sqrt(cylinder_calc.discri)) / (2 * cylinder_calc.quad_a);

//     // If the first intersection is behind the ray, return no intersection
//     if (cylinder_calc.t1 < EPSILON)
//         return (-1.0);

//     // Select the closer intersection point
//     cylinder_calc.chosen_t = (cylinder_calc.t1 > cylinder_calc.t2) ? cylinder_calc.t2 : cylinder_calc.t1;

//     // Calculate heights along the cylinder axis at the intersections
//     cylinder_calc.height_t2 = dot_product(ray->direction, cylinder_calc.axis) * cylinder_calc.t2
//                             + dot_product(cylinder_calc.ray_to_center, cylinder_calc.axis);
//     cylinder_calc.height_t1 = dot_product(ray->direction, cylinder_calc.axis) * cylinder_calc.t1
//                             + dot_product(cylinder_calc.ray_to_center, cylinder_calc.axis);

//     // Check if the intersection points are within the cylinder's height bounds
//     if (cylinder_calc.height_t2 >= EPSILON && cylinder_calc.height_t2 <= cylinder->parameters.y)
//         return (cylinder_calc.t2);
//     if (cylinder_calc.height_t1 >= EPSILON && cylinder_calc.height_t1 <= cylinder->parameters.y)
//         return (cylinder_calc.t1);

//     // No valid intersection
//     return (-1.0);
// }

// double find_cylinder_intersection(t_ray *ray, t_objs *cylinder)
// {
//     t_cylinder calc; // Struct to store intermediate calculations

//     // Normalize the cylinder's direction vector
//     calc.axis = scale_to_one(cylinder->direction);

//     // Vector from ray origin to cylinder center
//     calc.ray_to_center = sub_vec(ray->origin, cylinder->center);

//     // Compute quadratic equation coefficients
//     calc.quad_a = dot_product(ray->direction, ray->direction) 
//                   - pow(dot_product(ray->direction, calc.axis), 2);
//     calc.quad_b = 2 * (dot_product(ray->direction, calc.ray_to_center)
//                        - dot_product(ray->direction, calc.axis)
//                        * dot_product(calc.ray_to_center, calc.axis));
//     calc.quad_c = dot_product(calc.ray_to_center, calc.ray_to_center)
//                   - pow(dot_product(calc.ray_to_center, calc.axis), 2)
//                   - pow(cylinder->parameters.x / 2, 2);

//     // Compute the discriminant
//     calc.discri = pow(calc.quad_b, 2) - 4 * calc.quad_a * calc.quad_c;

//     // If the discriminant is negative, there's no intersection
//     if (calc.discri < EPSILON)
//         return (-1.0);

//     // Find and return the closest valid intersection
//     return calculate_cylinder_intersection(calc, ray, cylinder);
// }
