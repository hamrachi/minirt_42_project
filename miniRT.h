/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:01:11 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/01 09:51:18 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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

void validate_camera_input(char **args, t_world *scene);
void validate_camera_orientation(t_point3d dir);
void validate_camera_fov(double fov);

// void validate_light_input(char **args, t_scene *scene);
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

// allocation

// Garbage collector functions

// Allocation functions
t_world *allocate_scene(void);
t_scene_element *allocate_object(t_world *scene);
void gc_cleanup(t_heap_track **garbage_collector, t_heap_track *collector_node);
void *gc_malloc(t_heap_track **garbage_collector, size_t size);
t_heap_track **create_and_append(t_heap_track **garbage_collector, void *allocated_memory);
// t_collector *create_collector_node(void *allocated_memory);
// t_collector **append_to_collector(t_collector **garbage_collector, void *allocated_memory);
t_heap_track	*garbage_collector;

// tools
int			ft_strlen(const char *str);
char        *append_char_to_string(char *original, char new_char);
char	    *line(int fd);
double		ft_atod(const char *str);
int			ft_atoi(const char *str);
char        **ft_split(const char *input_string, char delimiter);
void	free_split(char **array);
int ft_strncmp(char *first_str, const char *second_str, size_t max_len);
int         ft_strcmp(const char *str1, const char *str2);

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



/* intersections*/
double find_min(double first_num, double second_num);

t_inter_data	find_closest_intersection(t_ray *ray, t_world *scene);


t_inter_data calc_sphere_normal(t_inter_data current_hit, t_scene_element *sphere, t_ray *ray);


double calc_sp_ray_inter(t_ray *ray, t_scene_element *sphere);

double      calculate_plane_intersection(t_ray *ray, t_scene_element *plane);

double      find_cylinder_intersection(t_ray *ray, t_scene_element *cylinder);
// double intersect_cylinder(t_ray *ray, t_objs *cylinder);

double      calculate_cylinder_intersection(t_cyl_calc cylinder_calc, t_ray *ray, t_scene_element *cylinder);
t_inter_data calc_cylinder_normal(t_inter_data closest_hit, t_scene_element *cylinder, t_ray *ray);
// double  pick_cylinder_intersection(t_cylinder cyl_info, t_ray *ray, t_objs *cylinder);

t_inter_data calc_plan_normal(t_inter_data closest_hit, t_scene_element *plane, t_ray *ray);


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
double      calc_pl_ray_inter(t_ray *ray, t_scene_element *plane);
t_inter_data     find_closest_intersection(t_ray *ray, t_world *scene);


//=-=-=--=Draw
/*rendring */
void		ft_render(t_world *sc);
void ft_draw(t_tracer info, t_world *sc);
void	*render_section(void *arg);


#endif