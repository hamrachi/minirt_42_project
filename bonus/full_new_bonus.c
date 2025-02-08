
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


// Add this to your header file
typedef struct s_texture
{
    int has_checkerboard;
    double checker_size;
    t_point3d color2;  // Second color for checkerboard

	// Add image texture support
    int         has_image;
    t_canvas    *image;
    double      scale_u;    // Texture scaling in U direction
    double      scale_v;    // Texture scaling in V direction
} t_texture;

typedef struct s_vars //need tototototototototo
{
	void	*mlx;
	void	*win;
}				t_vars;



typedef struct s_scene_element 
{
	int					type;       // Object type
	t_texture 			texture;
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
	t_texture   texture;
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

//=-=-=-=-=-

typedef struct s_thread_info
{
    int thread_id;
    int rows_per_thread;
    t_world *scene;
    t_tracer *render_info;
} t_thread_info;

typedef struct s_thread_data 
{
    int thread_id;      // ID of the thread
    int start_row;      // Starting row for this thread
    int end_row;        // Ending row for this thread
    t_world *scene;     // Pointer to the scene
    t_tracer *info;     // Pointer to the rendering information

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
	t_cam_matrix		*cam;
	t_world			*scene;
}	t_ray_trace_context;

typedef struct s_ray_params
{
	double	u;
	double	v;
	double	offset_u;
	double	offset_v;
}	t_ray_params;

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
# include "structs_bonus.h"

#define NUM_THREADS 7

//parse_utils

void validate_camera_input(char **args, t_world *scene);
void validate_camera_orientation(t_point3d dir);
void validate_camera_fov(double fov);
void validate_light_input(char **args);
void validate_light_ratio(double ratio);
void validate_plane_input(char **args);
void validate_plane_orientation(t_point3d dir);
void validate_color_input(char **args);
void validate_color_range(t_point3d color);
void validate_vec_input(char **args);
void validate_sphere_input(char **args);
void validate_sphere_diameter(double diameter);
void validate_cylinder_input(char **args);
void validate_cylinder_orientation(t_point3d dir);
void validate_ambient_ratio_range(double ratio);
void validate_ambient_input(char **args, t_world *scene);
void validate_cylinder_diameter(double diameter, double height);


// parse
void        report_error(char *str);
int			is_valid_rt_file(int ac, char **av);
void        parse_scene_file(t_world *sc, int fd);//
void        parse_object(char *object_type, char **tokens, t_world *scene);//new
void		parse_plane(t_world *sc, char **tockens);
void		parse_cylinder(t_world *sc, char **tockens);
void		parse_sphere(t_world *sc, char **tockens);
void		parse_light(t_world *sc, char **tockens);
void		parse_camera(t_world *sc, char **tockens);
void		parse_ambient(t_world *sc, char **tockens);
void        parse_cone(t_world *scene, char **args);

// allocation

// Garbage collector functions

// Allocation functions
t_world *allocate_scene(void);
t_scene_element *allocate_object(t_world *scene);
void gc_cleanup(t_heap_track **garbage_collector, t_heap_track *collector_node);
void *gc_malloc(t_heap_track **garbage_collector, size_t size);
// t_collector *create_collector_node(void *allocated_memory);
// t_collector **append_to_collector(t_collector **garbage_collector, void *allocated_memory);
t_heap_track	*garbage_collector;

// tools
int			ft_strlen(const char *str);
char        *append_char_to_string(char *original, char new_char);
char	    *line(int fd);
double		ft_atod(const char *str);
int			ft_atoi(const char *str);
char		**ft_split(const char *str, char c);
void	free_split(char **array);
int	        ft_strncmp(char *s1, const char *s2, size_t n);
int	ft_strcmp(const char *str1, const char *str2);

/* camera */
t_cam_matrix	set_camera(t_world *sc);
t_ray	ray_primary(t_cam_matrix *cam, double v, double u);
t_point3d		ray_at(t_ray *ray, double t);
t_point3d		ray_at(t_ray *ray, double t);
//vectors
void		reset_vec(t_point3d *v);
t_point3d		get_vec(char *s);
t_point3d		get_color(char *s);
t_point3d		scale_to_one(t_point3d v);
t_point3d		sub_vec(t_point3d u, t_point3d v);
t_point3d	vec_addition(t_point3d v1, t_point3d v2);
t_point3d		mult_vec(t_point3d v, double a);
t_point3d		cross_product(t_point3d v1, t_point3d v2);//
double		dot_product(t_point3d u, t_point3d v);
double		magnitude(t_point3d	v);
t_point3d		div_vect(t_point3d v, double a);
t_point3d		create_vector(double x, double y, double z);

/*rendring */
void		ft_render(t_world *sc);


/* intersections*/
double find_min(double first_num, double second_num);

t_inter_data	find_closest_intersection(t_ray *ray, t_world *scene);


t_inter_data calc_sphere_normal(t_inter_data current_hit, t_scene_element *sphere, t_ray *ray);
// t_inter calculate_sphere_intersection(t_inter current_closest, t_objs *sphere, t_ray *ray);


double calc_sp_ray_inter(t_ray *ray, t_scene_element *sphere);
// double	sphere_intersection(t_ray *ray, t_objs *sphere);

double      calculate_plane_intersection(t_ray *ray, t_scene_element *plane);

double      find_cylinder_intersection(t_ray *ray, t_scene_element *cylinder);
// double intersect_cylinder(t_ray *ray, t_objs *cylinder);

double      calculate_cylinder_intersection(t_cyl_calc cylinder_calc, t_ray *ray, t_scene_element *cylinder);
// double  pick_cylinder_intersection(t_cylinder cyl_info, t_ray *ray, t_objs *cylinder);

t_inter_data calc_plan_normal(t_inter_data closest_hit, t_scene_element *plane, t_ray *ray);
// t_inter	update_closest_plane_intersection(t_inter closest_intersection, t_objs *plane, t_ray *ray);

t_inter_data calc_cylinder_normal(t_inter_data closest_hit, t_scene_element *cylinder, t_ray *ray);



t_inter_data cone_normal(t_inter_data closest_hit, t_scene_element *cone, t_ray *ray);

// double pick_cone_intersection(t_scene_element *cone, t_ray *ray, t_cone_info cone_info);
// double pick_cone_intersection(t_objs *cone, t_cam *ray, t_cone_info cone_info);
// double intersect_cone(t_cam *ray, t_objs *cone);
double intersect_cone(t_ray *ray, t_scene_element *cone);


/* mlx funct */
int			cross_button(t_vars *vars);
int			esc_key(int key, t_vars *vars);
void		my_mlx_pixel_put(t_canvas *data, int x, int y, int color);
void	image_init(t_tracer	*info);

// color
t_point3d       scale_and_combine_colors(t_point3d base_color, t_point3d light_color, double intensity_ratio);
int			create_rgb(int r, int g, int b);
t_point3d       blend_colors(t_point3d color_a, t_point3d color_b);
t_point3d		ray_color(t_ray *ray, t_world *sc);
t_point3d		colorize(double r, double g, double b);
t_point3d		diffuse(t_inter_data inter, t_light_source *light, double d);

int         is_point_in_shadow(t_world *scene, t_inter_data intersection, t_light_source *light_source);
//surface normal
int			ray_is_inside(t_point3d ray, t_point3d s_norm);


double calc_pl_ray_inter(t_ray *ray, t_scene_element *plane);
// double plane_intersection(t_ray *ray, t_objs *plane);
t_inter_data	find_closest_intersection(t_ray *ray, t_world *scene);

//=-=-=--=threads

void join_threads(pthread_t *threads);
void create_threads(pthread_t *threads, t_thread_data *thread_data);
// void init_thread_data(t_thread_data *data, int thread_id, int rows_per_thread, t_scene *sc, t_render *info);
void init_thread_data(t_thread_data *data, t_thread_info *info);
int get_thread_end_row(int thread_id, int rows_per_thread);

//=-=-=-SSAA

t_point3d    process_pixel_with_ssaa(int x, int y, t_cam_matrix *cam, t_world *scene);
t_point3d process_sample_row(t_ray_trace_context *ctx, int sy);
t_point3d process_single_sample(t_ray_trace_context *ctx, int sx, int sy);
void set_pixel_coords(t_ray_trace_context *ctx, int x, int y);
void init_pixel_context(t_ray_trace_context *ctx, t_ssaa_config *config, t_cam_matrix *cam, t_world *scene);
t_ssaa_config	init_ssaa_config(void);
//=-=-=--=Draw

void ft_draw(t_tracer *info, t_world *sc);
void	*render_section(void *arg);
t_point3d	trace_sample_ray(t_ray_trace_context *ctx);
t_ray_params	calculate_ray_params(t_ray_trace_context *ctx);



t_point3d specular(t_world *scene, t_inter_data intersection, t_light_source *light);
t_point3d apply_checkerboard(t_inter_data *intersection, t_texture *texture);
// t_vec apply_checkerboard(t_inter *intersection);
void parse_checkerboard(t_texture *texture, char **args, int start_idx);


void parse_texture(t_texture *texture, char **args, int start_idx, void *mlx);
// t_img_data *load_texture(void *mlx, char *path);
t_point3d get_texture_color(t_texture *texture, double u, double v);
void calculate_texture_coords(t_inter_data *intersection, t_scene_element *obj, double *u, double *v);
t_point3d apply_texture(t_inter_data *intersection, t_texture *texture, t_scene_element *obj);


#endif

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
	t_world	*scene;
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
// camera
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

	// Initialize the camera parameters
	cam = initialize_camera_params(sc);
	// Set ref_axis and calculate up and right vectors
	ref_world_up = create_vector(0.0, -1.0, 0.0);
	cam.up_vec = scale_to_one(cross_product(cam.fwd_vec, ref_world_up));
	cam.right_vec = scale_to_one(cross_product(cam.fwd_vec, cam.up_vec));
	return (cam);
}

