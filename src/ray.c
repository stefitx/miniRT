/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:21:10 by atudor            #+#    #+#             */
/*   Updated: 2024/10/20 17:21:12 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

t_vector	calculate_direction(t_vector camera_o, double ndc_x, double ndc_y, t_data *data)
{


t_ray	create_ray(t_data *data, int x, int y)
{
	t_ray	direction;
	double	ndc_x;
	double	ndc_y;
	t_vector	camera_o;

	camera_o = data->scene->camera->orientation;
	ndc_x = normal_dev_coordinates(x, data, data->aspect_ratio, 0) * data->scale;
	ndc_y = normal_dev_coordinates(y, data, data->aspect_ratio, 1) * data->scale;
	ray.direction = calculate_direction(camera_o, ndc_x, ndc_y, data);
	return (normalize_vector(ray.direction.x, ray.direction.y, ray.direction.z));
}