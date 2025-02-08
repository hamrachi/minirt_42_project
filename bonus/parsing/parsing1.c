/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:49:29 by elel-bah          #+#    #+#             */
/*   Updated: 2025/01/04 16:19:09 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"


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


// // Helper function to parse checkerboard parameters
// void parse_checkerboard(t_texture *texture, char **args, int start_idx)
// {
//     if (!args[start_idx])
//         return;
    
//     // Check if it's a checkerboard texture
//     if (ft_strcmp(args[start_idx], "checker") == 0) {
//         if (!args[start_idx + 1] || !args[start_idx + 2])
//             report_error("Invalid checkerboard parameters");
            
//         texture->has_checkerboard = 1;
//         texture->checker_size = ft_atod(args[start_idx + 1]);
//         texture->color2 = get_color(args[start_idx + 2]);
        
//         if (texture->checker_size <= 0)
//             report_error("Checker size must be positive");
//     }
// }

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

// void parse_cylinder(t_scene *scene, char **args)//new
// {
//     t_objs *obj;

//     // Validate cylinder input (args and count)
//     validate_cylinder_input(args);
//     // Allocate memory for the new cylinder object
//     obj = allocate_object(scene);
//     obj->type = CYLINDER;
//     // Set cylinder center and direction
//     obj->center = get_vec(args[1]);
//     obj->direction = get_vec(args[2]);
//     // Validate cylinder orientation
//     validate_cylinder_orientation(obj->direction);
//     // Set cylinder diameter and height
//     obj->p.x = ft_atod(args[3]);
//     obj->p.y = ft_atod(args[4]);
//     // Validate cylinder diameter and height
//     validate_cylinder_diameter(obj->p.x, obj->p.y);
//     // Set the cylinder color
//     obj->color = get_color(args[5]);
// }


void parse_sphere(t_scene *scene, char **args)
{
    t_objs *obj;

    validate_sphere_input(args);
    obj = allocate_object(scene);
    obj->type = SPHERE;
    obj->center = get_vec(args[1]);
    obj->p.x = ft_atod(args[2]);
    validate_sphere_diameter(obj->p.x);
    obj->color = get_color(args[3]);
    
    // Initialize texture
    obj->texture.has_checkerboard = 0;
    obj->texture.has_image = 0;
    // Parse either checkerboard or image texture
    if (args[4])
    {
        if (ft_strcmp(args[4], "checker") == 0)
            parse_checkerboard(&obj->texture, args, 4);
        else if (ft_strcmp(args[4], "texture") == 0)
            parse_texture(&obj->texture, args, 4, scene->mlx);
    }
}

// void parse_sphere(t_scene *scene, char **args)//lastone
// {
//     t_objs *obj;

//     validate_sphere_input(args);
//     obj = allocate_object(scene);
//     obj->type = SPHERE;
//     obj->center = get_vec(args[1]);
//     obj->p.x = ft_atod(args[2]);
//     validate_sphere_diameter(obj->p.x);
//     obj->color = get_color(args[3]);
    
//     // Initialize texture
//     obj->texture.has_checkerboard = 0;
//     // Parse optional checkerboard parameters
//     parse_checkerboard(&obj->texture, args, 4);
// }

// void parse_sphere(t_scene *scene, char **args)//new
// {
//     t_objs *obj;

//     // Validate sphere input (args and count)
//     validate_sphere_input(args);
//     // Allocate memory for the new sphere object
//     obj = allocate_object(scene);
//     obj->type = SPHERE;
//     // Set sphere center and validate the diameter
//     obj->center = get_vec(args[1]);
//     obj->p.x = ft_atod(args[2]);
//     // Validate the sphere diameter
//     validate_sphere_diameter(obj->p.x);

//     // Set the sphere color
//     obj->color = get_color(args[3]);
// }

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
