/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 14:46:38 by atudor            #+#    #+#             */
/*   Updated: 2024/10/20 14:46:40 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	setup_spheres(t_scene *scene, int num_spheres)
{
	if (num_spheres < 1)
		scene->spheres = NULL;
	else
	{
		scene->spheres = malloc(sizeof(t_sphere) * num_spheres);
		if (!scene->spheres)
			exit(1);
		while (num_spheres > 0)
		{
			scene->spheres[num_spheres - 1] = create_sphere(scene);
			num_spheres--;
		}
	}
}

t_sphere	*create_sphere(t_scene *scene)
{
	t_sphere	*sphere;

	(void)scene;
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		exit(1);
	init_vector(&sphere->center, 100.f, -50.f, 200.f);
	sphere->radius = 50.f;
	init_vector(&sphere->color, 255.f, 0.f, 0.f);
	return (sphere);
}

