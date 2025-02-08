/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:01:11 by elel-bah          #+#    #+#             */
/*   Updated: 2025/01/09 14:52:40 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/* img info struct */


typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int     width;
    int     height;
}	t_img_data;

// Add this to your header file
typedef struct s_texture
{
    int has_checkerboard;
    double checker_size;
    t_vec color2;  // Second color for checkerboard

	// Add image texture support
    int         has_image;
    t_img_data     *image;
    double      scale_u;    // Texture scaling in U direction
    double      scale_v;    // Texture scaling in V direction
} t_texture;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;



typedef struct s_objs
{
	int				type;       // Object type
	t_vec			center;     // Cylinder center
	t_vec			direction;  // Cylinder direction vector
	t_vec			parameters; // Parameters: x=radius, y=height
	t_vec			color;      // Color of the object
	t_vec			normal;     // Normal vector at intersection
	t_vec			p;

	t_texture texture;
	struct s_objs	*next;      // Pointer to the next object
}	t_objs;

typedef struct s_inter
{
	double	t;
	t_vec	color;
	t_vec	hit_point;
	t_vec	normal;

	int         obj_type;
	int has_checkerboard;
	t_texture   texture;
}	t_inter;

typedef struct t_cam
{
	t_vec	cen;
	t_vec	dir;
	double	fov;
	int		count;
}	t_cam;

typedef struct s_light
{
	t_vec			src;
	double			ratio;
	t_vec			col;
	struct s_light	*next;
}	t_light;

typedef struct s_amb
{
	t_vec	col;
	double	ratio;
	int		count;
}	t_amb;




// typedef struct s_objs
// {
// 	int				type;
// 	t_vec			cen;
// 	t_vec			dir;
// 	t_vec			p;
// 	t_vec			col;
// 	t_vec			norm;
// 	struct s_objs	*next;
// }	t_objs;

typedef struct s_scene
{
	t_vec	col;
	t_cam	cam;
	t_light	*light;
	t_amb	amb;
	t_objs	*objs;

	int light_count; // Tracks the number of spotlights in the scene

	void *mlx;
}	t_scene;

typedef struct collector
{
	void				*adr;
	struct collector	*next;
}	t_collector;

/* camera */
typedef struct Camera_Setup
{
	t_vec		orig;
	t_vec		up;
	t_vec		right;
	t_vec		forward;
	double		height;
	double		width;
	double		aspect_r;
	double		theta;
}	t_camera;

typedef struct ray
{
	t_vec	origin;
	t_vec	direction;
}	t_ray;

/* rendring */
typedef struct render
{
	t_vars		vars;
	t_img_data	img;
	double		v;
	double		u;
	int			x;
	int			y;
	t_camera	cam;
	t_ray	ray_;
	t_vec		ray_col;
}	t_render;

// Intersection 

typedef struct sphere
{
	double	a;
	double	b;
	double	c;
	double	discri;
	double	t1;
	double	t2;
	t_vec	oc;
}	t_sphere;

//=-=-=-=

typedef struct cylinder
{
	double	quad_a;      // Quadratic equation coefficient a
	double	quad_b;      // Quadratic equation coefficient b
	double	quad_c;      // Quadratic equation coefficient c
	double	chosen_t;       // Selected t (intersection distance)
	double	t1;  // First t value from quadratic equation
	double	t2;  // Second t value from quadratic equation
	double	discri;      // Discriminant of the quadratic equation
	double	height_t2;      // Height at t2 along cylinder axis
	double	height_t1;      // Height at t1 along cylinder axis
	t_vec	ray_to_center;   // Vector from ray origin to cylinder center
	t_vec	axis;     // Normalized cylinder axis vector
}	t_cylinder;

typedef struct cone
{
    double a;                   // Quadratic coefficient for t^2
    double b;                   // Quadratic coefficient for t
    double c;                   // Quadratic constant term
    double discriminant;        // Discriminant of the quadratic equation
    double t_closest;           // Closest valid intersection (t)
    double t_near;              // Near intersection point (t1)
    double t_far;               // Far intersection point (t2)
    double y_far;               // y-coordinate of the far intersection point
    double y_near;              // y-coordinate of the near intersection point
    t_vec origin_to_cone;       // Vector from ray origin to cone center
    t_vec axis;                 // Normalized direction of the cone's axis
    double slope;               // Slope of the cone (tan(angle/2))


	
	t_vec center;
	t_vec direction;
} t_cone_info;

// typedef struct ray_tracing
// {
//     t_vec origin;
//     t_vec direction;
// } t_raytracing;

//==-=-=-

// typedef struct cylinder
// {
// 	double	a;
// 	double	b;
// 	double	c;
// 	double	t;
// 	double	t1;
// 	double	t2;
// 	double	delta;
// 	double	y0;
// 	double	y1;
// 	t_vec	oc;
// 	t_vec	normal;
// }	t_cylinder;

// typedef struct cone//BONUS
// {
// 	double	a;
// 	double	b;
// 	double	c;
// 	double	delta;
// 	double	t;
// 	double	t1;
// 	double	t2;
// 	double	y0;
// 	double	y1;
// 	t_vec	x;
// 	t_vec	v;
// 	double	k;
// }	t_cone_info;

//=-=-=-=-=-

typedef struct s_thread_info
{
    int thread_id;
    int rows_per_thread;
    t_scene *scene;
    t_render *render_info;
} t_thread_info;

typedef struct s_thread_data 
{
    int thread_id;      // ID of the thread
    int start_row;      // Starting row for this thread
    int end_row;        // Ending row for this thread
    t_scene *scene;     // Pointer to the scene
    t_render *info;     // Pointer to the rendering information

    pthread_mutex_t render_mutex;
	
} t_thread_data;

typedef struct s_ssaa_config 
{
	int		samples_per_side;
	double	subpixel_step;
	double	inv_total_samples;
	int		total_samples;
}	t_ssaa_config;

typedef struct s_ray_trace_context
{
	int				x;
	int				y;
	int				sx;
	int				sy;
	t_ssaa_config	*config;
	t_camera		*cam;
	t_scene			*scene;
}	t_ray_trace_context;

typedef struct s_ray_params
{
	double	u;
	double	v;
	double	offset_u;
	double	offset_v;
}	t_ray_params;

typedef struct s_ndc
{
    double u;
    double v;
} t_ndc;
//=-=-=-=-=-

#endif
