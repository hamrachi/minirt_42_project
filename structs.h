/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:01:11 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/01 11:40:39 by elel-bah         ###   ########.fr       */
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
    void    *mlx_img;           // More descriptive name than 'img'
    char    *pixel_buffer;      // More descriptive than 'addr'
    int     color_depth;        // Instead of bits_per_pixel
    int     stride;             // Instead of line_length (common graphics term)
    int     byte_order;         // Instead of endian (more descriptive)
    int     resolution[2];      // Combines width and height into an array
}   t_canvas;


// // Add this to your header file
// typedef struct s_texture
// {
//     int has_checkerboard;
//     double checker_size;
//     t_point3d color2;  // Second color for checkerboard

// 	// Add image texture support
//     int         has_image;
//     t_canvas    *image;
//     double      scale_u;    // Texture scaling in U direction
//     double      scale_v;    // Texture scaling in V direction
// } t_texture;

typedef struct s_vars //need tototototototototo
{
	void	*mlx;
	void	*win;
}				t_vars;



typedef struct s_scene_element 
{
	int					type;       // Object type
	// t_texture 			texture;
	t_point3d			center;     // Cylinder center
	t_point3d			direction;  // Cylinder direction vector
	t_point3d			color;      // Color of the object
	t_point3d			param; // Parameters: x=radius, y=height
	t_point3d			normal;     // Normal vector at intersection
	struct s_scene_element	*next;      // Pointer to the next object
}	t_scene_element;

typedef struct s_inter_data
{
	double		t;
	t_point3d	color;
	t_point3d	hit_point;
	t_point3d	normal;

	int         obj_type;
	int 			has_checkerboard;
	// t_texture   texture;
}	t_inter_data;

typedef struct s_viewport
{
	t_point3d	origin;
	t_point3d	orientation;
	double	f_o_v;
	int		cam_count;
}	t_viewport;

typedef struct s_light_source
{
    t_point3d            position;       // Instead of 'src' - light position
    double              brightness;      // Instead of 'ratio' - more intuitive
    t_point3d            light_color;    // Instead of 'col' - more descriptive
    struct s_light_source   *next;       // Keep linked list functionality
}   t_light_source;


typedef struct s_a_light
{
	t_point3d   light_color;    // Instead of 'col' - more descriptive
    double      intensity;      // Instead of 'ratio' - common lighting term
    int         light_count;    // Instead of 'count' - clearer purpose
}	t_a_light;



typedef struct s_world
{
	t_point3d	color;
	t_viewport	camera;
	t_light_source	*light;
	t_a_light	amb_light;
	t_scene_element	*objs;

	int light_count; // Tracks the number of spotlights in the scene

	void *mlx;
}	t_world;

//=-=-=-=-=-
//garbedge collector

typedef struct s_heap_track
{
    void               	*addr;    // Memory address
    struct s_heap_track	*next;   // Next tracked address
}   t_heap_track;


/* camera */

typedef struct s_cam_matrix
{
    t_point3d    pos;        // Instead of 'orig'
    t_point3d    up_vec;     // Instead of 'up'
    t_point3d    right_vec;  // Instead of 'right'
    t_point3d    fwd_vec;    // Instead of 'forward'
    double      h;          // Instead of 'height'
    double      w;          // Instead of 'width'
    double      ratio;      // Instead of 'aspect_r'
    double      angle;      // Instead of 'theta'
}   t_cam_matrix;

typedef struct ray
{
	t_point3d	origin;
	t_point3d	direction;
}	t_ray;

/* rendring */

typedef struct s_tracer
{
    t_vars          data;       // "vars" Core variables
    t_canvas        frame;      // "img"Frame buffer
    double          vpos;       // "v" Vertical position
    double          hpos;       // "u" Horizontal position
    int             col;        // "x" Column index
    int             row;        // "y" Row index
    t_cam_matrix    camera;        // Camera setup
    t_ray           path;       // "Ray" path
    t_point3d       rgb;        // "ray_color" Pixel color
}   t_tracer;

// Intersection 


typedef struct s_sph_calc
{
    double      quad_a;     // Instead of 'a' - quadratic a term
    double      quad_b;     // Instead of 'b' - quadratic b term
    double      quad_c;     // Instead of 'c' - quadratic c term
    double      delta;      // Instead of 'discri' (discriminant)
    double      hit1;       // Instead of 't1' - first intersection
    double      hit2;       // Instead of 't2' - second intersection
    t_point3d   rel_pos;    // Instead of 'oc' (origin to center vector)
}   t_sph_calc;


typedef struct s_cyl_calc
{
    double      quad_a;        // First coefficient
    double      quad_b;        // Second coefficient
    double      quad_c;        // Third coefficient
    double      sel_t;         // Selected intersection
    double      hit1;          // First intersection
    double      hit2;          // Second intersection
    double      delta;         // Discriminant
    double      h2;            // Height at hit2
    double      h1;            // Height at hit1
    t_point3d   ray_to_center;       // Relative position vector
    t_point3d   norm_axis;     // Normalized direction
}   t_cyl_calc;

typedef struct s_ndc
{
    double u;
    double v;
} t_ndc;
//=-=-=-=-=-

#endif
