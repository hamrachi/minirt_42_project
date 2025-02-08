/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_code_mandatory.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:01:11 by elel-bah          #+#    #+#             */
/*   Updated: 2025/01/09 11:35:56 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//miniRT.h

#ifndef MINIRT_H
# define MINIRT_H

# define BUFFER_SIZE 32

# define HEIGHT 800
# define WIDTH 800
# define EPSILON 0.000001
# define CYLINDER 1
# define PLAN 2
# define SPHERE 3

#include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "structs.h"

#define NUM_THREADS 4

//parse_utils

void validate_camera_input(char **args, t_scene *scene);
void validate_camera_orientation(t_vec dir);
void validate_camera_fov(double fov);

// void validate_light_input(char **args, t_scene *scene);
void validate_light_input(char **args);
void validate_light_ratio(double ratio);
void validate_plane_input(char **args);
void validate_plane_orientation(t_vec dir);
void validate_color_input(char **args);
void validate_color_range(t_vec color);
void validate_vec_input(char **args);
void validate_sphere_input(char **args);
void validate_sphere_diameter(double diameter);
void validate_cylinder_input(char **args);
void validate_cylinder_orientation(t_vec dir);
void validate_ambient_ratio_range(double ratio);
void validate_ambient_input(char **args, t_scene *scene);
void validate_cylinder_diameter(double diameter, double height);

// parse
void        report_error(char *str);
int			is_valid_rt_file(int ac, char **av);
void        parse_scene_file(t_scene *sc, int fd);//
void        parse_object(char *object_type, char **tokens, t_scene *scene);//new
void		parse_plane(t_scene *sc, char **tockens);
void		parse_cylinder(t_scene *sc, char **tockens);
void		parse_sphere(t_scene *sc, char **tockens);
void		parse_light(t_scene *sc, char **tockens);
void		parse_camera(t_scene *sc, char **tockens);
void		parse_ambient(t_scene *sc, char **tockens);

// allocation

// Garbage collector functions

// Allocation functions
t_scene *allocate_scene(void);
t_objs *allocate_object(t_scene *scene);
void gc_cleanup(t_collector **garbage_collector, t_collector *collector_node);
void *gc_malloc(t_collector **garbage_collector, size_t size);
t_collector **create_and_append(t_collector **garbage_collector, void *allocated_memory);
// t_collector *create_collector_node(void *allocated_memory);
// t_collector **append_to_collector(t_collector **garbage_collector, void *allocated_memory);
t_collector	*garbage_collector;

// tools
int			ft_strlen(const char *str);
char        *append_char_to_string(char *original, char new_char);
char	    *line(int fd);
double		ft_atod(const char *str);
int			ft_atoi(const char *str);
char		**ft_split(const char *str, char c);
void		free_split(char **s);
int	        ft_strncmp(char *s1, const char *s2, size_t n);
int         ft_strcmp(const char *str1, const char *str2);

/* camera */
t_camera	set_camera(t_scene *sc);
t_ray	ray_primary(t_camera *cam, double v, double u);
t_vec		ray_at(t_ray *ray, double t);
t_vec		ray_at(t_ray *ray, double t);
//vectors
void		reset_vec(t_vec *v);
t_vec		get_vec(char *s);
t_vec		get_color(char *s);
t_vec		scale_to_one(t_vec v);
t_vec		sub_vec(t_vec u, t_vec v);
t_vec	vec_addition(t_vec v1, t_vec v2);
t_vec		mult_vec(t_vec v, double a);
t_vec		cross_product(t_vec v1, t_vec v2);//
double		dot_product(t_vec u, t_vec v);
double		magnitude(t_vec	v);
t_vec		div_vect(t_vec v, double a);
t_vec		create_vector(double x, double y, double z);



/* intersections*/
double		take_min(double x, double y);

t_inter	find_closest_intersection(t_ray *ray, t_scene *scene);


