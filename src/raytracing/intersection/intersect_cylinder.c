/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:53:31 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/20 21:02:51 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

static float solve_t_quadratic_formula(t_xyz ray_dir_perpentual_to_axis, t_xyz oc_proj, float radius)
{
	float a;
	float b;
	float c;

	a = vec_dot(ray_dir_perpentual_to_axis, ray_dir_perpentual_to_axis);
	b = 2.0 * vec_dot(ray_dir_perpentual_to_axis, oc_proj);
	c = vec_dot(oc_proj, oc_proj) - radius * radius;
	return (quadratic_equation(a, b, c));
}

static float t_is_valid_hit_point(t_cylinder *cyl, t_ray ray, float t)
{
	t_xyz hit_point;
	t_xyz vec_center_to_hit;
	float hit_proj;

	hit_point = vec_add(ray.origin, vec_scale(ray.direction, t));
	vec_center_to_hit = vec_subtract(hit_point, cyl->cylinderCenter);
	hit_proj = vec_dot(vec_center_to_hit, cyl->normVecOfAxis);

	if (fabsf(hit_proj) > cyl->height / 2.0)
		return (-1);
	return (0);
}


/*
Arguments;
A cylinder in the scene, and a ray from the camera going in the direction of a certain pixel on the screen.

Description:
Find out if the ray intersects with the cylinder in the 3d scene.

A cylinder consists of two circular bases connected by a curved surface.
We need to find if the ray intersects with either any of the circular bases, or if it intersects the curved surface.

Return:
Where on the ray, the ray intersects with the cylinder.
*/
static float intersect_cylinder(t_cylinder *cyl, t_ray ray)
{
	t_xyz  vec_cyl_axis;
	t_xyz  vec_cyl_to_cam;
	t_xyz ray_dir_perpentual_to_axis;
	t_xyz oc_proj;
	float t;

	vec_cyl_axis = cyl->normVecOfAxis;
	vec_cyl_to_cam = vec_subtract(ray.origin, cyl->cylinderCenter);
	ray_dir_perpentual_to_axis = vec_subtract(ray.direction, vec_scale(vec_cyl_axis, vec_dot(ray.direction, vec_cyl_axis)));
	oc_proj = vec_subtract(vec_cyl_to_cam, vec_scale(vec_cyl_axis, vec_dot(vec_cyl_to_cam, vec_cyl_axis)));

	t = solve_t_quadratic_formula(ray_dir_perpentual_to_axis, oc_proj, cyl->diameter / 2.0);

	if (t_is_valid_hit_point(cyl, ray, t) == -1)
		return (-1);

	//also try the two bases
		
	return (t);
}
