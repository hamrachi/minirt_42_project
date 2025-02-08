

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


#ifndef MINIRT_H
# define MINIRT_H

# define BUFFER_SIZE 32

# define HEIGHT 800
# define WIDTH 800
# define EPSILON 0.000001
# define CYLINDER 1
# define PLAN 2
# define SPHERE 3
# define CONE 4

#include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "structs.h"

#define NUM_THREADS 7

//parse_utils

void validate_camera_input(char **args, t_scene *scene);
void validate_camera_orientation(t_vec dir);
void validate_camera_fov(double fov);
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

void valid_orient_cone_range(t_vec direction);
void validate_cone_input(char **args);

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
void        parse_cone(t_scene *scene, char **args);

// allocation

// Garbage collector functions

// Allocation functions
t_scene *allocate_scene(void);
t_objs *allocate_object(t_scene *scene);
void gc_cleanup(t_collector **garbage_collector, t_collector *collector_node);
void *gc_malloc(t_collector **garbage_collector, size_t size);
t_collector *create_collector_node(void *allocated_memory);
t_collector **append_to_collector(t_collector **garbage_collector, void *allocated_memory);
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
int	ft_strcmp(const char *str1, const char *str2);

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

/*rendring */
void		ft_render(t_scene *sc);


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
// double  pick_cylinder_intersection(t_cylinder cyl_info, t_ray *ray, t_objs *cylinder);

t_inter calc_plan_normal(t_inter closest_hit, t_objs *plane, t_ray *ray);
// t_inter	update_closest_plane_intersection(t_inter closest_intersection, t_objs *plane, t_ray *ray);

t_inter calc_cylinder_normal(t_inter closest_hit, t_objs *cylinder, t_ray *ray);



t_inter cone_normal(t_inter closest_hit, t_objs *cone, t_ray *ray);

double pick_cone_intersection(t_objs *cone, t_ray *ray, t_cone_info cone_info);
// double pick_cone_intersection(t_objs *cone, t_cam *ray, t_cone_info cone_info);
// double intersect_cone(t_cam *ray, t_objs *cone);
double intersect_cone(t_ray *ray, t_objs *cone);


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


double calc_pl_ray_inter(t_ray *ray, t_objs *plane);
// double plane_intersection(t_ray *ray, t_objs *plane);
t_inter	find_closest_intersection(t_ray *ray, t_scene *scene);

//=-=-=--=threads

void join_threads(pthread_t *threads);
void create_threads(pthread_t *threads, t_thread_data *thread_data);
// void init_thread_data(t_thread_data *data, int thread_id, int rows_per_thread, t_scene *sc, t_render *info);
void init_thread_data(t_thread_data *data, t_thread_info *info);
int get_thread_end_row(int thread_id, int rows_per_thread);

//=-=-=-SSAA

t_vec    process_pixel_with_ssaa(int x, int y, t_camera *cam, t_scene *scene);
t_vec process_sample_row(t_ray_trace_context *ctx, int sy);
t_vec process_single_sample(t_ray_trace_context *ctx, int sx, int sy);
void set_pixel_coords(t_ray_trace_context *ctx, int x, int y);
void init_pixel_context(t_ray_trace_context *ctx, t_ssaa_config *config, t_camera *cam, t_scene *scene);
t_ssaa_config	init_ssaa_config(void);
//=-=-=--=Draw

void ft_draw(t_render *info, t_scene *sc);
void	*render_section(void *arg);
t_vec	trace_sample_ray(t_ray_trace_context *ctx);
t_ray_params	calculate_ray_params(t_ray_trace_context *ctx);



t_vec specular(t_scene *scene, t_inter intersection, t_light *light);
t_vec apply_checkerboard(t_inter *intersection, t_texture *texture);
// t_vec apply_checkerboard(t_inter *intersection);
void parse_checkerboard(t_texture *texture, char **args, int start_idx);


#endif

