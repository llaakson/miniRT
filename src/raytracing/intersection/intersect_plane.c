/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:36:21 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/18 21:34:31 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

/*
Arguments:
A plane in the scene, and a ray from the camera going in the direction of a certain pixel on the screen.

Description:
Find out if the ray intersects with the plane in the 3d scene.
A plane in this case is infinite (it has no specified length or area).
A ray can intersect the plane, not intersect the plane,
or be perfectly aligned with and lie on the plane (The ray touches an eternal amount of points on the sphere).

We have the ray formula P(t) = O + t * D, where
P(t) = a point on the ray,
O = ray origin,
t = where on the ray we are,
D = ray direction.

We have the plane formula in vector form: (P - Po) * n = 0, where
P = a "test" point (if the test point is on the plane, the result will be 0)
Po = a point on the plane,
n = a normal vector to the plane

We insert the ray formula into the P of the plane formula.
(O + t * D - Po) * n = 0;

We want to solve the equation in regards to t (where on the ray a intersection with the plane is true).
We organize the new formula for that.
t =  (Po - O) * n / D * n

If D *n is equal to 0, the ray and plane are parallell.

If D * n = 0 AND (Po - O) * n = 0, the ray is perfectly aligned with and lies on the plan. In this case we
return 0.0001 as a random point on the ray, to prevent the pixel the ray is
sampling from to be missed in the result rendered image. We return such a small value (0.0001 units from the ray origin),
to make sure we realistically capture the plane in the scene. Since the ray is "hitting" the plane at every point,
and the plane is infinite, Returning a hit point as soon as we can from the camera is safest.

Otherwise we calculate the result t. If t < 0, the intersection is behind the camera.
*/
static float intersect_plane(t_plane *plane, t_ray ray)
{
	float t;
	float numerator;
	float denominator;

	numerator = vec_dot(vec_subtract(plane->pointInPlane, ray.origin), plane->normNormalVec);
	denominator = vec_dot(ray.direction, plane->normNormalVec);
	if (denominator == 0)
		return (-1);
	else if (numerator == 0 && denominator == 0)
		return (0.0001);
	t =  numerator / denominator;
	if (t < 0)
		return (-1);
	return (t);
}


void loop_intersect_planes(t_plane *planes, t_ray ray, t_intersection *intersection)
{
	t_plane *current;
	float temp;

	if (!planes)
		return ;
	current = planes;
	while (current != NULL)
	{
		temp = intersect_plane(current, ray);
		if (temp < (*intersection).rayClosestIntersect && temp > -1.0)
		{
			(*intersection).rayClosestIntersect = temp;
			(*intersection).object.planes = current;
		}
		current = current->next;
	}
}
