/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:01:11 by elel-bah          #+#    #+#             */
/*   Updated: 2025/01/09 13:16:13 by elel-bah         ###   ########.fr       */
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
int			esc_key(int key, t_vars *vars);
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


void parse_texture(t_texture *texture, char **args, int start_idx, void *mlx);
t_img_data *load_texture(void *mlx, char *path);
t_vec get_texture_color(t_texture *texture, double u, double v);
void calculate_texture_coords(t_inter *intersection, t_objs *obj, double *u, double *v);
t_vec apply_texture(t_inter *intersection, t_texture *texture, t_objs *obj);


#endif