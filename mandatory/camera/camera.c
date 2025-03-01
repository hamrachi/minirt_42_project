/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:43:19 by elel-bah          #+#    #+#             */
/*   Updated: 2025/03/01 18:20:13 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

t_cam_matrix	initialize_camera_params(t_world *sc)
{
	t_cam_matrix	cam;

	cam.pos = sc->camera.origin;
	cam.ratio = (double)WIDTH / (double)HEIGHT;
	cam.angle = sc->camera.f_o_v * M_PI / 180.0;
	cam.w = tan(cam.angle / 2);
	cam.h = cam.ratio * cam.w;
	cam.fwd_vec = sc->camera.orientation;
	cam.fwd_vec.x_coord += EPSILON;
	return (cam);
}

t_cam_matrix	set_camera(t_world *sc)
{
	t_cam_matrix	cam;
	t_point3d		ref_world_up;

	cam = initialize_camera_params(sc);
	ref_world_up = create_vector(0.0, -1.0, 0.0);
	cam.up_vec = scale_to_one(cross_product(cam.fwd_vec, ref_world_up));
	cam.right_vec = scale_to_one(cross_product(cam.fwd_vec, cam.up_vec));
	return (cam);
}

t_ray	ray_primary(t_cam_matrix *cam, double v, double u)
{
	t_ray		ray;
	t_point3d	vertical_offset;
	t_point3d	horizontal_offset;
	t_point3d	combine_offset;

	ray.origin = cam->pos;
	vertical_offset = mult_vec(cam->up_vec, v * cam->h);
	horizontal_offset = mult_vec(cam->right_vec, u * cam->w);
	combine_offset = vec_addition(vertical_offset, horizontal_offset);
	ray.direction = vec_addition(combine_offset, cam->fwd_vec);
	ray.direction = scale_to_one(ray.direction);
	return (ray);
}

t_point3d	colorize(double r, double g, double b)
{
	t_point3d	color;

	color.x_coord = r;
	color.y_coord = g;
	color.z_coord = b;
	return (color);
}

t_point3d	ray_at(t_ray *ray, double t)
{
	t_point3d	target;

	target.x_coord = ray->origin.x_coord + t * ray->direction.x_coord;
	target.y_coord = ray->origin.y_coord + t * ray->direction.y_coord;
	target.z_coord = ray->origin.z_coord + t * ray->direction.z_coord;
	return (target);
}
