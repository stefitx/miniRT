/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:36:36 by atudor            #+#    #+#             */
/*   Updated: 2024/09/18 09:36:39 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minirt.h"
#include <math.h>

void draw_image(t_mlx_data *mlx_data)
{

	int i = 0;
	int j = 0;
	int iter = 0;

	while (i < mlx_data->mlx->width)
	{
		printf("i: %d\n", i);
		j = 0;
		while (j < mlx_data->mlx->height)
		{
			printf("intersection: %d\n", mlx_data->pixel_map->intersection[iter]);
			if (mlx_data->pixel_map->intersection[iter] == true)
				mlx_put_pixel(mlx_data->img, i, j, 0xFF0000);
			iter++;
			j++;
		}
		i++;
	}
}

t_scene	init_scene(void)
{
	t_scene scene;
	int nr_objects = 1;
	int light_count = 0;

	scene.camera.origin.x = -50.f;
	scene.camera.origin.y = 0.f;
	scene.camera.origin.z = 20.f;
	scene.camera.orientation.x = 0.f;
	scene.camera.orientation.y = 1.f;
	scene.camera.orientation.z = 0.f;
	scene.camera.fov = 70.f;

	scene.light_count = 0;
	scene.lights = NULL;


	scene.object_count = nr_objects;
	scene.light_count = light_count;

	scene.objects = malloc(sizeof(t_object) * nr_objects);
	scene.objects->type = SPHERE;
	
	scene.objects->shape.sphere.center.x = 0.f;
	scene.objects->shape.sphere.center.y = 0.f;
	scene.objects->shape.sphere.center.z = 20.f;
	scene.objects->shape.sphere.radius = 12.6f/2.f;
	scene.objects->shape.sphere.color = 0xFF0000;

	return (scene);
}

t_mlx_data	mlx_minrt_init(void)
{
	mlx_t *mlx;
	mlx_image_t *img;
	t_mlx_data mlx_data;

	mlx = mlx_init(1500, 1500, "miniRT", true);
	//mlx.win = mlx_new_window(mlx.ptr, 1800, 1600, "MiniRT");
	img = mlx_new_image(mlx, 1500, 1500);
	
	mlx_data.mlx = mlx;
	mlx_data.img = img;
	
	return (mlx_data);
}

int main(void)
{
	t_mlx_data mlx_data;
	t_scene scene;

	mlx_data = mlx_minrt_init();
	scene = init_scene();
	mlx_data.scene = scene;
	//printf("camera origin: %f %f %f\n", scene.camera.origin.x, scene.camera.origin.y, scene.camera.origin.z);
	//draw_image(mlx_data, scene);
	camera_setup(&mlx_data, &scene);
	draw_image(&mlx_data);
	mlx_image_to_window(mlx_data.mlx, mlx_data.img, 0, 0);
	mlx_loop(mlx_data.mlx);
	return 0;
}