int	is_valid_rt_file(int ac, char **av)
{
	int	i;
	int	fd;

	fd = 0;
	if (ac != 2 || !av[1])
		return (1);
	i = ft_strlen(av[1]);
	if (i < 4)
		return (1);
	if (i > 3 && ft_strncmp(av[1] + i - 3, ".rt", 3) == 0)
	{
		fd = open(av[1], O_RDONLY);
		if (fd < 0)
			return (1);
		close(fd);
	}
	else
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_scene	*scene;
	int		fd;

	if (is_valid_rt_file(ac, av))
		report_error("wrong args : Please try enter filename.rt");
	fd = open(av[1], O_RDONLY);
	scene = allocate_scene();
	if (!scene)
		report_error("allocation");
	parse_scene_file(scene, fd);
	ft_render(scene);
	gc_cleanup(&garbage_collector, garbage_collector);
	return (0);
}

// Modified parsing functions
void parse_plane(t_scene *scene, char **args)
{
    t_objs *obj;

    validate_plane_input(args);
    obj = allocate_object(scene);
    obj->type = PLAN;
    obj->center = get_vec(args[1]);
    obj->direction = get_vec(args[2]);
    validate_plane_orientation(obj->direction);
    obj->color = get_color(args[3]);
    
    // Initialize texture
    obj->texture.has_checkerboard = 0;
    // Parse optional checkerboard parameters
    parse_checkerboard(&obj->texture, args, 4);
}
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
    else if (ft_strcmp(shape_type, "co") == 0)
        parse_cone(scene, tokens);
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
             (ft_strcmp(object_type, "cy") == 0) ||
             (ft_strcmp(object_type, "co") == 0))
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
    // Initialize MLX here, before parsing
    sc->mlx = mlx_init();
    if (!sc->mlx)
        report_error("MLX initialization failed");
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

// Helper function to parse checkerboard parameters
void parse_checkerboard(t_texture *texture, char **args, int start_idx)
{
    if (!args[start_idx])
        return;
    
    // Check if it's a checkerboard texture
    if (ft_strcmp(args[start_idx], "checker") == 0) {
        if (!args[start_idx + 1] || !args[start_idx + 2])
            report_error("Invalid checkerboard parameters");
            
        texture->has_checkerboard = 1;
        texture->checker_size = ft_atod(args[start_idx + 1]);
        texture->color2 = get_color(args[start_idx + 2]);
        
        if (texture->checker_size <= 0)
            report_error("Checker size must be positive");
    }
}

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

