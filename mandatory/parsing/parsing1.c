/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:49:29 by elel-bah          #+#    #+#             */
/*   Updated: 2024/12/23 18:24:39 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

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


// void parse_light(t_scene *scene, char **args)//new
// {
//     t_light *new;

//     // Validate light input (args and count)
//     // validate_light_input(args);
//     validate_light_input(args, scene);
//     // Allocate memory for the new light object
//     new = alloc_light(scene);
//     // Set the light source vector and validate the ratio
//     new->src = get_vec(args[1]);
//     new->ratio = ft_atod(args[2]);
//     // Validate light brightness ratio
//     validate_light_ratio(new->ratio);
//     // Set the color of the light
//     new->col = get_color(args[3]);
// }

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