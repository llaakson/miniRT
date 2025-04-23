/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:06:35 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/23 13:26:50 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"



static t_intersection init_intersection(void)
{
	t_intersection intersect;

	intersect.object.spheres = NULL;
	intersect.object.planes = NULL;
	intersect.object.cylinders = NULL;
	intersect.rayClosestIntersect = INFINITY;
	intersect.coorinates = (t_xyz){0,0,0};
	intersect.RGB = (t_xyz){0,0,0};
	intersect.surface_normal = (t_xyz){0,0,0};
	return (intersect);
}

//check if a ray hits an object
t_intersection intersect(t_minirt *data, t_ray ray)
{
	t_intersection intersection;
	intersection = init_intersection();

	loop_intersect_spheres(data->objects->spheres, ray, &intersection);
	loop_intersect_planes(data->objects->planes, ray, &intersection);
	loop_intersect_cylinders(data->objects->cylinders, ray, &intersection);

	return (intersection);
}
