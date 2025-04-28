/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:06:35 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/28 11:33:15 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

static void	loop_intersect_spheres(t_sphere *spheres,
		t_ray ray, t_hit *intersection)
{
	t_sphere	*current;
	float		temp;

	if (!spheres)
		return ;
	current = spheres;
	while (current != NULL)
	{
		temp = intersect_sphere(current, ray);
		if (temp < (*intersection).closest_intersect && temp > -1.0)
		{
			(*intersection).object.spheres = current;
			set_intersection_data(intersection, current->rgb, temp, ray);
			(*intersection).surface_normal = vec_normalize(vec_sub(
						(*intersection).coordinates, current->center));
			//test
			if (vec_dot(ray.dir, (*intersection).surface_normal) > 0.0)
				(*intersection).surface_normal = vec_scale((*intersection).surface_normal, -1);
		}
		current = current->next;
	}
}

static void	loop_intersect_planes(t_plane *planes,
	t_ray ray, t_hit *intersection)
{
	t_plane	*current;
	float	temp;

	if (!planes)
		return ;
	current = planes;
	while (current != NULL)
	{
		temp = intersect_plane(current, ray);
		if (temp < (*intersection).closest_intersect && temp > -1.0)
		{
			(*intersection).object.planes = current;
			set_intersection_data(intersection, current->rgb, temp, ray);
			if (vec_dot(ray.dir, current->orientation) > 0)
				(*intersection).surface_normal = vec_scale(
						current->orientation, -1);
			else
				(*intersection).surface_normal = current->orientation;
		}
		current = current->next;
	}
}

static void	loop_intersect_cylinders(t_cylinder *cylinders,
	t_ray ray, t_hit *intersection)
{
	t_cylinder	*current;
	float		temp;

	if (!cylinders)
		return ;
	current = cylinders;
	while (current != NULL)
	{
		temp = intersect_cylinder(current, ray);
		if (temp < (*intersection).closest_intersect && temp > -1.0)
		{
			(*intersection).object.cylinders = current;
			set_intersection_data(intersection, current->rgb, temp, ray);
			set_cyl_intersect_surface_normal(current, intersection, ray);
		}
		current = current->next;
	}
}

static t_hit	init_hit_struct(void)
{
	t_hit	intersect;

	intersect.object.spheres = NULL;
	intersect.object.planes = NULL;
	intersect.object.cylinders = NULL;
	intersect.closest_intersect = INFINITY;
	intersect.coordinates = (t_xyz){0, 0, 0};
	intersect.rgb = (t_xyz){0, 0, 0};
	intersect.surface_normal = (t_xyz){0, 0, 0};
	return (intersect);
}

/*
Arguments:
The t_minirt struct containing of important program data.
A ray going from the camera in the direction of a certain pixel on the screen.

Description:
Find the intersect of the ray and a sphere, plane or a cylinder,
that is closest to the camera.

Return:
A t_hit struct containing important data of the
intersection that possibly took place.
Ex. coordinates of the intersection.
*/
t_hit	intersect(t_minirt *data, t_ray ray)
{
	t_hit	intersection;

	intersection = init_hit_struct();
	loop_intersect_spheres(data->objects->spheres, ray, &intersection);
	loop_intersect_planes(data->objects->planes, ray, &intersection);
	loop_intersect_cylinders(data->objects->cylinders, ray, &intersection);
	return (intersection);
}
