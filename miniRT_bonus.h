/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:01:11 by elel-bah          #+#    #+#             */
/*   Updated: 2025/03/01 19:37:33 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# define BUFFER_SIZE 32
# define HEIGHT 800
# define WIDTH 800
# define EPSILON 0.000001
# define CYLINDER 1
# define PLAN 2
# define SPHERE 3

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "structs_bonus.h"

# define NUM_THREADS 7

//parse_utils

void				validate_camera_input_b(char **args, t_world *scene);
void				validate_camera_orientation_b(t_point3d dir);
void				validate_camera_fov_b(double fov);
void				validate_light_input_b(char **args);
void				validate_light_ratio_b(double ratio);
void				validate_plane_input_b(char **args);
void				validate_plane_orientation_b(t_point3d dir);
void				validate_color_input_b(char **args);
void				validate_color_range_b(t_point3d color);
void				validate_vec_input_b(char **args);
void				validate_sphere_input_b(char **args);
void				validate_sphere_diameter_b(double diameter);
void				validate_cylinder_input_b(char **args);
void				validate_cylinder_orientation_b(t_point3d dir);
void				validate_ambient_ratio_range_b(double ratio);
void				validate_ambient_input_b(char **args, t_world *scene);
void				validate_cylinder_diameter_b(double diameter, \
	double height);

// parse

void				report_error_b(char *str);
int					is_valid_rt_file_b(int ac, char **av);
void				parse_scene_file_b(t_world *sc, int fd);//
void				parse_object_b(char *object_type, char **tokens, \
	t_world *scene);//new
void				parse_plane_b(t_world *sc, char **tockens);
void				parse_cylinder_b(t_world *sc, char **tockens);
void				parse_sphere_b(t_world *sc, char **tockens);
void				parse_light_b(t_world *sc, char **tockens);
void				parse_camera_b(t_world *sc, char **tockens);
void				parse_ambient_b(t_world *sc, char **tockens);
void				parse_scene_shape_b(const char *shape_type, \
	t_world *scene, char **tokens);
void				parse_scene_element_b(char element_type, \
	t_world *scene, char **tokens);

// Allocation functions
t_world				*allocate_scene_b(void);
t_scene_element		*allocate_object_b(t_world *scene);
void				gc_cleanup_b(t_heap_track **g_garbage_collector, \
	t_heap_track *collector_node);
void				*gc_malloc_b(t_heap_track **g_garbage_collector, \
	size_t size);
t_heap_track		*g_garbage_collector;

// tools
int					ft_strlcpy_b(char *dest, const char *source, int max_size);
int					ft_strlen_b(const char *str);
char				*append_char_to_string_b(char *original, char new_char, \
	t_heap_track **g_garbage_collector);
char				*line_b(int fd, t_heap_track **g_garbage_collector);
double				ft_atod_b(const char *str);
int					ft_atoi_b(const char *str);
char				**ft_split_b(const char *input_string, char delimiter, \
	t_heap_track **g_garbage_collector);
void				free_split_b(char **array);
int					ft_strncmp_b(char *s1, const char *s2, size_t n);
int					ft_strcmp_b(const char *str1, const char *str2);

/* camera */

t_cam_matrix		set_camera_b(t_world *sc);
t_ray				ray_primary_b(t_cam_matrix *cam, double v, double u);
t_point3d			ray_at_b(t_ray *ray, double t);
t_point3d			ray_at_b(t_ray *ray, double t);

//vectors

void				reset_vec_b(t_point3d *v);
t_point3d			get_vec_b(char *s);
t_point3d			get_color_b(char *s);
t_point3d			scale_to_one_b(t_point3d v);
t_point3d			sub_vec_b(t_point3d u, t_point3d v);
t_point3d			vec_addition_b(t_point3d v1, t_point3d v2);
t_point3d			mult_vec_b(t_point3d v, double a);
t_point3d			cross_product_b(t_point3d v1, t_point3d v2);//
double				dot_product_b(t_point3d u, t_point3d v);
double				magnitude_b(t_point3d	v);
t_point3d			div_vect_b(t_point3d v, double a);
t_point3d			create_vector_b(double x, double y, double z);

