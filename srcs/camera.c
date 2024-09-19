/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 01:37:38 by atudor            #+#    #+#             */
/*   Updated: 2024/09/19 01:37:40 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

bool ray_cast(t_mlx_data *mlx_data, t_vector direction, t_vector pixel)
{
	float t1;
	float t2;
	t_vector ray_origin;
	(void)pixel;

	ray_origin.x = mlx_data->scene.camera.origin.x - mlx_data->scene.objects->shape.sphere.center.x;
	ray_origin.y = mlx_data->scene.camera.origin.y - mlx_data->scene.objects->shape.sphere.center.y;
	ray_origin.z = mlx_data->scene.camera.origin.z - mlx_data->scene.objects->shape.sphere.center.z;

	float b = 2.0f * (ray_origin.x * direction.x + ray_origin.y * direction.y + ray_origin.z * direction.z);
	float c = (ray_origin.x * ray_origin.x + ray_origin.y * ray_origin.y + ray_origin.z * ray_origin.z) - pow(mlx_data->scene.objects->shape.sphere.radius, 2);

	t1 = (-b + sqrt(pow(b, 2) - 4 * c)) / 2;
	t2 = (-b - sqrt(pow(b, 2) - 4 * c)) / 2;

	if (t1 < 0 && t2 < 0)
		return (false);
	return (true);
}

t_vector	get_pixel_direction(t_mlx_data *mlx_data, int i, int j, float half_width)
{
	t_vector pixel;
	t_vector direction;
	float u;
	float v;

	//turn into real world coordinates

	u = (i + 0.5f) / mlx_data->mlx->width;
	//printf("U: %f\n", u);
	v = (j + 0.5f) / mlx_data->mlx->height;
	//printf("V: %f\n", v);

	pixel.x = (2 * u - 1) * half_width;
	pixel.y = (1 - 2 * v) * half_width;
	pixel.z = -1;
	//printf("Pixel: %f %f %f\n", pixel.x, pixel.y, pixel.z);

	//get direction
	//printf("Camera origin: %f %f %f\n", mlx_data.scene.camera.origin.x, mlx_data.scene.camera.origin.y, mlx_data.scene.camera.origin.z);
	direction.x = pixel.x - mlx_data->scene.camera.origin.x;
	direction.y = pixel.y - mlx_data->scene.camera.origin.y;
	direction.z = pixel.z - mlx_data->scene.camera.origin.z;
	//normalize direction
	float magnitude = sqrt(pow(direction.x, 2) + pow(direction.y, 2) + pow(direction.z, 2));
	printf("Magnitude: %f\n", magnitude);
	// Check to avoid division by zero
	if (magnitude != 0) {
		direction.x /= magnitude;
		direction.y /= magnitude;
		direction.z /= magnitude;
	} else {
		// Handle zero-magnitude case appropriately
		direction.x = 0;
		direction.y = 0;
		direction.z = 0;
	}
	return (direction);
	
}

t_vector	*pixel_direction(t_mlx_data *mlx_data, t_scene *scene, float half_width)
{
	int i;
	int j;
	int iter = 0;
	t_pixel_map pixel_map;
	t_vector *direction = malloc(sizeof(t_vector));
	(void)scene;

	pixel_map.pixel_array = malloc(sizeof(t_vector) * mlx_data->mlx->width * mlx_data->mlx->height);
	pixel_map.intersection = malloc(sizeof(int) * mlx_data->mlx->width * mlx_data->mlx->height);
	i = 0;
	while (i < mlx_data->mlx->width)
	{
		j = 0;
		while (j < mlx_data->mlx->height)
		{
			direction[iter] = get_pixel_direction(mlx_data, i, j, half_width);
			pixel_map.pixel_array = malloc(sizeof(t_vector) * mlx_data->mlx->width * mlx_data->mlx->height);
			pixel_map.pixel_array[iter].x = i;
			pixel_map.pixel_array[iter].y = j;
			pixel_map.pixel_array[iter].z = 0;
			printf("Direction: %f %f %f\n", direction[iter].x, direction[iter].y, direction[iter].z);
			pixel_map.intersection[iter] = ray_cast(mlx_data, direction[iter], pixel_map.pixel_array[iter]);
			// if (pixel_map.intersection[iter] == 1)
			// 	mlx_put_pixel(mlx_data->img, i, j, 0xFF0000);
			iter++;
			j++;
		}
		i++;
	}
	mlx_data->pixel_map = &pixel_map;
	return (direction);
}

void	camera_setup(t_mlx_data *mlx_data, t_scene *scene)
{
	//fov stuff
	//int half_width;
	t_vector *direction;
	printf("Camera origin: %f %f %f\n", mlx_data->scene.camera.origin.x, mlx_data->scene.camera.origin.y, mlx_data->scene.camera.origin.z);
	float half_width = tan((scene->camera.fov * M_PI / 180.0) / 2.0);
	direction = pixel_direction(mlx_data, scene, half_width);
}



// tie camera direction to pixel direction
