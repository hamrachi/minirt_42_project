/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:01:11 by elel-bah          #+#    #+#             */
/*   Updated: 2025/03/01 19:27:19 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/* img info struct */

typedef struct s_point3d
{
	double	x_coord;
	double	y_coord;
	double	z_coord;
}	t_point3d;

typedef struct s_canvas
{
	void	*mlx_img;
	char	*pixel_buffer;
	int		color_depth;
	int		stride;
	int		byte_order;
	int		resolution[2];
}	t_canvas;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct s_scene_element
{
	int						type;	
	t_point3d				center;
	t_point3d				direction;
	t_point3d				color;
	t_point3d				param;
	t_point3d				normal;
	struct s_scene_element	*next;
}	t_scene_element;

typedef struct s_inter_data
{
	double		t;
	t_point3d	color;
	t_point3d	hit_point;
	t_point3d	normal;
	int			obj_type;
	int			has_checkerboard;
}	t_inter_data;

typedef struct s_viewport
{
	t_point3d	origin;
	t_point3d	orientation;
	double		f_o_v;
	int			cam_count;
}	t_viewport;

typedef struct s_light_source
{
	t_point3d				position;
	double					brightness;
	t_point3d				light_color;
	struct s_light_source	*next;
}	t_light_source;

typedef struct s_a_light
{
	t_point3d	light_color;
	double		intensity;
	int			light_count;
}	t_a_light;

typedef struct s_world
{
	t_point3d		color;
	t_viewport		camera;
	t_light_source	*light;
	t_a_light		amb_light;
	t_scene_element	*objs;
	int				light_count;
	void			*mlx;
}	t_world;

//garbedge collector

typedef struct s_heap_track
{
	void				*addr;
	struct s_heap_track	*next;
}	t_heap_track;

/* camera */

typedef struct s_cam_matrix
{
	t_point3d		pos;
	t_point3d		up_vec;
	t_point3d		right_vec;
	t_point3d		fwd_vec;
	double			h;
	double			w;
	double			ratio;
	double			angle;
}	t_cam_matrix;

typedef struct ray
{
	t_point3d	origin;
	t_point3d	direction;
}	t_ray;

/* rendring */

typedef struct s_tracer
{
	t_vars			data;
	t_canvas		frame;
	double			vpos;
	double			hpos;
	int				col;
	int				row;
	t_cam_matrix	camera;
	t_ray			path;
	t_point3d		rgb;
}	t_tracer;

// Intersection 

typedef struct s_sph_calc
{
	double		quad_a;
	double		quad_b;
	double		quad_c;
	double		delta;
	double		hit1;
	double		hit2;
	t_point3d	rel_pos;
}	t_sph_calc;

typedef struct s_cyl_calc
{
	double		quad_a;
	double		quad_b;
	double		quad_c;
	double		sel_t;
	double		hit1;
	double		hit2;
	double		delta;
	double		h2;
	double		h1;
	t_point3d	ray_to_center;
	t_point3d	norm_axis;
}	t_cyl_calc;

typedef struct s_ndc
{
	double	u;
	double	v;
}	t_ndc;

#endif