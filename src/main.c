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

void key_events(void* param)
{
	mlx_t		 *mlx;
	
	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void	init_data(t_data *data, t_scene *scene)
{
	mlx_t *mlx;
	mlx_image_t *img;

	mlx = mlx_init(1000, 1000, "miniRT", true);
	img = mlx_new_image(mlx, 1000, 1000);
	mlx_loop_hook(mlx, key_events, &mlx);
	mlx_image_to_window(mlx, img, 0, 0);
	data->mlx = mlx;
	data->img = img;
	data->scene = scene;
	//setup FOV (calculate image plane)
	data->scale = tan(data->scene->camera->fov / 2 * M_PI / 180);
	data->aspect_ratio = data->img->width / data->img->height;
	mlx = mlx_init(1000, 1000, "miniRT", true);
	img = mlx_new_image(mlx, 1000, 1000);
}


int main(void)
{
	t_data data;
	t_scene scene;
	

	// ERIK
	// Parse command line arguments
	// Read the scene file
	// Parse the scene file
    // Initialize the scene 
	//-> idk, modify create_scene(&scene), create_sphere, create_camera, create_plane, create_lights, create_cylinder
	
	create_scene(&scene);

	init_data(&data, &scene);

	// Render the scene
	render_engine(&data);

    // Display or save the rendered image
	//mlx_display_image(mlx_data.img);

    // Free memory and cleanup
	
	mlx_loop(data.mlx);
	return 0;
}


