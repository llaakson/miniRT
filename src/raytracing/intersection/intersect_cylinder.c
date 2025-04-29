/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:53:31 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/29 21:35:30 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"
/*
Arguments:
D⊥, O⊥ and r of the equation (O⊥ + tD⊥)^2 = r^2.

Description:
We re-organize our equation (O⊥ + tD⊥)^2 = r^2,
to get the standard quadratic formula (at^2 + bt + c = 0).
t^2(D⊥ * D⊥) + 2t(D⊥ * O⊥) + (O⊥ * O⊥) − r^2 = 0.

We calculate our a, b and c
according to our version of the standard quadratic formula,
and then we solve for t in quadratic_equation().

Return:
t (where on the ray, the ray intersects with the cylinder)
*/
static double	solve_t_quadratic_formula(t_xyz ray_dir_perp_to_axis,
	t_xyz cyl_to_cam_dir_perp_to_axis, double radius)
{
	double	a;
	double	b;
	double	c;

	a = vec_dot(ray_dir_perp_to_axis, ray_dir_perp_to_axis);
	b = 2.0 * vec_dot(ray_dir_perp_to_axis, cyl_to_cam_dir_perp_to_axis);
	c = vec_dot(cyl_to_cam_dir_perp_to_axis, cyl_to_cam_dir_perp_to_axis);
	c = c - radius * radius;
	return (quadratic_equation(a, b, c));
}

/*
Arguments:
The cylinder, the ray,
and t (where on the ray, the ray intersects with the cylinder)

Description:
t is calculated as a point on the ray, where the point
intersects the cylinder curved surface if the cylinder is infinitely long.
Here we check if the point is a
valid point if the cylinder is finitely long (which it is).

intersect_coords = The coordinates of the intersection. t is not a coordinate.

vec_cyl_center_to_intersect_p = A vector from the
cylinder center to the intersection point.

axis_point_of_intersect = The intersection point is on the cylinder surface.
Here we find out the distance from the cylinder center
(middle point of cylinder, on the axis) to the point on the axis,
where the intersection at a radius distance "horizontally" will happen.

We make axis_point_of_intersect into a absolute value (the positive
equivalent of the number, so -33 would be 33 and so on).
The cylinder height is always positive, but the axis_point_of_intersect
can be negative (since cylinder center is in the middle of the axis ("point 0"),
the axis_point_of_intersect can be below it (negative), or above it (positive).
Then we compare the absolute value against the cylinder height / 2.
We divide the height by two, to compare the axis_point_of_intersect with either
center_point to top of cylinder, or center_point, to bottom of cylinder.

Return:
-1 if the intersection point is
not within the height of the cylinder. 0 if it is.
*/
static double	t_is_valid_intersection(t_cylinder *cyl, t_ray ray, double t)
{
	t_xyz	intersect_coords;
	t_xyz	vec_cyl_center_to_intersect_p;
	double	axis_point_of_intersect;

	intersect_coords = vec_add(ray.origin, vec_scale(ray.dir, t));
	vec_cyl_center_to_intersect_p = vec_sub(intersect_coords, cyl->center);
	axis_point_of_intersect = vec_dot(vec_cyl_center_to_intersect_p,
			cyl->orientation);
	if (fabs(axis_point_of_intersect) > cyl->height / 2.0)
		return (-1);
	return (0);
}

/*
Arguments:
The cylinder and a check for what kind of plane we want to make.

Description:
Initialize a t_plane struct based on cylinder base parameters.
A cylinder has two bases. Based on the check value, we decide what
kind of cyl_base we want the plane to represent,
the cylinder upper base (0) or the cylinder lower base (1).
They have different center points, but other
than that the plane struct will look the same for them both.

Return:
The newly made t_plane struct.
*/
static t_plane	init_cyl_base_as_plane(t_cylinder *cyl, int check)
{
	t_plane	cyl_base;

	cyl_base.next = NULL;
	cyl_base.rgb = (t_xyz){0, 0, 0};
	if (check == 0)
	{
		cyl_base.point_in_plane = vec_add(cyl->center,
				vec_scale(cyl->orientation, cyl->height / 2.0));
		cyl_base.orientation = cyl->orientation;
	}
	else if (check == 1)
	{
		cyl_base.point_in_plane = vec_sub(cyl->center,
				vec_scale(cyl->orientation, cyl->height / 2.0));
		cyl_base.orientation = vec_scale(cyl->orientation, -1);
	}
	return (cyl_base);
}

