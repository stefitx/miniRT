/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_engine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:11:30 by atudor            #+#    #+#             */
/*   Updated: 2024/10/20 16:11:33 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include <math.h>

void	render_engine(t_data *data)
{
	int	x;
	int	y;
	t_ray	ray;
	int	aspect_ratio;
	double	scale;

	
	
	// loop through each pixel in the image
	y = 0;
	while (y < data->img->height)
	{
		x = 0;
		while (x < data->img->width)
		{
			ray = create_ray(data, x, y);
			// generate ray from camera to pixel
			// calculate direction
			// create ray and check for intersections
			// get color
			// put pixel on image
			x++;
		}
		y++;
	}
	// generate ray from camera to pixel
	// calculate direction
	// create ray and check for intersections
	// get color
	// put pixel on image
}
