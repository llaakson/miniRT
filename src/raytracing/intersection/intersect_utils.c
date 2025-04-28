/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 22:15:14 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/28 12:12:28 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

void	set_intersection_data(t_hit *inter, t_xyz rgb, float inter_p, t_ray ray)
{
	(*inter).closest_intersect = inter_p;
	(*inter).rgb = rgb;
	(*inter).coordinates = vec_add(ray.origin, vec_scale(ray.dir, inter_p));
}

/*
----Note----------------------------------
base_or_side_hit: a number between 1 and 3.
1 = intersection with curved surface of cylinder.
2 = intersection with "upper base" of cylinder.
3 = intersection with "lower base" of cylinder.

CALCUATION FOR 1 (intersection with curved surface)
cyl_center_to_intersect: a vector between the
cylinder center and the intersection point.

intersect_distance_on_axis: a scalar projection where we see
how har up on the cylinder axis, the intersection point is.

axis_p_closest_to_intersect: make the intersect_distance_to_axis,
into an actual point x,y,z on the axis.

the surface normal:
a unit vector pointing outward from the axis point of intersect,
to the actual cylinder surface point of intersect.

A surface normal is a unit vector
pointing directly outward from the point of intersect.
*/
void	set_cyl_intersect_surface_normal(t_cylinder *cyl,
	t_hit *inter, t_ray ray)
{
	t_xyz	cyl_center_to_inter_p;
	t_xyz	axis_inter_p;
	float	inter_dist_on_axis;

	if (cyl->base_or_side_hit == 1)
	{
		cyl_center_to_inter_p = vec_sub((*inter).coordinates, cyl->center);
		inter_dist_on_axis = vec_dot(cyl_center_to_inter_p, cyl->orientation);
		axis_inter_p = vec_scale(cyl->orientation, inter_dist_on_axis);
		axis_inter_p = vec_add(cyl->center, axis_inter_p);
		(*inter).surface_normal = vec_sub((*inter).coordinates, axis_inter_p);
		(*inter).surface_normal = vec_normalize((*inter).surface_normal);
	}
	else if (cyl->base_or_side_hit == 2)
		(*inter).surface_normal = cyl->orientation;
	else if (cyl->base_or_side_hit == 3)
		(*inter).surface_normal = vec_scale(cyl->orientation, -1);
	//test
	if (vec_dot(ray.dir, (*inter).surface_normal) > 0.0)
		(*inter).surface_normal = vec_scale((*inter).surface_normal, -1);
}
