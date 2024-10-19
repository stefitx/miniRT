/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:56:44 by atudor            #+#    #+#             */
/*   Updated: 2024/09/18 16:56:46 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

/* ************************************************************************** */
/*                                geometry structures                         */
/* ************************************************************************** */

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_line
{
	t_vector origin;
	t_vector direction;
}	t_line;

typedef struct s_sphere
{
	t_vector	center;
	float		radius;
	t_vector			color;
}	t_sphere;

typedef struct s_plane
{
	t_vector	center;
	t_vector	normal;
	t_vector	color;
}	t_plane;

typedef struct s_cylinder
{
	t_vector	center;
	t_vector	axis;
	float		radius;
	float		height;
	t_vector	color;
}	t_cylinder;

typedef struct s_paraboloid
{
	t_vector	center;
	t_vector	direction;
	float		radius;
	int			color;
}	t_paraboloid;

/* ************************************************************************** */
/*                                scene structures                            */
/* ************************************************************************** */

typedef struct s_light
{
	t_vector	origin;
	double		brightness;
	t_vector	color;
}	t_light;

typedef struct s_camera
{
	t_vector	origin;
	t_vector	orientation;
	double		fov;
}	t_camera;

typedef struct s_scene
{
    t_sphere **spheres;
    t_plane **planes;
    t_cylinder **cylinders;
    t_light **lights;
    t_camera camera;
    double ambient_intensity;
    int num_spheres;
    int num_planes;
    int num_cylinders;
    int num_lights;
}	t_scene;

typedef struct s_pixel_map
{
	t_vector		*pixel_array;
	t_vector		*all_intersections;
	int			*intersection;
}	t_pixel_map;

/* ************************************************************************** */
/*                                mlx structures                              */
/* ************************************************************************** */

typedef struct s_mlx_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_pixel_map	*pixel_map;
	t_scene		scene;
}t_mlx_data;

#endif