/*rendring */
void				ft_render_b(t_world *sc);

/* intersections*/
double				find_min_b(double first_num, double second_num);
t_inter_data		find_closest_intersection_b(t_ray *ray, t_world *scene);
t_inter_data		calc_sphere_normal_b(t_inter_data current_hit, \
	t_scene_element *sphere, t_ray *ray);

double				calc_sp_ray_inter_b(t_ray *ray, t_scene_element *sphere);
double				calculate_plane_intersection_b(t_ray *ray, \
	t_scene_element *plane);
double				find_cylinder_intersection_b(t_ray *ray, \
	t_scene_element *cylinder);
double				calculate_cylinder_intersection_b(t_cyl_calc cylinder_calc, \
	t_ray *ray, t_scene_element *cylinder);
t_inter_data		calc_plan_normal_b(t_inter_data closest_hit, \
	t_scene_element *plane, t_ray *ray);
t_inter_data		calc_cylinder_normal_b(t_inter_data closest_hit, \
	t_scene_element *cylinder, t_ray *ray);

/* mlx funct */
int					cross_button_b(t_vars *vars);
int					esc_key_b(int key, t_vars *vars);
void				my_mlx_pixel_put(t_canvas *data, int x, int y, int color);
void				image_init_b(t_tracer	*info);

// color
t_point3d			scale_and_combine_colors_b(t_point3d base_color, \
	t_point3d light_color, double intensity_ratio);
int					create_rgb_b(int r, int g, int b);
t_point3d			blend_colors_b(t_point3d color_a, t_point3d color_b);
t_point3d			ray_color_b(t_ray *ray, t_world *sc);
t_point3d			colorize_b(double r, double g, double b);
t_point3d			diffuse_b(t_inter_data inter, t_light_source *light, \
	double d);
int					is_point_in_shadow_b(t_world *scene, \
	t_inter_data intersection, t_light_source *light_source);
//surface normal
int					ray_is_inside_b(t_point3d ray, t_point3d s_norm);
double				calc_pl_ray_inter(t_ray *ray, t_scene_element *plane);

//=-=-=--=threads

void				join_threads_b(pthread_t *threads);
void				create_threads_b(pthread_t *threads, \
	t_thread_data *thread_data);
void				init_thread_data_b(t_thread_data *data, \
	t_thread_info *info);
int					get_thread_end_row_b(int thread_id, int rows_per_thread);
void				init_thread_data_array_b(t_thread_data *thread_data, \
	t_world *sc, t_tracer *info, int rows_per_thread);

//=-=-=-SSAA

t_point3d			process_pixel_with_ssaa_b(int x, int y, \
	t_cam_matrix *cam, t_world *scene);
t_point3d			process_sample_row_b(t_ray_trace_context *ctx, int sy);
t_point3d			process_single_sample_b(t_ray_trace_context *ctx, \
	int sx, int sy);
void				set_pixel_coords_b(t_ray_trace_context *ctx, \
	int x, int y);
void				init_pixel_context_b(t_ray_trace_context *ctx, \
	t_ssaa_config *config, t_cam_matrix *cam, t_world *scene);
t_ssaa_config		init_ssaa_config_b(void);
//=-=-=--=Draw
void				ft_draw_b(t_tracer *info, t_world *sc);
void				*render_section_b(void *arg);
t_point3d			trace_sample_ray_b(t_ray_trace_context *ctx);
t_ray_params		calculate_ray_params_b(t_ray_trace_context *ctx);
t_point3d			specular_b(t_world *scene, \
	t_inter_data intersection, t_light_source *light);
t_point3d			apply_checkerboard_b(t_inter_data *intersection, \
	t_texture *texture);
void				parse_checkerboard_b(t_texture *texture, \
	char **args, int start_idx);

#endif