t_inter calc_sphere_normal(t_inter current_hit, t_objs *sphere, t_ray *ray);
// t_inter calculate_sphere_intersection(t_inter current_closest, t_objs *sphere, t_ray *ray);


double calc_sp_ray_inter(t_ray *ray, t_objs *sphere);
// double	sphere_intersection(t_ray *ray, t_objs *sphere);

double      calculate_plane_intersection(t_ray *ray, t_objs *plane);

double      find_cylinder_intersection(t_ray *ray, t_objs *cylinder);
// double intersect_cylinder(t_ray *ray, t_objs *cylinder);

double      calculate_cylinder_intersection(t_cylinder cylinder_calc, t_ray *ray, t_objs *cylinder);
t_inter calc_cylinder_normal(t_inter closest_hit, t_objs *cylinder, t_ray *ray);
// double  pick_cylinder_intersection(t_cylinder cyl_info, t_ray *ray, t_objs *cylinder);

t_inter calc_plan_normal(t_inter closest_hit, t_objs *plane, t_ray *ray);


/* mlx funct */
int			cross_button(t_vars *vars);
int			handle_key(int key, t_vars *vars);
void		my_mlx_pixel_put(t_img_data *data, int x, int y, int color);
void	image_init(t_render	*info);

// color
t_vec       scale_and_combine_colors(t_vec base_color, t_vec light_color, double intensity_ratio);
int			create_rgb(int r, int g, int b);
t_vec       blend_colors(t_vec color_a, t_vec color_b);
t_vec		ray_color(t_ray *ray, t_scene *sc);
t_vec		colorize(double r, double g, double b);
t_vec		diffuse(t_inter inter, t_light *light, double d);

int         is_point_in_shadow(t_scene *scene, t_inter intersection, t_light *light_source);

//surface normal
int			ray_is_inside(t_vec ray, t_vec s_norm);
double      calc_pl_ray_inter(t_ray *ray, t_objs *plane);
t_inter     find_closest_intersection(t_ray *ray, t_scene *scene);


//=-=-=--=Draw
/*rendring */
void		ft_render(t_scene *sc);
void ft_draw(t_render info, t_scene *sc);
void	*render_section(void *arg);


#endif

//struct.h

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

//=-=-=-=-=-

#endif

//functions of parsing:

//parsing.c

void parse_plane(t_scene *scene, char **args)//new
{
    t_objs *obj;

    // Validate plane input (args and count)
    validate_plane_input(args);
    // Allocate memory for the new plane object
    obj = allocate_object(scene);
    obj->type = PLAN;
    // Set plane center and direction
    obj->center = get_vec(args[1]);
    obj->direction = get_vec(args[2]);
    // Validate plane orientation
    validate_plane_orientation(obj->direction);
    // Set the plane color
    obj->color = get_color(args[3]);
}

//==

t_vec get_color(char *str)//new
{
    char **args;
    t_vec color;

    // Split the input string into R, G, B components
    args = ft_split(str, ',');
    // Validate color input format
    validate_color_input(args);
    // Convert the split string values to integers and store in a vector
    color = (t_vec){ft_atoi(args[0]), ft_atoi(args[1]), ft_atoi(args[2])};
    // Validate the range of the color values
    validate_color_range(color);
    // Free the split string array
    free_split(args);
    return color;
}

t_vec	get_vec(char *s)
{
	char	**args;
	t_vec	cord;

	args = ft_split(s, ',');
	validate_vec_input(args);
	cord = create_vector(ft_atod(args[0]), ft_atod(args[1]), ft_atod(args[2]));
	free_split(args);
	return (cord);
}


//==-=-=--==-=-=-

void parse_scene_element(char element_type, t_scene *scene, char **tokens)
{
    if (element_type == 'A')
        parse_ambient(scene, tokens);
    else if (element_type == 'C')
        parse_camera(scene, tokens);
    else if (element_type == 'l')
        parse_light(scene, tokens);
    else
        report_error("invalid scene element");
}

