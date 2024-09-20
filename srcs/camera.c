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

bool ray_cast(t_mlx_data *mlx_data, t_vector direction)
{
   float t1;
   float t2;
   float a;
   float b;
   float c;
   t_vector sphere = mlx_data->scene.objects->shape.sphere.center;

	//printf("heyaya\n");
	a = pow(direction.x, 2) + pow(direction.y, 2) + pow(direction.z, 2);
	printf("a: %f\n", a);
	b = 2 * ((mlx_data->scene.camera.origin.x - sphere.x) * direction.x
		+ (mlx_data->scene.camera.origin.y - sphere.y) * direction.y
		+ (mlx_data->scene.camera.origin.z - sphere.z) * direction.z);
	printf("b: %f\n", b);
	c = pow(mlx_data->scene.camera.origin.x - sphere.x, 2)
		+ pow(mlx_data->scene.camera.origin.y - sphere.y, 2)
		+ pow(mlx_data->scene.camera.origin.z - sphere.z, 2)
		- pow(mlx_data->scene.objects->shape.sphere.radius, 2);
	printf("c: %f\n", c);
	float discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return (false);
	t1 = (-b + sqrt(discriminant)) / (2 * a);
	t2 = (-b - sqrt(discriminant)) / (2 * a);
	if (t1 < 0 && t2 < 0)
	{
		printf("No intersection\n");
		return (false);
	}
	printf("intersection");
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
	if (mlx_data->scene.camera.orientation.x == 1 || mlx_data->scene.camera.orientation.x == -1) 
	{
		pixel.x = -1 * mlx_data->scene.camera.orientation.x;
		pixel.y = (2 * u - 1) * half_width;
		pixel.z = (1 - 2 * v) * half_width;
	}
	else if (mlx_data->scene.camera.orientation.y == 1 || mlx_data->scene.camera.orientation.y == -1)
	{
		pixel.x = (2 * u - 1) * half_width;
		pixel.y = -1 * mlx_data->scene.camera.orientation.y;
		pixel.z = (1 - 2 * v) * half_width;
	}
	else if (mlx_data->scene.camera.orientation.z == 1 || mlx_data->scene.camera.orientation.z == -1)
	{
		pixel.x = (2 * u - 1) * half_width;
		pixel.y = (1 - 2 * v) * half_width;
		pixel.z = -1 * mlx_data->scene.camera.orientation.z;
	}

	//printf("Pixel: %f %f %f\n", pixel.x, pixel.y, pixel.z);

	//get direction
	//printf("Camera origin: %f %f %f\n", mlx_data.scene.camera.origin.x, mlx_data.scene.camera.origin.y, mlx_data.scene.camera.origin.z);
	direction.x = pixel.x - mlx_data->scene.camera.origin.x;
	direction.y = pixel.y - mlx_data->scene.camera.origin.y;
	direction.z = pixel.z - mlx_data->scene.camera.origin.z;
	//normalize direction
	float magnitude = sqrt(pow(direction.x, 2) + pow(direction.y, 2) + pow(direction.z, 2));
	//printf("Magnitude: %f\n", magnitude);
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
	    int width = mlx_data->mlx->width;
    int height = mlx_data->mlx->height;

	(void)scene;

	  t_vector *direction = malloc(sizeof(t_vector) * width * height);
    if (!direction) return NULL;

    mlx_data->pixel_map = malloc(sizeof(t_pixel_map));
    if (!mlx_data->pixel_map) return NULL;

    mlx_data->pixel_map->pixel_array = malloc(sizeof(t_vector) * width * height);
    if (!mlx_data->pixel_map->pixel_array) return NULL;

    mlx_data->pixel_map->intersection = malloc(sizeof(int) * width * height);
    if (!mlx_data->pixel_map->intersection) return NULL;
	i = 0;
	while (i < mlx_data->mlx->width)
	{
		j = 0;
		while (j < mlx_data->mlx->height)
		{
			direction[iter] = get_pixel_direction(mlx_data, i, j, half_width);
			//pixel_map.pixel_array = malloc(sizeof(t_vector) * mlx_data->mlx->width * mlx_data->mlx->height);
			 mlx_data->pixel_map->pixel_array[iter].x = i;
			 mlx_data->pixel_map->pixel_array[iter].y = j;
			 mlx_data->pixel_map->pixel_array[iter].z = 0;
			//printf("Direction: %f %f %f\n", direction[iter].x, direction[iter].y, direction[iter].z);
			 
			 mlx_data->pixel_map->intersection[iter] = ray_cast(mlx_data, direction[iter]);
			 printf("Intersection: %d\n", mlx_data->pixel_map->intersection[iter]);
			// if (pixel_map.intersection[iter] == 1)
			// 	mlx_put_pixel(mlx_data->img, i, j, 0xFF0000);
			//printf("here\n");
			iter++;
			j++;
		}
		i++;
	}
	return (direction);
}

void	camera_setup(t_mlx_data *mlx_data, t_scene *scene)
{
	//fov stuff
	//int half_width;
	t_vector *direction;
	///printf("Camera origin: %f %f %f\n", mlx_data->scene.camera.origin.x, mlx_data->scene.camera.origin.y, mlx_data->scene.camera.origin.z);
	float half_width = tan((scene->camera.fov * M_PI / 180.0) / 2.0);
	direction = pixel_direction(mlx_data, scene, half_width);
}



// tie camera direction to pixel direction
