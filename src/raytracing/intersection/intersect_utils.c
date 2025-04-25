/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 22:15:14 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/25 10:33:55 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

void	set_intersection_data(t_intersection *intersect, t_xyz RGB, float closest_intersect, t_ray ray)
{
	(*intersect).rayClosestIntersect = closest_intersect;
	(*intersect).RGB = RGB;
	(*intersect).coorinates = vec_add(ray.origin, vec_scale(ray.direction, closest_intersect));
}

/*
----Note----------------------------------
base_or_side_hit: a number between 1 and 3.
1 = intersection with curved surface of cylinder.
2 = intersection with "upper base" of cylinder.
3 = intersection with "lower base" of cylinder.

CALCUATION FOR 1 (intersection with curved surface)
cyl_center_to_intersect: a vector between the cylinder center and the intersection point.

intersect_distance_on_axis: a scalar projection where we see how har up on the cylinder axis,
the intersection point is.

axis_p_closest_to_intersect: make the intersect_distance_to_axis,
into an actual point x,y,z on the axis.

the surface normal:
a unit vector pointing outward from the axis point of intersect,
to the actual cylinder surface point of intersect.

A surface normal is a unit vector pointing directly outward from the point of intersect.
*/
void	set_cyl_intersect_surface_normal(t_cylinder *cyl, t_intersection *intersect)
{
	t_xyz	cyl_center_to_intersect;
	t_xyz	axis_p_closest_to_intersect;
	float	intersect_distance_on_axis;

	if (cyl->base_or_side_hit == 1)
	{
		cyl_center_to_intersect = vec_subtract((*intersect).coorinates, cyl->cylinderCenter);
		intersect_distance_on_axis = vec_dot(cyl_center_to_intersect, cyl->normVecOfAxis);
		axis_p_closest_to_intersect = vec_add(cyl->cylinderCenter, vec_scale(cyl->normVecOfAxis, intersect_distance_on_axis));
		(*intersect).surface_normal = vec_normalize(vec_subtract((*intersect).coorinates, axis_p_closest_to_intersect));
	}
	else if (cyl->base_or_side_hit == 2)
		(*intersect).surface_normal = cyl->normVecOfAxis;
	else if (cyl->base_or_side_hit == 3)
		(*intersect).surface_normal = vec_scale(cyl->normVecOfAxis, -1);
}