void parse_scene_shape(const char *shape_type, t_scene *scene, char **tokens)
{
    if (ft_strcmp(shape_type, "sp") == 0)
        parse_sphere(scene, tokens);
    else if (ft_strcmp(shape_type, "pl") == 0)
        parse_plane(scene, tokens);
    else if (ft_strcmp(shape_type, "cy") == 0)
        parse_cylinder(scene, tokens);
    else
        report_error("invalid scene shape");
}

void parse_object(char *object_type, char **tokens, t_scene *scene)
{
    if ((object_type[0] == 'A' && object_type[1] == '\0') ||
        (object_type[0] == 'C' && object_type[1] == '\0') ||
        (object_type[0] == 'l' && object_type[1] == '\0'))
    {
        parse_scene_element(object_type[0], scene, tokens);
    }
    else if ((ft_strcmp(object_type, "sp") == 0) ||
             (ft_strcmp(object_type, "pl") == 0) ||
             (ft_strcmp(object_type, "cy") == 0))
    {
        parse_scene_shape(object_type, scene, tokens);
    }
    else
    {
        report_error("invalid object type");
    }
}

void process_scene_line(char **tokens, t_scene *sc)
{
    if (*tokens)
        parse_object(*tokens, tokens, sc);
}

void parse_scene_file(t_scene *sc, int fd)
{
    char **tokens;

    while (1)
    {
        tokens = ft_split(line(fd), ' ');
        
        if (tokens == NULL)
            break;

        process_scene_line(tokens, sc);
        
        free_split(tokens);
    }

    close(fd);
}

//parsing1.c

t_light	*alloc_light(t_scene *sc)
{
	t_light	*new_light;

	new_light = malloc(sizeof(t_light));
	if (!new_light)
        report_error("allocation failed\n");
	new_light->next = sc->light;
	sc->light = new_light;
	return (new_light);
}

void parse_light(t_scene *scene, char **args)
{
    t_light *new;

    // Check if a light already exists in the scene
    if (scene->light != NULL)
        report_error("Only one spotlight is allowed.");

    // Validate light input (args and count)
    validate_light_input(args);
    // validate_light_input(args, scene);

    // Allocate memory for the new light object
    new = alloc_light(scene);

    // Set the light source vector and validate the ratio
    new->src = get_vec(args[1]);
    new->ratio = ft_atod(args[2]);
    validate_light_ratio(new->ratio);

    // Set the color of the light
    new->col = get_color(args[3]);
}
void parse_camera(t_scene *scene, char **args)//new__
{
    // Validate camera input (args and count)
    validate_camera_input(args, scene);
    // Increment camera count
    scene->cam.count++;
    // Set camera center and direction vectors
    scene->cam.cen = get_vec(args[1]);
    scene->cam.dir = get_vec(args[2]);
    // Validate camera orientation
    validate_camera_orientation(scene->cam.dir);
    // Set and validate the camera FOV
    scene->cam.fov = ft_atod(args[3]);
    validate_camera_fov(scene->cam.fov);
}

// Main function to parse ambient lighting
void parse_ambient(t_scene *scene, char **args)//new
{
    // Validate ambient parameters (tokens and count)
    validate_ambient_input(args, scene);
    // Increment ambient count
    scene->amb.count++;
    // Set ambient lighting ratio
    scene->amb.ratio = ft_atod(args[1]);
    // Validate the ambient lighting ratio
    validate_ambient_ratio_range(scene->amb.ratio);
    // Set the color for ambient lighting
    scene->amb.col = get_color(args[2]);
}

void parse_cylinder(t_scene *scene, char **args)//new
{
    t_objs *obj;

    // Validate cylinder input (args and count)
    validate_cylinder_input(args);
    // Allocate memory for the new cylinder object
    obj = allocate_object(scene);
    obj->type = CYLINDER;
    // Set cylinder center and direction
    obj->center = get_vec(args[1]);
    obj->direction = get_vec(args[2]);
    // Validate cylinder orientation
    validate_cylinder_orientation(obj->direction);
    // Set cylinder diameter and height
    obj->p.x = ft_atod(args[3]);
    obj->p.y = ft_atod(args[4]);
    // Validate cylinder diameter and height
    validate_cylinder_diameter(obj->p.x, obj->p.y);
    // Set the cylinder color
    obj->color = get_color(args[5]);
}

