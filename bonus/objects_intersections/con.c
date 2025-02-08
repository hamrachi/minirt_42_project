/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   con.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:58:09 by elel-bah          #+#    #+#             */
/*   Updated: 2024/12/30 17:25:56 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

double pick_cone_intersection(t_objs *cone, t_ray *ray, t_cone_info cone_info)
{
    // Check if the discriminant is negative (no intersection)
    if (cone_info.discriminant < 0)
        return (-1.0);

    // Calculate the two potential intersection points (t1 and t2)
    cone_info.t_near = (-cone_info.b + sqrt(cone_info.discriminant)) / (2 * cone_info.a);
    cone_info.t_far = (-cone_info.b - sqrt(cone_info.discriminant)) / (2 * cone_info.a);

    // If the near intersection is behind the ray, return no intersection
    if (cone_info.t_near < EPSILON)
        return (-1.0);

    // Pick the closer valid intersection (t)
    if (cone_info.t_near > cone_info.t_far)
        cone_info.t_closest = cone_info.t_far;
    else
        cone_info.t_closest = cone_info.t_near;

    // Calculate the y-coordinates for the intersections
    cone_info.y_far = dot_product(ray->direction, cone_info.axis) * cone_info.t_far
        + dot_product(cone_info.origin_to_cone, cone_info.axis);
    cone_info.y_near = dot_product(ray->direction, cone_info.axis) * cone_info.t_near
        + dot_product(cone_info.origin_to_cone, cone_info.axis);

    // Check if the y-coordinates are within the cone's height range
    if (cone_info.y_far >= EPSILON && cone_info.y_far <= cone->p.y)
        return (cone_info.t_far);
    if (cone_info.y_near >= EPSILON && cone_info.y_near <= cone->p.y)
        return (cone_info.t_near);

    // No valid intersection
    return (-1.0);
}
double intersect_cone(t_ray *ray, t_objs *cone)
{
    t_cone_info cone_info;
    double intersection_t;

    // Calculate the slope of the cone (k)
    cone_info.slope = tan((cone->p.z / 2) * M_PI / 180.0);

    // Normalize the cone's axis direction
    cone_info.axis = scale_to_one(cone->direction);

    // Vector from ray origin to cone center
    cone_info.origin_to_cone = sub_vec(ray->origin, cone->center);

    // Quadratic coefficients (a, b, c) for the ray-cone intersection
    cone_info.a = dot_product(ray->direction, ray->direction) 
        - (1 + pow(cone_info.slope, 2.0)) 
        * pow(dot_product(ray->direction, cone_info.axis), 2);

    cone_info.b = 2.0 * (dot_product(ray->direction, cone_info.origin_to_cone)
        - (1 + pow(cone_info.slope, 2.0)) 
        * dot_product(ray->direction, cone_info.axis) 
        * dot_product(cone_info.origin_to_cone, cone_info.axis));

    cone_info.c = dot_product(cone_info.origin_to_cone, cone_info.origin_to_cone) 
        - (1 + pow(cone_info.slope, 2.0)) 
        * pow(dot_product(cone_info.origin_to_cone, cone_info.axis), 2);

    // Discriminant for the quadratic equation
    cone_info.discriminant = cone_info.b * cone_info.b - (4 * cone_info.a * cone_info.c);

    // Find the nearest valid intersection
    intersection_t = pick_cone_intersection(cone, ray, cone_info);
    return (intersection_t);
}

t_inter cone_normal(t_inter closest_hit, t_objs *cone, t_ray *ray)
{
    t_inter current_hit;
    double slope;                  // Slope of the cone (tan(angle/2))
    double m;                      // Scalar projection for calculating the normal
    t_vec axis;                    // Normalized direction of the cone's axis
    t_vec point_to_apex;           // Vector from hit point to cone apex
    t_vec normal_vector;           // Unnormalized normal at the intersection point

    // Calculate the slope of the cone
    slope = tan((cone->p.z / 2) * M_PI / 180.0);

    // Find the intersection point (t) with the cone
    current_hit.t = intersect_cone(ray, cone);

    // Normalize the cone's axis direction
    axis = scale_to_one(cone->direction);

    // Calculate the scalar projection (m) for the cone's normal
    m = dot_product(ray->direction, mult_vec(axis, current_hit.t)) +
        dot_product(sub_vec(ray->origin, cone->center), axis);

    // Update if this intersection is closer and valid
    if ((closest_hit.t > current_hit.t || closest_hit.t == -1) && current_hit.t > EPSILON)
    {
        // Set the intersection color
        current_hit.color = cone->color;

        // Calculate the hit point on the cone
        current_hit.hit_point = vec_addition(ray->origin, mult_vec(ray->direction, current_hit.t));

        // Calculate the unnormalized normal vector
        point_to_apex = sub_vec(current_hit.hit_point, cone->center);
        normal_vector = sub_vec(point_to_apex, mult_vec(axis, (1 + pow(slope, 2.0)) * m));

        // Normalize the normal vector
        current_hit.normal = scale_to_one(normal_vector);

        // Update the closest hit
        closest_hit = current_hit;
    }

    return closest_hit;
}


