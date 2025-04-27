/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:06:35 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/27 14:27:40 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

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
Find the intersect of the ray and a sphere, plane or a cylinder, that is closest to the camera.

Return:
A t_hit struct containing important data of the intersection that possibly took place.
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