void parse_sphere(t_scene *scene, char **args)//new
{
    t_objs *obj;

    // Validate sphere input (args and count)
    validate_sphere_input(args);
    // Allocate memory for the new sphere object
    obj = allocate_object(scene);
    obj->type = SPHERE;
    // Set sphere center and validate the diameter
    obj->center = get_vec(args[1]);
    obj->p.x = ft_atod(args[2]);
    // Validate the sphere diameter
    validate_sphere_diameter(obj->p.x);

    // Set the sphere color
    obj->color = get_color(args[3]);
}

//parsing_utils.c

// Helper function to validate camera parameters (args and count)
void validate_camera_input(char **args, t_scene *scene)
{
    if (!args || !args[1] || !args[2] || !args[3] || args[4])
        report_error("Invalid camera arguments.");
    if (scene->cam.count != 0)
        report_error("Only one camera is allowed.");
}

// Helper function to validate camera direction (orientation)
void validate_camera_orientation(t_vec dir)
{
    if (dir.x > 1 || dir.y > 1 || dir.z > 1)
        report_error("Camera direction components must be between -1 and 1.");
    if (dir.x < -1 || dir.y < -1 || dir.z < -1)
        report_error("Camera orientation cannot be a zero vector (0, 0, 0).");
    if (dir.x == 0 && dir.y == 0 && dir.z == 0)
        report_error("FOV must lie within the range [0, 180]");
}

// Helper function to validate camera FOV (field of view)
void validate_camera_fov(double fov)
{
    if (fov < 0 || fov > 180)
        report_error("FOV must be in the range [0, 180].");
}

// Helper function to validate light parameters (args and count)
void validate_light_input(char **args)
{
    if (!args || !args[1] || !args[2] || !args[3] || args[4])
        report_error("Light parameters are invalid.");
}

// Helper function to validate light brightness ratio
void validate_light_ratio(double ratio)
{
    if (ratio < 0 || ratio > 1)
        report_error("Light brightness ratio must lie between 0.0 and 1.0.");
}
//parsing_utils1:

// Helper function to validate plane input (args and count)
void validate_plane_input(char **args)
{
    if (!args || !args[1] || !args[2] || !args[3] || args[4])
        report_error("Invalid plane arguments.");
}

// Helper function to validate the plane orientation
void validate_plane_orientation(t_vec dir)
{
    if (dir.x > 1 || dir.y > 1 || dir.z > 1 || \
			dir.x < -1 || dir.y < -1 || dir.z < -1)
        report_error("Plane direction components must be between -1 and 1.");
}

//parsing_utils2.c

// Helper function to validate the color parameters (input format)
void validate_color_input(char **args)
{
    if (!args || !args[1] || !args[2] || args[3])
        report_error("Invalid color format! Expected R,G,B.");
}

// Helper function to validate the color range
void validate_color_range(t_vec color)
{
    if (color.x < 0 || color.y < 0 || color.z < 0 || 
        color.x > 255 || color.y > 255 || color.z > 255)
        report_error("Color values must be in the range [0, 255].");
}

//========

void validate_vec_input(char **args)
{
    if (!args || !args[1] || !args[2] || args[3])
        report_error("Invalid vector format! Expected X,Y,Z.");
}
//=-=-=-

// Helper function to validate sphere input (args and count)
void validate_sphere_input(char **args)
{
    if (!args || !args[1] || !args[2] || !args[3] || args[4])
        report_error("Sphere parameters are invalid.");
}

// Helper function to validate the sphere diameter
void validate_sphere_diameter(double diameter)
{
    if (diameter <= 0)
        report_error("Invalid sphere diameter: must be positive.");
}
//=========

