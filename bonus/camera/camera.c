/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:43:19 by elel-bah          #+#    #+#             */
/*   Updated: 2025/01/04 18:57:13 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

t_camera	initialize_camera_params(t_scene *sc)
{
	t_camera	cam;

	cam.orig = sc->cam.cen;
	cam.aspect_r = (double)WIDTH / (double)HEIGHT;
	cam.theta = sc->cam.fov * M_PI / 180.0;
	cam.width = tan(cam.theta / 2);
	cam.height = cam.aspect_r * cam.width;
	cam.forward = sc->cam.dir;
	cam.forward.x += EPSILON;
	return (cam);
}

t_camera	set_camera(t_scene *sc)
{
	t_camera	cam;
	t_vec		ref_world_up;

	// Initialize the camera parameters
	cam = initialize_camera_params(sc);
	// Set ref_axis and calculate up and right vectors

	ref_world_up = create_vector(0.0, -1.0, 0.0);
	cam.up = scale_to_one(cross_product(cam.forward, ref_world_up));
	cam.right = scale_to_one(cross_product(cam.forward, cam.up));
	return (cam);
}

t_ray	ray_primary(t_camera *cam, double v, double u)
{
	t_ray	ray;
	t_vec	vertical_offset;
	t_vec horizontal_offset;
	t_vec combine_offset;

	ray.origin = cam->orig;
	vertical_offset = mult_vec(cam->up, v * cam->height);
	horizontal_offset = mult_vec(cam->right, u * cam->width);
	combine_offset = vec_addition(vertical_offset, horizontal_offset);
	ray.direction = vec_addition(combine_offset, cam->forward);
	ray.direction = scale_to_one(ray.direction);
	return (ray);
}

t_vec	colorize(double r, double g, double b)
{
	t_vec	color;

	color.x = r;
	color.y = g;
	color.z = b;
	return (color);
}

t_vec	ray_at(t_ray *ray, double t)
{
	t_vec	target;

	target.x = ray->origin.x + t * ray->direction.x;
	target.y = ray->origin.y + t * ray->direction.y;
	target.z = ray->origin.z + t * ray->direction.z;
	return (target);
}