/*
Arguments:
The ray, the cylinder, the radius of the cylinder,
and a pointer to t which we can
modify if we find a closer intersection point to the camera along the ray.

Description:
See if the ray has an intersection point with
either the upper base or the lower base of the cylinder.
We first treat the bases (that are round), as planes, so
we can use the already existing plane intersection function.
Then we check if the potential intersection point is actually
within the borders of the circular base.

Index i is also used in the loop to choose which of the
bases we are testing.
i = 0 upper base
i = 1 lower base

Return:
Nothing. We modify t in case of intersection point.
*/
static void	intersect_cylinder_bases(t_ray ray, t_cylinder *cyl,
	double cyl_radius, double *t)
{
	double	temp;
	t_plane	cyl_base;
	int		i;
	t_xyz	intersect_point;
	t_xyz	base_to_inter_p;

	i = 0;
	while (i < 2)
	{
		cyl_base = init_cyl_base_as_plane(cyl, i);
		temp = intersect_plane(&cyl_base, ray);
		intersect_point = vec_add(ray.origin, vec_scale(ray.dir, temp));
		base_to_inter_p = vec_sub(intersect_point, cyl_base.point_in_plane);
		if (vec_dot(base_to_inter_p, base_to_inter_p)
			<= cyl_radius * cyl_radius)
		{
			if ((*t == -1 && temp != -1) || (temp < *t && temp > -1))
			{
				*t = temp;
				cyl->base_or_side_hit = i + 2;
			}
		}
		i++;
	}
}

/*
Arguments;
A cylinder in the scene, and a ray from the camera going
in the direction of a certain pixel on the screen.

Description:
Find out if the ray intersects with the cylinder in the 3d scene.

A cylinder consists of two circular bases connected by a curved surface.
We need to find if the ray intersects with either
any of the circular bases, or if it intersects the curved surface.


------Equations used---------------------------------------------
We have the ray formula P(t) = O + t * D, where
P(t) = a point on the ray,
O = ray origin,
t = where on the ray we are,
D = ray direction.

We have the cylinder formula for a infinitely long curved surface (P⊥)^2 = r^2,
defining that every point at a radius distance from the cylinder axis,
is part of the surface of the cylinder.
r = radius
P⊥ = a point perpendicular to the axis.

We insert the ray formula into the cylinder formula,
to get a formula that can satisfy
both equations (a point both part of the cylinder and part of the ray).
New formula: (O⊥ + tD⊥)^2 = r^2.



-----PART 1------------------------------------------------------
In this function we first want to figure out what our values D⊥ and O⊥ are.
We already have the radius (cyl->diamteter / 2),
and t is what we want to solve for later on.
(t = where on the ray, the ray could intersect with the cylinder).

vec_cyl_axis: the direction of the cylinder axis.

vec_cyl_to_cam: vector from the cylinder center to the camera.

!OUR D⊥! ray_dir_perp_to_axis: The ray (a 3d vector) has a direction.
The direction can be split into two components relative to the cylinder.
How much the ray is pointing towards the cylinder, and how much the ray
is pointing along (parallell) the cylinder.
ray_dir_perpentual_to_axis, is the component that is
perpendicular to the cylinder (pointing towards it).

!OUR O⊥! cyl_to_cam_dir_perp_to_axis: Similar to ray_dir_perpentual_to_axis,
but instead the component of the vector from the cylinder center to the camera,
that is perpendicular to the cylinder.


----PART 2----------------------------------------------------------
We solve t (where on the ray, the ray intersects
with the cylinder curved surface)
for our newly made formula, in solve_t_quadratic_formula().
Since our formula is for an infinitely long cylinder,
we afterwards find out if the intersection point is actually
within the height of our
finite cylinder curved surface (t_is_valid_intersection()).


----PART 3---------------------------------------------------------
We find out if the ray happens to intersect with any of the cylinder bases

Return:
Where on the ray, the ray intersects with the cylinder.
*/
double	intersect_cylinder(t_cylinder *cyl, t_ray ray)
{
	t_xyz	vec_cyl_axis;
	t_xyz	vec_cyl_to_cam;
	t_xyz	ray_dir_perp_to_axis;
	t_xyz	cyl_to_cam_dir_perp_to_axis;
	double	t;

	vec_cyl_axis = cyl->orientation;
	vec_cyl_to_cam = vec_sub(ray.origin, cyl->center);
	ray_dir_perp_to_axis = vec_sub(ray.dir, vec_scale(vec_cyl_axis,
				vec_dot(ray.dir, vec_cyl_axis)));
	cyl_to_cam_dir_perp_to_axis = vec_sub(vec_cyl_to_cam,
			vec_scale(vec_cyl_axis, vec_dot(vec_cyl_to_cam, vec_cyl_axis)));
	t = solve_t_quadratic_formula(ray_dir_perp_to_axis,
			cyl_to_cam_dir_perp_to_axis, cyl->diameter / 2.0);
	if (t != -1)
	{
		if (t_is_valid_intersection(cyl, ray, t) == -1)
			t = -1;
		else
			cyl->base_or_side_hit = 1;
	}
	intersect_cylinder_bases(ray, cyl, cyl->diameter / 2, &t);
	return (t);
}