void parse_light(t_scene *scene, char **args)//new
{
    t_light *new;

    // Validate light input (args and count)
    validate_light_input(args);
    // Allocate memory for the new light object
    new = alloc_light(scene);
    // Set the light source vector and validate the ratio
    new->src = get_vec(args[1]);
    new->ratio = ft_atod(args[2]);
    // Validate light brightness ratio
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

void parse_cylinder(t_scene *scene, char **args)
{
    t_objs *obj;

    validate_cylinder_input(args);
    obj = allocate_object(scene);
    obj->type = CYLINDER;
    obj->center = get_vec(args[1]);
    obj->direction = get_vec(args[2]);

    validate_cylinder_orientation(obj->direction);
    obj->p.x = ft_atod(args[3]);
    obj->p.y = ft_atod(args[4]);
    validate_cylinder_diameter(obj->p.x, obj->p.y);
    obj->color = get_color(args[5]);
    
    // Initialize texture
    obj->texture.has_checkerboard = 0;
    // Parse optional checkerboard parameters
    parse_checkerboard(&obj->texture, args, 6);


}

// Modified parse_sphere function to handle texture parameters
void parse_sphere(t_scene *scene, char **args)
{
    t_objs *obj;
    void *mlx = scene->render_info.vars.mlx; // Assuming you have MLX context in scene

    validate_sphere_input(args);
    obj = allocate_object(scene);
    obj->type = SPHERE;
    obj->center = get_vec(args[1]);
    obj->p.x = ft_atod(args[2]);
    validate_sphere_diameter(obj->p.x);
    obj->color = get_color(args[3]);
    
    // Initialize texture properties
    obj->texture.has_checkerboard = 0;
    obj->texture.has_image = 0;
    
    // Check for texture parameters
    int arg_idx = 4;
    if (args[arg_idx])
    {
        if (ft_strcmp(args[arg_idx], "checker") == 0)
        {
            // Parse checkerboard parameters
            parse_checkerboard(&obj->texture, args, arg_idx);
        }
        else if (ft_strcmp(args[arg_idx], "texture") == 0)
        {
            // Parse image texture parameters
            parse_texture(&obj->texture, args, arg_idx, mlx);
        }
    }
}

void parse_cone(t_scene *scene, char **args)
{
    t_objs *obj;
    double height;

    validate_cone_input(args);
    obj = allocate_object(scene);
    obj->type = CONE;
    obj->center = get_vec(args[1]);
    obj->direction = get_vec(args[2]);
    obj->direction = scale_to_one(obj->direction);
    
    // Validate cone orientation
    valid_orient_cone_range(obj->direction);

    obj->p.x = ft_atod(args[3]);
    height = ft_atod(args[4]);    // height
    obj->p.y = height;           // store height
    obj->p.z = ft_atod(args[5]);
    if (obj->p.x <= 0 || obj->p.x > 180)
        report_error("invalid diameter cone");

    obj->color = get_color(args[6]);

    // Initialize texture
    obj->texture.has_checkerboard = 0;
    // Parse optional checkerboard parameters
    parse_checkerboard(&obj->texture, args, 7);
}

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
//=-=-=-=-=-

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

void validate_plane_input(char **args)
{
    int arg_count = 0;
    
    if (!args || !args[1] || !args[2] || !args[3])
        report_error("Plane parameters are invalid.");
    
    while (args[arg_count])
        arg_count++;
    
    if (arg_count == 4)
        return;
    else if (arg_count == 7 && ft_strcmp(args[4], "checker") == 0)
        return;
    else
        report_error("Invalid number of arguments for plane.");
}
// Helper function to validate the plane orientation
void validate_plane_orientation(t_vec dir)
{
    if (dir.x > 1 || dir.y > 1 || dir.z > 1 || \
			dir.x < -1 || dir.y < -1 || dir.z < -1)
        report_error("Plane direction components must be between -1 and 1.");
}

void valid_orient_cone_range(t_vec direction)
{
   if (direction.x > 1 || direction.y > 1 || direction.z > 1)
		report_error("invalid orientation cone");
	if (direction.x < -1 || direction.y < -1 || direction.z < -1)
		report_error("invalid orientation cone"); 
}

// void validate_cone_input(char **args)
// {
//     if (!args || !args[1] || !args[2] || !args[3] || !args[4]
// 		|| !args[5] || !args[6] || args[7])
// 		report_error("invalid cone");
// }

void validate_cone_input(char **args)
{
    int arg_count = 0;
    
    // Check required parameters (position, direction, diameter, height, angle, color)
    if (!args || !args[1] || !args[2] || !args[3] || !args[4] || !args[5] || !args[6])
        report_error("Cone parameters are invalid.");
    
    while (args[arg_count])
        arg_count++;
    
    // Valid cases:
    // 1. Basic cone: exactly 7 arguments (co x,y,z dx,dy,dz diameter height angle r,g,b)
    // 2. Cone with checker: exactly 10 arguments (adding: checker size r2,g2,b2)
    if (arg_count == 7)
        return;
    else if (arg_count == 10 && ft_strcmp(args[7], "checker") == 0)
        return;
    else
        report_error("Invalid number of arguments for cone. Use either:\n"
                    "co x,y,z dx,dy,dz diameter height angle r,g,b\n"
                    "or\n"
                    "co x,y,z dx,dy,dz diameter height angle r,g,b checker size r2,g2,b2");
}

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

// Modified sphere input validation to account for textures
void validate_sphere_input(char **args)
{
    int arg_count = 0;
    
    if (!args || !args[1] || !args[2] || !args[3])
        report_error("Sphere parameters are invalid.");
    
    while (args[arg_count])
        arg_count++;
    
    // Valid formats:
    // 1. Basic sphere: sp x,y,z diameter r,g,b
    // 2. Checker texture: sp x,y,z diameter r,g,b checker size r2,g2,b2
    // 3. Image texture: sp x,y,z diameter r,g,b texture path scale_u scale_v
    if (arg_count == 4)
        return; // Basic sphere
    else if (arg_count == 7 && ft_strcmp(args[4], "checker") == 0)
        return; // Checker pattern
    else if (arg_count == 8 && ft_strcmp(args[4], "texture") == 0)
        return; // Image texture
    else
        report_error("Invalid sphere format. Use one of:\n"
                    "sp x,y,z diameter r,g,b\n"
                    "sp x,y,z diameter r,g,b checker size r2,g2,b2\n"
                    "sp x,y,z diameter r,g,b texture path scale_u scale_v");
}

// Helper function to validate the sphere diameter
void validate_sphere_diameter(double diameter)
{
    if (diameter <= 0)
        report_error("Invalid sphere diameter: must be positive.");
}
//=========

void validate_cylinder_input(char **args)
{
    int arg_count = 0;
    
    if (!args || !args[1] || !args[2] || !args[3] || !args[4] || !args[5])
        report_error("Cylinder parameters are invalid.");
    
    while (args[arg_count])
        arg_count++;
    
    if (arg_count == 6)
        return;
    else if (arg_count == 9 && ft_strcmp(args[6], "checker") == 0)
        return;
    else
        report_error("Invalid number of arguments for cylinder.");
}
// Helper function to validate the cylinder orientation
void validate_cylinder_orientation(t_vec dir)
{
    if (dir.x > 1 || dir.y > 1 || dir.z > 1 || \
			dir.x < -1 || dir.y < -1 || dir.z < -1)
        report_error("Cylinder direction components must be between -1 and 1.");
}

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

//camera

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

//checkerboeard and speculare and colors and calclute_lighting

// Function to calculate the checkerboard color
t_vec apply_checkerboard(t_inter *intersection, t_texture *texture)
{
    int x, y, z;

    if (!texture->has_checkerboard)
        return (intersection->color); // No checkerboard, return the object's base color

    // Scale the hit point to the checker size
    x = floor(intersection->hit_point.x / texture->checker_size);
    y = floor(intersection->hit_point.y / texture->checker_size);
    z = floor(intersection->hit_point.z / texture->checker_size);

    // Determine the color based on alternating pattern
    if ((x + y + z) % 2 == 0)
        return (intersection->color); // Base color
    return (texture->color2); // Checkerboard color
}
t_vec compute_lighting(t_scene *scene, t_inter intersection, t_vec ambient_color)//origine
{
    t_light *current_light;
    t_vec final_color;
    t_vec light_direction;
    double diffuse_factor;

    final_color = create_vector(0, 0, 0);
    current_light = scene->light;

    while (current_light)
    {
        if (!is_point_in_shadow(scene, intersection, current_light))
        {
            // Diffuse Lighting
            light_direction = sub_vec(current_light->src, intersection.hit_point);
            diffuse_factor = dot_product(scale_to_one(light_direction), intersection.normal);
            if (diffuse_factor > 0)
                final_color = blend_colors(final_color, diffuse(intersection, current_light, diffuse_factor));

            // Specular Lighting
            final_color = blend_colors(final_color, specular(scene, intersection, current_light));
        }
        current_light = current_light->next;
    }

    // Add Ambient Light
    final_color = blend_colors(final_color, ambient_color);

    // Clamp Final Color
    final_color.x = fmin(final_color.x, 255);
    final_color.y = fmin(final_color.y, 255);
    final_color.z = fmin(final_color.z, 255);    
    return final_color;
}

t_vec scale_and_combine_colors(t_vec base_color, t_vec light_color, double intensity_ratio)
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

t_vec specular(t_scene *scene, t_inter intersection, t_light *light)
{
    t_vec light_to_hit;         // Vector from light to intersection point
    t_vec normalized_light_dir; // Normalized direction of light
    t_vec view_vector;          // Direction from intersection point to camera
    t_vec reflection_vector;    // Reflected light direction
    double specular_intensity;  // Calculated specular intensity
    t_vec specular_color;       // Resultant specular color

    // Calculate the vector from light source to the intersection point
    light_to_hit = sub_vec(light->src, intersection.hit_point);

    // Normalize the light direction
    normalized_light_dir = scale_to_one(light_to_hit);

    // Calculate the view vector (from hit point to camera)
    t_vec hit_to_camera = sub_vec(intersection.hit_point, scene->cam.cen);
    view_vector = scale_to_one(hit_to_camera);
    // Calculate the reflection vector
    t_vec scaled_normal = mult_vec(intersection.normal, 2 * dot_product(intersection.normal, normalized_light_dir));
    reflection_vector = sub_vec(scaled_normal, normalized_light_dir);
    // Calculate the specular intensity using the reflection and view vectors
    specular_intensity = pow(dot_product(reflection_vector, view_vector), 50) * light->ratio * 0.5;
    // Calculate the specular color by scaling the light color
    specular_color = mult_vec(light->col, specular_intensity);
    return specular_color;
}
//mlx thing:

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
//intersections

t_inter find_closest_intersection(t_ray *ray, t_scene *scene)
{
    t_inter closest_inter;
    t_objs *current_obj;
    t_objs *closest_obj = NULL;
    double u, v;

    closest_inter.t = -1.0;
    current_obj = scene->objs;

    while (current_obj)
    {
        t_inter temp_inter = closest_inter;

        if (current_obj->type == SPHERE)
            temp_inter = calc_sphere_normal(closest_inter, current_obj, ray);
        if (current_obj->type == PLAN)
            temp_inter = calc_plan_normal(closest_inter, current_obj, ray);
        if (current_obj->type == CYLINDER)
            temp_inter = calc_cylinder_normal(closest_inter, current_obj, ray);
        if (current_obj->type == CONE)
            temp_inter = cone_normal(closest_inter, current_obj, ray);

        if (temp_inter.t > EPSILON && (closest_inter.t < 0 || temp_inter.t < closest_inter.t))
        {
            closest_inter = temp_inter;
            closest_obj = current_obj;
        }

        current_obj = current_obj->next;
    }

    // Apply texture only if we found an intersection and have a valid object
    if (closest_obj && closest_inter.t > EPSILON)
    {
        // Calculate texture coordinates based on object type
        calculate_texture_coords(&closest_inter, closest_obj, &u, &v);

        // Apply texture if present
        if (closest_obj->texture.has_image)
        {
            // Apply image texture using calculated UV coordinates
            closest_inter.color = get_texture_color(&closest_obj->texture, u, v);
        }
        else if (closest_obj->texture.has_checkerboard)
        {
            // Apply checkerboard texture
            closest_inter.color = apply_checkerboard(&closest_inter, &closest_obj->texture);
        }
    }

    return closest_inter;
}

// t_inter find_closest_intersection(t_ray *ray, t_scene *scene)//old
// {
//     t_inter closest_inter;
//     t_objs *current_obj;
//     t_objs *closest_obj = NULL;  // Keep track of the closest object

//     closest_inter.t = -1.0; // Initialize with no intersection
//     current_obj = scene->objs; // Start traversing objects

//     while (current_obj)
//     {
//         t_inter temp_inter = closest_inter;  // Store current intersection

//         if (current_obj->type == SPHERE)
//             temp_inter = calc_sphere_normal(closest_inter, current_obj, ray);
//         if (current_obj->type == PLAN)
//             temp_inter = calc_plan_normal(closest_inter, current_obj, ray);
//         if (current_obj->type == CYLINDER)
//             temp_inter = calc_cylinder_normal(closest_inter, current_obj, ray);
//         if (current_obj->type == CONE)
//             temp_inter = cone_normal(closest_inter, current_obj, ray);

//         // Update closest intersection if we found a closer one
//         if (temp_inter.t > EPSILON && (closest_inter.t < 0 || temp_inter.t < closest_inter.t))
//         {
//             closest_inter = temp_inter;
//             closest_obj = current_obj;  // Remember which object was closest
//         }

//         current_obj = current_obj->next;
//     }
//     // Apply texture only for the closest object
//     if (closest_obj && closest_inter.t > EPSILON)
//     {
//         closest_inter.has_checkerboard = closest_obj->texture.has_checkerboard;
//         if (closest_obj->texture.has_checkerboard)
//             closest_inter.color = apply_checkerboard(&closest_inter, &closest_obj->texture);
//     }

//     return (closest_inter);
// }
//rendring

void	ft_render(t_scene *sc)
{
	t_render	info;

	info.cam = set_camera(sc);
	image_init(&info);
	ft_draw(&info, sc);
	mlx_put_image_to_window(info.vars.mlx, info.vars.win, info.img.img, 0, 0);
	mlx_key_hook(info.vars.win, handle_key, &info.vars);
	mlx_hook(info.vars.win, 17, 0, cross_button, &info.vars);
	mlx_loop(info.vars.mlx);
}
//draw and treads and supersimpling

// Calculate end row for a thread
int get_thread_end_row(int thread_id, int rows_per_thread)
{
    int end_row;

    if (thread_id == NUM_THREADS - 1)
        end_row = HEIGHT;
    else
        end_row = (thread_id + 1) * rows_per_thread;
    return (end_row);
}


void init_thread_data(t_thread_data *data, t_thread_info *info)
{
    data->thread_id = info->thread_id;
    data->start_row = info->thread_id * info->rows_per_thread;
    data->end_row = get_thread_end_row(info->thread_id, info->rows_per_thread);
    data->scene = info->scene;
    data->info = info->render_info;
}

// Wait for threads to complete
void join_threads(pthread_t *threads)
{
    int i;

    i = 0;
    while (i < NUM_THREADS)
    {
        pthread_join(threads[i], NULL);
        i++;
    }
}

void create_threads(pthread_t *threads, t_thread_data *thread_data)
{
    int i;

    i = 0;
    while (i < NUM_THREADS)
    {
        if (pthread_create(&threads[i], NULL, render_section, &thread_data[i]) != 0)
        {
            perror("Error creating thread");
            exit(EXIT_FAILURE);
        }
        i++;
    }
}

void ft_draw(t_render *info, t_scene *sc)
{
    pthread_t threads[NUM_THREADS];
    t_thread_data thread_data[NUM_THREADS];
    t_thread_info thread_info;
    int rows_per_thread;
    int i;

    rows_per_thread = (HEIGHT + NUM_THREADS - 1) / NUM_THREADS; // Ceiling division for even distribution
    pthread_mutex_t render_mutex;

    // Initialize mutex for shared data protection
    pthread_mutex_init(&render_mutex, NULL);

    i = 0;
    while (i < NUM_THREADS)
    {
        // Prepare thread info for the current thread
        thread_info.thread_id = i;
        thread_info.rows_per_thread = rows_per_thread;
        thread_info.scene = sc;
        thread_info.render_info = info;

        // Initialize thread data
        init_thread_data(&thread_data[i], &thread_info);

        // Pass the mutex to thread data if needed
        thread_data[i].render_mutex = render_mutex;

        i++;
    }

    create_threads(threads, thread_data);
    join_threads(threads);

    // Destroy the mutex after all threads are done
    pthread_mutex_destroy(&render_mutex);
}

// Calculate ray parameters
t_ray_params	calculate_ray_params(t_ray_trace_context *ctx)
{
	t_ray_params	params;

	params.offset_u = (ctx->sx + 0.5) * ctx->config->subpixel_step;
	params.offset_v = (ctx->sy + 0.5) * ctx->config->subpixel_step;

	params.u = ((double)ctx->x + params.offset_u) * 2 / WIDTH - 1;
	params.v = ((double)ctx->y + params.offset_v) * 2 / HEIGHT - 1;

	return (params);
}

// Trace a single sample ray
t_vec	trace_sample_ray(t_ray_trace_context *ctx)
{
	t_ray_params	params;
	t_ray		ray;

	// Calculate ray parameters
	params = calculate_ray_params(ctx);

	// Generate and trace the ray
	ray = ray_primary(ctx->cam, params.u, params.v);
	return (ray_color(&ray, ctx->scene));
}

//=-=-=-=-

// Initialize and prepare context for SSAA

// Initialize the context structure (4 parameters)
void init_pixel_context(t_ray_trace_context *ctx, t_ssaa_config *config, t_camera *cam, t_scene *scene)
{
    ctx->config = config;
    ctx->cam = cam;
    ctx->scene = scene;
}

// Set pixel coordinates in context (3 parameters)
void set_pixel_coords(t_ray_trace_context *ctx, int x, int y)
{
    ctx->x = x;
    ctx->y = y;
}

// Process a single sample of the pixel
t_vec process_single_sample(t_ray_trace_context *ctx, int sx, int sy)
{
    ctx->sx = sx;
    ctx->sy = sy;
    return (trace_sample_ray(ctx));
}


t_ssaa_config	init_ssaa_config(void)
{
	t_ssaa_config	config;

	config.samples_per_side = 2;
	config.total_samples = config.samples_per_side * config.samples_per_side;
	config.subpixel_step = 1.0 / config.samples_per_side;
	config.inv_total_samples = 1.0 / config.total_samples;
	return (config);
}

t_vec process_sample_row(t_ray_trace_context *ctx, int sy)
{
    t_vec color;
    t_vec sample_color;
    int   sx;

    color = (t_vec){0, 0, 0};
    sx = 0;
    while (sx < ctx->config->samples_per_side)
    {
        sample_color = process_single_sample(ctx, sx, sy);
        color = vec_addition(color, sample_color);
        sx++;
    }
    return (color);
}

// Main function to process pixel with supersampling
t_vec    process_pixel_with_ssaa(int x, int y, t_camera *cam, t_scene *scene)
{
    t_ray_trace_context    ctx;
    t_vec                  color;
    t_vec                  row_color;
    t_ssaa_config         config;
    int                    sy;

    config = init_ssaa_config();
    init_pixel_context(&ctx, &config, cam, scene);
    set_pixel_coords(&ctx, x, y);
    color = (t_vec){0, 0, 0};
    sy = 0;
    while (sy < config.samples_per_side)
    {
        row_color = process_sample_row(&ctx, sy);
        color = vec_addition(color, row_color);
        sy++;
    }
    return (mult_vec(color, config.inv_total_samples));
}

// Main render section function remains the same
void	*render_section(void *arg)
{
	t_thread_data	*data;
	int				x;
	int				y;
	t_vec			color;

	data = (t_thread_data *)arg;

	for (y = data->start_row; y < data->end_row; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			// Process pixel with SSAA
			color = process_pixel_with_ssaa(x, y, &data->info->cam, data->scene);

			// Write the final color to the pixel
			my_mlx_pixel_put(&data->info->img, x, HEIGHT - 1 - y,
							 create_rgb(color.x, color.y, color.z));
		}
	}
	return (NULL);
}