// Helper function to validate cylinder input (args and count)
void validate_cylinder_input(char **args)
{
    if (!args || !args[1] || !args[2] || !args[3] || \
			!args[4] || !args[5] || args[6])
        report_error("Invalid cylinder arguments.");
}

// Helper function to validate the cylinder orientation
void validate_cylinder_orientation(t_vec dir)
{
    if (dir.x > 1 || dir.y > 1 || dir.z > 1 || \
			dir.x < -1 || dir.y < -1 || dir.z < -1)
        report_error("Cylinder direction components must be between -1 and 1.");
}

//parsing_utils3.c:

// Helper function to validate the ambient lighting ratio
void validate_ambient_ratio_range(double ratio)
{
    if (ratio < 0 || ratio > 1)
        report_error("Ambient lighting ratio should be between 0.0 and 1.0.");
}

// Helper function to validate ambient parameters (tokens and count)
void validate_ambient_input(char **args, t_scene *scene)
{
    // Check if tokens are valid (must have at least 3 elements, no more than 3)
    if (!args || !args[1] || !args[2] || args[3])
        report_error("Ambient lighting parameters are invalid!");
    // Check if ambient count is already set
    if (scene->amb.count != 0)
        report_error("There can be only one ambient light source.");
}
// Helper function to validate the cylinder diameter
void validate_cylinder_diameter(double diameter, double height)
{
    if (diameter <= 0 || height <= 0)
        report_error("Cylinder diameter and height must both be positive.");
}
// camere/camera.c:

