/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:06:35 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/17 17:27:00 by aalbrech         ###   ########.fr       */
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
	return (intersect);
}

//using ray formula P(t)=O+t⋅D
static void set_intersect_coordinates(t_intersection *intersect, t_ray ray)
{
	if ((*intersect).rayClosestIntersect == INFINITY)
		return ;
	(*intersect).coorinates = vec_add(ray.origin, vec_scale(ray.direction, (*intersect).rayClosestIntersect));
}

//check if a ray hits an object
t_intersection intersect(t_minirt *data, t_ray ray)
{
	t_intersection intersection;
	intersection = init_intersection();

	loop_intersect_spheres(data->objects->spheres, ray, &intersection);
	//plane
	//cylinder
	set_intersect_coordinates(&intersection, ray);

	return (intersection);
}
