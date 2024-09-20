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

	printf("mlx_data->mlx->width: %d\n", mlx_data->mlx->width);
	printf("mlx_data->mlx->height: %d\n", mlx_data->mlx->height);
	while (i < mlx_data->mlx->width)
	{
		//printf("i: %d\n", i);
		j = 0;
		while (j < mlx_data->mlx->height)
		{
			//printf("intersection: %d\n", mlx_data->pixel_map->intersection[iter]);
			if (mlx_data->pixel_map->intersection[iter] == true)
			{
				printf("intersection: %d\n", mlx_data->pixel_map->intersection[iter]);
				mlx_put_pixel(mlx_data->img, i, j, 0xFF0000ff);
			}
			else
				mlx_put_pixel(mlx_data->img, i, j, 0x000000ff);
			iter++;
			j++;
		}
		i++;
	}
	for(int line = 25; line < mlx_data->mlx->width - 25; line++)
	{
		mlx_put_pixel(mlx_data->img, line, 50, 0xFF0000);
		mlx_put_pixel(mlx_data->img, line, mlx_data->mlx->height - 50, 0xFF0000);
	}
//	mlx_image_to_window(mlx_data->mlx, mlx_data->img, 0, 0);
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
	scene.camera.orientation.y = 0.f;
	scene.camera.orientation.z = 1.f;
	scene.camera.fov = 100.f;

	scene.light_count = 0;
	scene.lights = NULL;


	scene.object_count = nr_objects;
	scene.light_count = light_count;

	scene.objects = malloc(sizeof(t_object) * nr_objects);
	scene.objects->type = SPHERE;
	
	scene.objects->shape.sphere.center.x = 0.f;
	scene.objects->shape.sphere.center.y = 0.f;
	scene.objects->shape.sphere.center.z = 20.f;
	scene.objects->shape.sphere.radius = 30.6f/2.f;
	scene.objects->shape.sphere.color = 0xFF0000ff;

	return (scene);
}

void key_events(void* param)
{
	mlx_t		 *mlx;
	
	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}


int main(void)
{
	t_mlx_data mlx_data;
	t_scene scene;

	//mlx_data = mlx_minrt_init();
	scene = init_scene();
	mlx_data.scene = scene;
	mlx_t *mlx;
	mlx_image_t *img;
	//t_mlx_data mlx_data;

	mlx = mlx_init(1000, 1000, "miniRT", true);
	img = mlx_new_image(mlx, 1000, 1000);
	mlx_loop_hook(mlx, key_events, &mlx);
	mlx_image_to_window(mlx, img, 0, 0);
	printf("img address: %p\n", img);
	mlx_data.mlx = mlx;
	mlx_data.img = img;
	//printf("camera origin: %f %f %f\n", scene.camera.origin.x, scene.camera.origin.y, scene.camera.origin.z);
	camera_setup(&mlx_data, &scene);
	draw_image(&mlx_data);
	printf("img address FINAL: %p\n", mlx_data.img);
	
	mlx_loop(mlx_data.mlx);
	//printf("Hello, world!\n");
	return 0;
}