t_camera	initialize_camera_params(t_scene *sc)
{
	t_camera	cam;

	cam.orig = sc->cam.cen;
	cam.aspect_r = (double)WIDTH / (double)HEIGHT;
	cam.theta = sc->cam.fov * M_PI / 180.0;//convert to radian
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

//the code of /colors/colors.c:

t_vec compute_lighting(t_scene *scene, t_inter intersection, t_vec ambient_color)
{
    t_light     *current_light;
    t_vec       final_color;
    t_vec       light_direction;
    double      diffuse_factor;

    final_color = create_vector(0, 0, 0);
    current_light = scene->light;
    if (!current_light)
        return (ambient_color);

    if (is_point_in_shadow(scene, intersection, current_light))
        final_color = blend_colors(final_color, ambient_color);
    else
    {
        light_direction = sub_vec(current_light->src, intersection.hit_point);
        diffuse_factor = dot_product(scale_to_one(light_direction), intersection.normal);
        final_color = blend_colors(final_color, ambient_color);
        if (diffuse_factor > 0)
            final_color = blend_colors(final_color, diffuse(intersection, current_light, diffuse_factor));
    }
    return (final_color);
}


t_vec  scale_and_combine_colors(t_vec base_color, t_vec light_color, double intensity_ratio)
{
    t_vec result_color;

    result_color.x = base_color.x * (light_color.x / 255) * intensity_ratio;
    result_color.y = base_color.y * (light_color.y / 255) * intensity_ratio;
    result_color.z = base_color.z * (light_color.z / 255) * intensity_ratio;

    return (result_color);
}


t_vec blend_colors(t_vec color_a, t_vec color_b)
{
    t_vec blended_color;

    blended_color = vec_addition(color_a, color_b);
    if (blended_color.x > 255)
        blended_color.x = 255;
    if (blended_color.y > 255)
        blended_color.y = 255;
    if (blended_color.z > 255)
        blended_color.z = 255;

    return (blended_color);
}

t_vec	ray_color(t_ray *ray, t_scene *sc)
{
	t_inter	inter;
	t_vec	px_col;
	t_vec	amb;

	inter = find_closest_intersection(ray, sc);
	if (inter.t > EPSILON)
	{
		amb = scale_and_combine_colors(inter.color, sc->amb.col, sc->amb.ratio);
		if (ray_is_inside(ray->direction, inter.normal))
			inter.normal = mult_vec(inter.normal, -1);
		px_col = compute_lighting(sc, inter, amb);
		return (px_col);
	}
	return (mult_vec(sc->amb.col, sc->amb.ratio));
}

int	create_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

//the code of /garbedge_collector/allocation.c:

void	report_error(char *str)
{
	int	i;

	i = -1;
    write(2, "Error: ", 7);
	while (str[++i])
		write(2, &str[i], 1);
    write(2, "\n", 1);
    gc_cleanup(&garbage_collector, garbage_collector);
	exit(1);
}

// Allocate scene

void initialize_scene_fields(t_scene *scene)
{
    scene->objs = NULL;
    scene->amb.count = 0;
    scene->cam.count = 0;
    scene->light = NULL;
}
t_scene *allocate_scene(void)//t+world
{
    t_scene *scene;

    garbage_collector = NULL;
    scene = gc_malloc(&garbage_collector, sizeof(t_scene));
    if (!scene)
        return (NULL);
    initialize_scene_fields(scene);
    return (scene);
}

// Allocate object

void init_object_vec(t_objs *object)
{
    reset_vec(&(object->color));
    reset_vec(&(object->center));
    reset_vec(&(object->direction));
    reset_vec(&(object->p));//
}

t_objs *allocate_object(t_scene *scene)
{
    t_objs *new_object;

    new_object = gc_malloc(&garbage_collector, sizeof(t_objs));
    if (!new_object)
        return (NULL);
    init_object_vec(new_object);
    new_object->next = scene->objs;
    scene->objs = new_object;
    return (new_object);
}
//the code garbege_collector/garbdge.c

t_collector **create_and_append(t_collector **garbage_collector, void *allocated_memory)
{
    t_collector *new_node;
    t_collector *temp;

    // Create a new collector node
    new_node = malloc(sizeof(t_collector));
    if (!new_node)
        return (NULL);
    new_node->adr = allocated_memory;
    new_node->next = NULL;
    // Append the node to the linked list
    if (!*garbage_collector)
        return (*garbage_collector = new_node, garbage_collector);
    temp = *garbage_collector;
    while (temp->next)
        temp = temp->next;
    temp->next = new_node;

    return (garbage_collector);
}
// Memory allocation with garbage collector tracking
void *gc_malloc(t_collector **garbage_collector, size_t size)
{
    void *allocated_memory;

    allocated_memory = malloc(size);
    if (!allocated_memory)
        return (NULL);
    return (create_and_append(garbage_collector, allocated_memory), allocated_memory);
}

// Cleanup all memory tracked by the garbage collector
void gc_cleanup(t_collector **garbage_collector, t_collector *collector_node)
{
    if (!collector_node)
        return;
    gc_cleanup(garbage_collector, collector_node->next);
    free(collector_node->adr);
    free(collector_node);
}
//the code of /gnl/line.c

char *append_char_to_string(char *original, char new_char)
{
    char *new_str;  
    size_t  i;        // Pointer for the resulting string.
    size_t original_len; // Length of the original string.

    original_len = 0;
    // Calculate the length of the original string.
    if (original)
        while (original[original_len])
            original_len++;
    // Allocate memory for the new string (1 for the new char and 1 for the null terminator).
    new_str = malloc((original_len + 2) * sizeof(char));
    if (!new_str)
        return (NULL);
    // Copy the original string into the new string.
    for (i = 0; i < original_len; i++)
        new_str[i] = original[i];
    // Add the new character and null terminator.
    new_str[original_len] = new_char;
    new_str[original_len + 1] = '\0';
    // Free the old string and return the new one.
    free(original);
    return (new_str);
}

char *line(int fd)
{
    char c;                    // Temporary storage for the character read.
    static char *line;  // Static to preserve the line between function calls.

    line = NULL;
    // Free the previous line if it exists.
    if (line)
    {
        free(line);
        line = NULL;
    }
    // Read characters one by one from the file descriptor.
    while (read(fd, &c, 1))
    {
        // Skip over newline characters if `line` is still NULL.
        if (c == '\n' && line == NULL)
            continue;
        // Stop reading upon encountering a newline (excluding the first one).
        if (c == '\n')
        {
            if (line && line[0] == '#')
            {
                free(line);
                line = NULL;
                continue;
            }
            break;
        }
        // Append the character to the line.
        line = append_char_to_string(line, c);
        if (!line) // Handle memory allocation failure.
            return (NULL);
    }
    // Return the constructed line (or NULL if nothing was read).
    return (line);
}

//the code of /mlx/mlx_functions.c:

void	image_init(t_render	*info)
{
	info->vars.mlx = mlx_init();
	info->vars.win = mlx_new_window(info->vars.mlx, WIDTH, HEIGHT, "MiniRT");
	info->img.img = mlx_new_image(info->vars.mlx, WIDTH, HEIGHT);
	info->img.addr = mlx_get_data_addr(info->img.img, &info->img.bits_per_pixel,
			&info->img.line_length, &info->img.endian);
}

void	my_mlx_pixel_put(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	handle_key(int key, t_vars *vars)
{
	if (key == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int	cross_button(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}
//the function of objects_intersections/intersection.c:

t_inter	find_closest_intersection(t_ray *ray, t_scene *scene)//without else
{
	t_inter	closest_inter; // Holds the closest intersection details
	t_objs	*current_obj;      // Pointer to traverse the objects in the scene

	closest_inter.t = -1.0; // Initialize to no intersection
	current_obj = scene->objs; // Start with the first object in the scene

	while (current_obj) // Loop through all objects in the scene
	{
		// Check the type of the current object and find intersections accordingly
		if (current_obj->type == SPHERE)
			closest_inter = calc_sphere_normal(closest_inter, current_obj, ray);
		if (current_obj->type == PLAN)
			closest_inter = calc_plan_normal(closest_inter, current_obj, ray);
		if (current_obj->type == CYLINDER)
			closest_inter =  calc_cylinder_normal(closest_inter, current_obj, ray);

		// Move to the next object in the linked list
		current_obj = current_obj->next;
	}

	return closest_inter; // Return the closest intersection found
}

//the function of objects_intersections/sphere.c:

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

//the function of objects_intersections/plane.c:

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
        if (dot_product(ray->direction, current_hit.normal) < EPSILON)
        {
            current_hit.normal = scale_to_one(
                                    mult_vec(plane->direction, -1));
        }
        // Update the closest intersection with this plane
        closest_hit = current_hit;
    }
    return (closest_hit);
}

//the function of objects_intersections/cylinder.c:

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

//the function of raytracing/ft_render.c:

typedef struct s_ndc
{
    double u;
    double v;
} t_ndc;

// Calculate normalized device coordinates (NDC) for a pixel
t_ndc calculate_ndc(int x, int y)
{
    t_ndc coords;
    
    coords.v = (double)x * 2 / WIDTH - 1;
    coords.u = (double)y * 2 / HEIGHT - 1;
    return (coords);
}

// Process a single pixel and return its color
t_vec process_pixel(t_render *info, t_scene *sc, int x, int y)
{
    t_ndc   coords;
    t_ray   primary_ray;
    t_vec   pixel_color;
    
    coords = calculate_ndc(x, y);
    primary_ray = ray_primary(&info->cam, coords.v, coords.u);
    pixel_color = ray_color(&primary_ray, sc);
    return (pixel_color);
}

// Draw a single row of pixels
void draw_row(t_render *info, t_scene *sc, int y)
{
    int     x;
    t_vec   pixel_color;
    
    x = 0;
    while (x < WIDTH)
    {
        pixel_color = process_pixel(info, sc, x, y);
        my_mlx_pixel_put(&info->img, x, HEIGHT - 1 - y,
            create_rgb(pixel_color.x, pixel_color.y, pixel_color.z));
        x++;
    }
}

// Main drawing function
void ft_draw(t_render info, t_scene *sc)
{
    int y;
    
    y = HEIGHT - 1;
    while (y >= 0)
    {
        draw_row(&info, sc, y);
        y--;
    }
}

void	ft_render(t_scene *sc)
{
	t_render	info;

	info.cam = set_camera(sc);
	image_init(&info);
	ft_draw(info, sc);
	mlx_put_image_to_window(info.vars.mlx, info.vars.win, info.img.img, 0, 0);
	mlx_key_hook(info.vars.win, handle_key, &info.vars);
	mlx_hook(info.vars.win, 17, 0, cross_button, &info.vars);
	mlx_loop(info.vars.mlx);
}
//the function of shadow/shadow.c:

int	ray_is_inside(t_vec ray, t_vec s_norm)
{
	if (dot_product(ray, s_norm) > 0)
		return (1);
	return (0);
}

int	is_point_in_shadow(t_scene *scene, t_inter intersection, t_light *light_source)
{ 
	t_vec		vector_to_light;
	t_ray		shadow_ray;
	t_inter		shadow_hit;
	t_vec		vector_to_shadow_hit;

	// Calculate the vector from the intersection point to the light source
	vector_to_light = sub_vec(light_source->src, intersection.hit_point);
	// Configure the shadow ray with its origin at the intersection point and direction toward the light source
	shadow_ray.origin = intersection.hit_point;
	shadow_ray.direction = scale_to_one(vector_to_light);
	// Find the closest object intersected by the shadow ray
	shadow_hit = find_closest_intersection(&shadow_ray, scene);
	// Calculate the vector from the shadow ray's origin to the point of intersection (if any)
	vector_to_shadow_hit = sub_vec(shadow_hit.hit_point, shadow_ray.origin);
	// Determine if the light source is blocked
	if (shadow_hit.t > EPSILON && (magnitude(vector_to_light) > magnitude(vector_to_shadow_hit)))
		return (1); // The point is in shadow
	return (0); // The point is not in shadow
}

t_vec	diffuse(t_inter inter, t_light *light, double d)
{
	t_vec	diff;

	diff = scale_and_combine_colors(inter.color, light->col, d * light->ratio);
	return (diff);
}
//the function of vectors/vec_magnitude.c:

t_vec	scale_to_one(t_vec v)
{
	double	length;
	t_vec	normalized;

	length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (length == 0)
		return (v);
	normalized.x = v.x / length;
	normalized.y = v.y / length;
	normalized.z = v.z / length;
	return (normalized);
}
//the function of vectors/vec2r.c:

void	reset_vec(t_vec *v)
{
	v->x = 0;
	v->y = 0;
	v->z = 0;
}

double	dot_product(t_vec u, t_vec v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vec	cross_product(t_vec v1, t_vec v2)
{
	t_vec	new_vec;

	new_vec.x = (v1.y * v2.z) - (v1.z * v2.y);
	new_vec.y = (v1.z * v2.x )- (v1.x * v2.z);
	new_vec.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (new_vec);
}

t_vec	mult_vec(t_vec v, double a)
{
	v.x = v.x * a;
	v.y = v.y * a;
	v.z = v.z * a;
	return (v);
}

t_vec	vec_addition(t_vec v1, t_vec v2)
{
	t_vec	w;

	w.x = v1.x + v2.x;
	w.y = v1.y + v2.y;
	w.z = v1.z + v2.z;
	return (w);
}

//the function of vectors/vec2r1.c:

t_vec	sub_vec(t_vec u, t_vec v)
{
	t_vec	w;

	w.x = u.x - v.x;
	w.y = u.y - v.y;
	w.z = u.z - v.z;
	return (w);
}

double	magnitude(t_vec	v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

t_vec	div_vect(t_vec v, double a)
{
	v.x /= a;
	v.x /= a;
	v.z /= a;
	return (v);
}

t_vec	create_vector(double x, double y, double z)
{
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}