t_ray	ray_primary(t_cam_matrix *cam, double v, double u)
{
	t_ray		ray;
	t_point3d	vertical_offset;
	t_point3d 	horizontal_offset;
	t_point3d 	combine_offset;

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
//checker board
// Function to calculate the checkerboard color
t_point3d apply_checkerboard(t_inter_data *intersection, t_texture *texture)
{
    int x;
    int y;
    int z;

    if (!texture->has_checkerboard)
        return (intersection->color); // No checkerboard, return the object's base color

    // Scale the hit point to the checker size
    x = floor(intersection->hit_point . x_coord / texture->checker_size);
    y = floor(intersection->hit_point . y_coord / texture->checker_size);
    z = floor(intersection->hit_point . z_coord / texture->checker_size);

    // Determine the color based on alternating pattern
    if ((x + y + z) % 2 == 0)
        return (intersection->color); // Base color
    return (texture->color2); // Checkerboard color
}
// color 
t_point3d compute_lighting(t_world *scene, t_inter_data intersection, t_point3d ambient_color)//origine
{
    t_light_source *current_light;
    t_point3d final_color;
    t_point3d light_direction;
    double diffuse_factor;

    final_color = create_vector(0, 0, 0);
    current_light = scene->light;

    while (current_light)
    {
        if (!is_point_in_shadow(scene, intersection, current_light))
        {
            // Diffuse Lighting
            light_direction = sub_vec(current_light->position, intersection.hit_point);
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
    return final_color;
}


t_point3d scale_and_combine_colors(t_point3d base_color, t_point3d light_color, double intensity_ratio)
{
    t_point3d result_color;

    result_color.x_coord = base_color.x_coord * (light_color.x_coord / 255) * intensity_ratio;
    result_color.y_coord = base_color.y_coord * (light_color.y_coord / 255) * intensity_ratio;
    result_color.z_coord = base_color.z_coord * (light_color.z_coord / 255) * intensity_ratio;

    return (result_color);
}



t_point3d blend_colors(t_point3d color_a, t_point3d color_b)
{
    t_point3d blended_color;

    blended_color = vec_addition(color_a, color_b);
    if (blended_color.x_coord > 255)
        blended_color.x_coord = 255;
    if (blended_color.y_coord > 255)
        blended_color.y_coord = 255;
    if (blended_color.z_coord > 255)
        blended_color.z_coord = 255;

    return (blended_color);
}


t_point3d	ray_color(t_ray *ray, t_world *sc)
{
	t_inter_data	inter;
	t_point3d	px_col;
	t_point3d	amb;

	inter = find_closest_intersection(ray, sc);
	if (inter.t > EPSILON)
	{
		amb = scale_and_combine_colors(inter.color, sc->amb_light.light_color, sc->amb_light.intensity);
		if (ray_is_inside(ray->direction, inter.normal))
			inter.normal = mult_vec(inter.normal, -1);
		px_col = compute_lighting(sc, inter, amb);
		return (px_col);
	}
	return (mult_vec(sc->amb_light.light_color, sc->amb_light.intensity));
}

int	create_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}
// Specular
t_point3d specular(t_world *scene, t_inter_data intersection, t_light_source *light)
{
    t_point3d light_to_hit;         // Vector from light to intersection point
    t_point3d normalized_light_dir; // Normalized direction of light
    t_point3d view_vector;          // Direction from intersection point to camera
    t_point3d reflection_vector;    // Reflected light direction
    double specular_intensity;  // Calculated specular intensity
    t_point3d specular_color;       // Resultant specular color

    // Calculate the vector from light source to the intersection point
    light_to_hit = sub_vec(light->position, intersection.hit_point);

    // Normalize the light direction
    normalized_light_dir = scale_to_one(light_to_hit);

    // Calculate the view vector (from hit point to camera)
    t_point3d hit_to_camera = sub_vec(intersection.hit_point, scene->camera.origin);
    view_vector = scale_to_one(hit_to_camera);
    // Calculate the reflection vector
    t_point3d scaled_normal = mult_vec(intersection.normal, 2 * dot_product(intersection.normal, normalized_light_dir));
    reflection_vector = sub_vec(scaled_normal, normalized_light_dir);
    // Calculate the specular intensity using the reflection and view vectors
    specular_intensity = pow(dot_product(reflection_vector, view_vector), 50) * light->brightness * 0.5;
    // Calculate the specular color by scaling the light color
    specular_color = mult_vec(light->light_color, specular_intensity);
    return specular_color;
}
//Garbedge collector
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

void initialize_scene_fields(t_world *scene)
{
    scene->objs = NULL;
    scene->amb_light.light_count = 0;
    scene->camera.cam_count = 0;
    scene->light = NULL;
}
t_world *allocate_scene(void)
{
    t_world *scene;

    garbage_collector = NULL;
    scene = gc_malloc(&garbage_collector, sizeof(t_world));
    if (!scene)
        return (NULL);
    initialize_scene_fields(scene);
    return (scene);
}

// Allocate object

void init_object_vec(t_scene_element *object)
{
    reset_vec(&(object->color));
    reset_vec(&(object->center));
    reset_vec(&(object->direction));
    reset_vec(&(object->param));//
    object->texture.has_checkerboard = 0;
}

t_scene_element *allocate_object(t_world *scene)
{
    t_scene_element *new_object;

    new_object = gc_malloc(&garbage_collector, sizeof(t_scene_element));
    if (!new_object)
        return (NULL);
    init_object_vec(new_object);
    new_object->next = scene->objs;
    scene->objs = new_object;
    return (new_object);
}


t_heap_track **create_and_append(t_heap_track **garbage_collector, void *allocated_memory)
{
    t_heap_track *new_node;
    t_heap_track *temp;

    // Create a new collector node
    new_node = malloc(sizeof(t_heap_track));
    if (!new_node)
        return (NULL);
    new_node->addr = allocated_memory;
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
void *gc_malloc(t_heap_track **garbage_collector, size_t size)
{
    void *allocated_memory;

    allocated_memory = malloc(size);
    if (!allocated_memory)
        return (NULL);
    return (create_and_append(garbage_collector, allocated_memory), allocated_memory);
}

// Cleanup all memory tracked by the garbage collector
void gc_cleanup(t_heap_track **garbage_collector, t_heap_track *collector_node)
{
    if (!collector_node)
        return;
    gc_cleanup(garbage_collector, collector_node->next);
    free(collector_node->addr);
    free(collector_node);
}
//GNL

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

// Helper function to handle the reading of characters and building the line
static char *read_line(int fd, char *line)
{
    char c;

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

    return (line);
}

// Main line function
char *line(int fd)
{
    static char *line = NULL;

    // Free the previous line if it exists.
    if (line)
    {
        free(line);
        line = NULL;
    }

    // Read characters and build the line.
    line = read_line(fd, line);

    // Return the constructed line (or NULL if nothing was read).
    return (line);
}
//mlx

void	image_init(t_tracer	*info)
{
	info->data.mlx = mlx_init();
	info->data.win = mlx_new_window(info->data.mlx, WIDTH, HEIGHT, "MiniRT");
	info->frame.mlx_img = mlx_new_image(info->data.mlx, WIDTH, HEIGHT);
	info->frame.pixel_buffer = mlx_get_data_addr(info->frame.mlx_img, &info->frame.color_depth,
			&info->frame.stride, &info->frame.byte_order);
}

void	my_mlx_pixel_put(t_canvas *data, int x, int y, int color)
{
	char	*dst;

	dst = data->pixel_buffer + (y * data->stride + x * (data->color_depth / 8));
	*(unsigned int *)dst = color;
}

int	esc_key(int key, t_vars *vars)
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
//objects_intersections

//-----//intersection

t_inter_data find_closest_intersection(t_ray *ray, t_world *scene)
{
    t_inter_data closest_inter;
    t_scene_element *current_obj;
    t_inter_data temp_inter;
    t_scene_element *closest_obj;

    closest_obj = NULL;
    closest_inter.t = -1.0;
    current_obj = scene->objs;

    while (current_obj)
    {
        temp_inter = closest_inter;

        if (current_obj->type == SPHERE)
            temp_inter = calc_sphere_normal(closest_inter, current_obj, ray);
        if (current_obj->type == PLAN)
            temp_inter = calc_plan_normal(closest_inter, current_obj, ray);
        if (current_obj->type == CYLINDER)
            temp_inter = calc_cylinder_normal(closest_inter, current_obj, ray);
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
       
        if (closest_obj->texture.has_checkerboard)
            closest_inter.color = apply_checkerboard(&closest_inter, &closest_obj->texture);
    }
    return closest_inter;
}
//cylinder 

double calculate_cylinder_intersection(t_cyl_calc cylinder_calc, t_ray *ray, t_scene_element *cylinder)
{
    double t1 = (-cylinder_calc.quad_b + sqrt(cylinder_calc.delta)) / (2 * cylinder_calc.quad_a);
    double t2 = (-cylinder_calc.quad_b - sqrt(cylinder_calc.delta)) / (2 * cylinder_calc.quad_a);
    
    // Calculate intersection heights
    t_point3d axis = scale_to_one(cylinder->direction);
    double y1 = dot_product(ray->direction, axis) * t1 
                + dot_product(cylinder_calc.ray_to_center, axis);
    double y2 = dot_product(ray->direction, axis) * t2 
                + dot_product(cylinder_calc.ray_to_center, axis);

    // Check height bounds for closest intersection point
    if (t2 > EPSILON && y2 >= 0 && y2 <= cylinder->param.y_coord)
        return t2;
    if (t1 > EPSILON && y1 >= 0 && y1 <= cylinder->param.y_coord)
        return t1;

    return (-1.0);
}

double find_cylinder_intersection(t_ray *ray, t_scene_element *cylinder)
{
    t_cyl_calc calc;
    
    calc.norm_axis = scale_to_one(cylinder->direction);
    calc.ray_to_center = sub_vec(ray->origin, cylinder->center);

    double dot_dir_axis = dot_product(ray->direction, calc.norm_axis);
    double dot_oc_axis = dot_product(calc.ray_to_center, calc.norm_axis);
    
    calc.quad_a = dot_product(ray->direction, ray->direction) 
                  - (dot_dir_axis * dot_dir_axis);
    calc.quad_b = 2 * (dot_product(ray->direction, calc.ray_to_center) 
                  - (dot_dir_axis * dot_oc_axis));
    calc.quad_c = dot_product(calc.ray_to_center, calc.ray_to_center)
                  - (dot_oc_axis * dot_oc_axis) 
                  - pow(cylinder->param.x_coord / 2, 2);

    calc.delta = calc.quad_b * calc.quad_b - 4 * calc.quad_a * calc.quad_c;

    if (calc.delta < EPSILON || calc.quad_a == 0)
        return (-1.0);

    return calculate_cylinder_intersection(calc, ray, cylinder);
}

t_inter_data calc_cylinder_normal(t_inter_data closest_hit, t_scene_element *cylinder, t_ray *ray)
{
    t_inter_data current_hit;
    double hit_height;
    t_point3d cyl_axis;

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
//plan

double calc_pl_ray_inter(t_ray *ray, t_scene_element *plane)
{
    t_point3d ray_to_plane;
    t_point3d plane_norm;
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

t_inter_data calc_plan_normal(t_inter_data closest_hit, t_scene_element *plane, t_ray *ray)
{
    t_inter_data current_hit;
    t_inter_data new_hit;
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
        if (dot_product(ray->direction, current_hit.normal) > __DBL_EPSILON__)
        {
            current_hit.normal = scale_to_one(
                                    mult_vec(plane->direction, -1));
        }
        new_hit.obj_type = PLAN;
        // Update the closest intersection with this plane
        closest_hit = current_hit;
    }

    return (closest_hit);
}

//sphere

double calc_sp_ray_inter(t_ray *ray, t_scene_element *sphere)
{
    t_sph_calc calc;
    t_point3d ray_to_center;
    double radius;

    ray_to_center = sub_vec(ray->origin, sphere->center); // Vector from ray origin to sphere center
    radius = sphere->param.x_coord / 2.0; // Radius of the sphere

    calc.quad_a = dot_product(ray->direction, ray->direction); // Ray direction magnitude squared
    calc.quad_b = 2.0 * dot_product(ray_to_center, ray->direction); // Linear coefficient
    calc.quad_c = dot_product(ray_to_center, ray_to_center) - (radius * radius); // Distance offset

    calc.delta = calc.quad_b * calc.quad_b - (4 * calc.quad_a * calc.quad_c); // Discriminant

    // If discriminant is negative, no intersection
    if (calc.delta < EPSILON)
        return (-1);

    // Compute possible intersection distances
    calc.hit1 = (-calc.quad_b - sqrt(calc.delta)) / (2.0 * calc.quad_a);
    calc.hit2 = (-calc.quad_b + sqrt(calc.delta)) / (2.0 * calc.quad_a);

    // Determine the closest valid intersection point
    if (calc.hit1 * calc.hit2 > EPSILON) // Both intersections are positive
    {
        if (calc.hit1 > EPSILON)
            return (find_min(calc.hit1, calc.hit2));
        return (-1); // No valid intersection
    }

    if (calc.hit1 > EPSILON) // First intersection is valid
        return (calc.hit1);

    return (calc.hit2); // Second intersection is valid
}

t_inter_data calc_sphere_normal(t_inter_data current_hit, t_scene_element *sphere, t_ray *ray)
{
    t_inter_data new_hit;

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

//shadow

int	ray_is_inside(t_point3d ray, t_point3d s_norm)
{
	if (dot_product(ray, s_norm) > 0)
		return (1);
	return (0);
}

int	is_point_in_shadow(t_world *scene, t_inter_data intersection, t_light_source *light_source)
{ 
	t_point3d		vector_to_light;
	t_ray		shadow_ray;
	t_inter_data		shadow_hit;
	t_point3d		vector_to_shadow_hit;

	// Calculate the vector from the intersection point to the light source
	vector_to_light = sub_vec(light_source->position, intersection.hit_point);
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

t_point3d	diffuse(t_inter_data inter, t_light_source *light, double d)
{
	t_point3d	diff;

	diff = scale_and_combine_colors(inter.color, light->light_color, d * light->brightness);
	return (diff);
}

// raytracing:
//----//ft_render

void	ft_render(t_world *sc)
{
	t_tracer	info;

	info.camera = set_camera(sc);
	image_init(&info);
	ft_draw(&info, sc);
	mlx_put_image_to_window(info.data.mlx, info.data.win, info.frame.mlx_img, 0, 0);
	mlx_key_hook(info.data.win, esc_key, &info.data);
	mlx_hook(info.data.win, 17, 0, cross_button, &info.data);
	mlx_loop(info.data.mlx);
}

///supersimpling

t_ssaa_config	init_ssaa_config(void)
{
	t_ssaa_config	config;

	config.samples_per_side = 2;
	config.total_samples = config.samples_per_side * config.samples_per_side;
	config.subpixel_step = 1.0 / config.samples_per_side;
	config.inv_total_samples = 1.0 / config.total_samples;
	return (config);
}

t_point3d process_sample_row(t_ray_trace_context *ctx, int sy)
{
    t_point3d   color;
    t_point3d   sample_color;
    int         sx;

    color = (t_point3d){0, 0, 0};
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
t_point3d    process_pixel_with_ssaa(int x, int y, t_cam_matrix *cam, t_world *scene)
{
    t_ray_trace_context    ctx;
    t_point3d                  color;
    t_point3d                  row_color;
    t_ssaa_config         config;
    int                    sy;

    config = init_ssaa_config();
    init_pixel_context(&ctx, &config, cam, scene);
    set_pixel_coords(&ctx, x, y);
    color = (t_point3d){0, 0, 0};
    sy = 0;
    while (sy < config.samples_per_side)
    {
        row_color = process_sample_row(&ctx, sy);
        color = vec_addition(color, row_color);
        sy++;
    }
    return (mult_vec(color, config.inv_total_samples));
}

void	*render_section(void *arg)
{
	t_thread_data	*data;
	int				x;
	int				y;
	t_point3d	    color;

	data = (t_thread_data *)arg;
	y = data->start_row;
	while (y < data->end_row)
	{
		x = 0;
		while (x < WIDTH)
		{
			// Process pixel with SSAA
			color = process_pixel_with_ssaa(x, y, &data->info->camera, data->scene);
			// Write the final color to the pixel
			my_mlx_pixel_put(&data->info->frame, x, HEIGHT - 1 - y,
							 create_rgb(color.x_coord, color.y_coord, color.z_coord));
			x++;
		}
		y++;
	}
	return (NULL);
}

//supersimpling1

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
t_point3d	trace_sample_ray(t_ray_trace_context *ctx)
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
void init_pixel_context(t_ray_trace_context *ctx, t_ssaa_config *config, t_cam_matrix *cam, t_world *scene)
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
t_point3d process_single_sample(t_ray_trace_context *ctx, int sx, int sy)
{
    ctx->sx = sx;
    ctx->sy = sy;
    return (trace_sample_ray(ctx));
}
//threads

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

void init_thread_data_array(t_thread_data *thread_data, t_world *sc, t_tracer *info, int rows_per_thread)
{
    t_thread_info thread_info;
    pthread_mutex_t render_mutex;
    int i;

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
}

void ft_draw(t_tracer *info, t_world *sc)
{
    pthread_t       threads[NUM_THREADS];
    t_thread_data   thread_data[NUM_THREADS];
    int             rows_per_thread;

    // Ceiling division for even distribution
    rows_per_thread = (HEIGHT + NUM_THREADS - 1) / NUM_THREADS;
    // Initialize thread data array
    init_thread_data_array(thread_data, sc, info, rows_per_thread);
    // Create and join threads
    create_threads(threads, thread_data);
    join_threads(threads);
    // Destroy the mutex after all threads are done
    pthread_mutex_destroy(&thread_data[0].render_mutex);
}