//here is the functions of the textures:

// Function to load texture from file
t_img_data *load_texture(void *mlx, char *path)
{
    t_img_data *img;

    img = malloc(sizeof(t_img_data));
    if (!img)
        return NULL;

    img->img = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
    if (!img->img)
    {
        free(img);
        return NULL;
    }

    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
                                 &img->line_length, &img->endian);
    return img;
}

// Function to get color from texture coordinates
t_vec get_texture_color(t_texture *texture, double u, double v)
{
    int x, y;
    int color;
    char *pixel;
    t_vec result;

    if (!texture->has_image || !texture->image)
        return (t_vec){0, 0, 0};

    // Scale and wrap texture coordinates
    u = fmod(u * texture->scale_u, 1.0);
    v = fmod(v * texture->scale_v, 1.0);
    if (u < 0) u += 1.0;
    if (v < 0) v += 1.0;

    // Convert to image coordinates
    x = (int)(u * (texture->image->width - 1));
    y = (int)(v * (texture->image->height - 1));

    // Get pixel color from image
    pixel = texture->image->addr + (y * texture->image->line_length + 
            x * (texture->image->bits_per_pixel / 8));
    color = *(unsigned int*)pixel;

    // Convert to RGB vector
    result.x = (color >> 16) & 0xFF;
    result.y = (color >> 8) & 0xFF;
    result.z = color & 0xFF;

    return result;
}

