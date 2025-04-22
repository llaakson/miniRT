/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:53:31 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/22 18:24:06 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

static float solve_t_quadratic_formula(t_xyz ray_dir_perpentual_to_axis, t_xyz cyl_to_cam_dir_perpentual_to_axis, float radius)
{
	float a;
	float b;
	float c;

	a = vec_dot(ray_dir_perpentual_to_axis, ray_dir_perpentual_to_axis);
	b = 2.0 * vec_dot(ray_dir_perpentual_to_axis, cyl_to_cam_dir_perpentual_to_axis);
	c = vec_dot(cyl_to_cam_dir_perpentual_to_axis, cyl_to_cam_dir_perpentual_to_axis) - radius * radius;
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

vec_cyl_axis: the direction of the cylinder axis.

vec_cyl_to_cam: vector from the cylinder center (coordinates of the middle of the cylinder end cap) to the camera.

ray_dir_perpentual_to_axis: The ray (a 3d vector) has a direction. The direction can be split into two components relative to the cylinder.
How much the ray is pointing towards the cylinder, and how much the ray is pointing along (parallell) the cylinder.
ray_dir_perpentual_to_axis, is the component that is perpentual to the cylinder.

cyl_to_cam_dir_perpentual_to_axis: Similar to ray_dir_perpentual_to_axis,
but instead the component of the vector from the cylinder center to the camera, that is perpentual to the cylinder.

Return:
Where on the ray, the ray intersects with the cylinder.
*/
static float intersect_cylinder(t_cylinder *cyl, t_ray ray)
{
	t_xyz  vec_cyl_axis;
	t_xyz  vec_cyl_to_cam;
	t_xyz ray_dir_perpentual_to_axis;
	t_xyz cyl_to_cam_dir_perpentual_to_axis;
	float t;

	vec_cyl_axis = cyl->normVecOfAxis;
	vec_cyl_to_cam = vec_subtract(ray.origin, cyl->cylinderCenter);
	ray_dir_perpentual_to_axis = vec_subtract(ray.direction, vec_scale(vec_cyl_axis, vec_dot(ray.direction, vec_cyl_axis)));
	cyl_to_cam_dir_perpentual_to_axis = vec_subtract(vec_cyl_to_cam, vec_scale(vec_cyl_axis, vec_dot(vec_cyl_to_cam, vec_cyl_axis)));

	t = solve_t_quadratic_formula(ray_dir_perpentual_to_axis, cyl_to_cam_dir_perpentual_to_axis, cyl->diameter / 2.0);

	if (t_is_valid_hit_point(cyl, ray, t) == -1)
		return (-1);

	//also try the two bases

	return (t);
}
