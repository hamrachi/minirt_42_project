/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:49:29 by elel-bah          #+#    #+#             */
/*   Updated: 2025/01/30 20:57:40 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

void parse_checkerboard(t_texture *texture, char **args, int start_idx)
{
    if (!args[start_idx])
        return;

    if (!args[start_idx + 1] || !args[start_idx + 2])
        report_error("Invalid checkerboard parameters");

    texture->has_checkerboard = 1;
    texture->checker_size = ft_atod(args[start_idx + 1]);
    texture->color2 = get_color(args[start_idx + 2]);

    if (texture->checker_size <= 0)
        report_error("Checker size must be positive");
}

t_light_source	*alloc_light(t_world *sc)
{
	t_light_source	*new_light;

	new_light = malloc(sizeof(t_light_source));
	if (!new_light)
        report_error("allocation failed\n");
	new_light->next = sc->light;
	sc->light = new_light;
	return (new_light);
}

void parse_light(t_world *scene, char **args)//new
{
    t_light_source *new;

    // Validate light input (args and count)
    validate_light_input(args);
    // Allocate memory for the new light object
    new = alloc_light(scene);
    // Set the light source vector and validate the ratio
    new->position = get_vec(args[1]);
    new->brightness = ft_atod(args[2]);
    // Validate light brightness ratio
    validate_light_ratio(new->brightness);
    // Set the color of the light
    new->light_color = get_color(args[3]);
}

void parse_camera(t_world *scene, char **args)//new__
{
    // Validate camera input (args and count)
    validate_camera_input(args, scene);
    // Increment camera count
    scene->camera.cam_count++;
    // Set camera center and direction vectors
    scene->camera.origin = get_vec(args[1]);
    scene->camera.orientation = get_vec(args[2]);
    // Validate camera orientation
    validate_camera_orientation(scene->camera.orientation);
    // Set and validate the camera FOV
    scene->camera.f_o_v = ft_atod(args[3]);
    validate_camera_fov(scene->camera.f_o_v);
}

// Main function to parse ambient lighting
void parse_ambient(t_world *scene, char **args)//new
{
    // Validate ambient parameters (tokens and count)
    validate_ambient_input(args, scene);
    // Increment ambient count
    scene->amb_light.light_count++;
    // Set ambient lighting ratio
    scene->amb_light.intensity = ft_atod(args[1]);
    // Validate the ambient lighting ratio
    validate_ambient_ratio_range(scene->amb_light.intensity);
    // Set the color for ambient lighting
    scene->amb_light.light_color = get_color(args[2]);
}

void parse_cylinder(t_world *scene, char **args)
{
    t_scene_element *obj;

    validate_cylinder_input(args);
    obj = allocate_object(scene);
    obj->type = CYLINDER;
    obj->center = get_vec(args[1]);
    obj->direction = get_vec(args[2]);

    validate_cylinder_orientation(obj->direction);
    obj->param.x_coord = ft_atod(args[3]);
    obj->param.y_coord = ft_atod(args[4]);
    validate_cylinder_diameter(obj->param.x_coord, obj->param.y_coord);
    obj->color = get_color(args[5]);
    
    // Initialize texture
    obj->texture.has_checkerboard = 0;
    // Parse optional checkerboard parameters
    parse_checkerboard(&obj->texture, args, 6);


}

void parse_sphere(t_world *scene, char **args)
{
    t_scene_element *obj;
    int arg_count = 0;

    // Count the number of arguments
    while (args[arg_count])
        arg_count++;

    // Validate the number of arguments
    if (arg_count != 4 && arg_count != 7)
        report_error("Invalid number of arguments for sphere. Use either:\n"
                     "sp x,y,z diameter r,g,b\n"
                     "or\n"
                     "sp x,y,z diameter r,g,b checker size r2,g2,b2");

    // Validate sphere input (position, diameter, color)
    validate_sphere_input(args);

    // Allocate and initialize the sphere object
    obj = allocate_object(scene);
    obj->type = SPHERE;
    obj->center = get_vec(args[1]);
    obj->param.x_coord = ft_atod(args[2]);
    validate_sphere_diameter(obj->param.x_coord);
    obj->color = get_color(args[3]);

    // Parse optional checkerboard parameters
    if (arg_count == 7)
    {
        if (ft_strcmp(args[4], "checker") == 0)
        {
            obj->texture.has_checkerboard = 1;
            obj->texture.checker_size = ft_atod(args[5]);
            obj->texture.color2 = get_color(args[6]);
        }
        else
        {
            report_error("Invalid sphere format. Use either:\n"
                         "sp x,y,z diameter r,g,b\n"
                         "or\n"
                         "sp x,y,z diameter r,g,b checker size r2,g2,b2");
        }
    }
}

