/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:37:33 by atudor            #+#    #+#             */
/*   Updated: 2024/09/18 09:37:36 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "../inc/MLX42/include/MLX42/MLX42.h"
# include "structs.h"

// Function prototypes
// void draw_image(t_img img);
// void render_scene(t_mlx mlx);

void	camera_setup(t_mlx_data *mlx_data, t_scene *scene);



#endif