// Function to calculate texture coordinates for each object type
void calculate_texture_coords(t_inter *intersection, t_objs *obj, double *u, double *v)
{
    t_vec local_point;
    
    switch (obj->type)
    {
        case SPHERE:
            // Spherical mapping
            *u = 0.5 + atan2(intersection->normal.z, intersection->normal.x) / (2 * M_PI);
            *v = 0.5 - asin(intersection->normal.y) / M_PI;
            break;
            
        case PLAN:
            // Planar mapping
            local_point = intersection->hit_point;
            *u = local_point.x * 0.1; // Scale factor can be adjusted
            *v = local_point.z * 0.1;
            break;
            
        case CYLINDER:
            // Cylindrical mapping
            local_point = sub_vec(intersection->hit_point, obj->center);
            *u = 0.5 + atan2(local_point.z, local_point.x) / (2 * M_PI);
            *v = fmod(local_point.y * 0.1, 1.0);
            break;
            
        case CONE:
            // Conical mapping
            local_point = sub_vec(intersection->hit_point, obj->center);
            *u = 0.5 + atan2(local_point.z, local_point.x) / (2 * M_PI);
            *v = sqrt(local_point.x * local_point.x + local_point.z * local_point.z) * 0.1;
            break;
    }
}

// Modified apply_texture function
t_vec apply_texture(t_inter *intersection, t_texture *texture, t_objs *obj)
{
    if (texture->has_checkerboard)
        return apply_checkerboard(intersection, texture);
    else if (texture->has_image)
    {
        double u, v;
        calculate_texture_coords(intersection, obj, &u, &v);
        return get_texture_color(texture, u, v);
    }
    return intersection->color;
}

// Add to parse functions
void parse_texture(t_texture *texture, char **args, int start_idx, void *mlx)
{
    if (!args[start_idx])
        return;

    if (ft_strcmp(args[start_idx], "texture") == 0)
    {
        if (!args[start_idx + 1] || !args[start_idx + 2] || !args[start_idx + 3])
            report_error("Invalid texture parameters");

        texture->has_image = 1;
        texture->image = load_texture(mlx, args[start_idx + 1]);
        if (!texture->image)
            report_error("Failed to load texture image");

        texture->scale_u = ft_atod(args[start_idx + 2]);
        texture->scale_v = ft_atod(args[start_idx + 3]);

        if (texture->scale_u <= 0 || texture->scale_v <= 0)
            report_error("Texture scaling must be positive");
    }
}