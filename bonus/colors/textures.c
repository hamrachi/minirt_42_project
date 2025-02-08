/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 10:10:02 by elel-bah          #+#    #+#             */
/*   Updated: 2025/01/04 18:41:51 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

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
    t_vec result = {0, 0, 0};


    if (!texture)
        return (t_vec){0, 0, 0};
        

    if (!texture->has_image)
        return (t_vec){0, 0, 0};
        

    if (!texture->image)
        return (t_vec){0, 0, 0};
        

    if (!texture->image->addr)
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