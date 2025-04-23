/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:31:36 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/23 13:20:31 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

/*
Arguments:
A sphere, and a ray from the camera, going in the direction of a certain pixel of the screen.

Description:
We want to find out if the ray intersects with the sphere in the 3d scene.
We build up the mathematical formula for that.

A sphere is defined by the fact that on which-ever point on the sphere surface, the distance
to the sphere center will be the same. That distance is the same as the sphere radius.
We can define this with an equation (P - C)^2 = r^2, where
P = a point,
C = sphere center,
r = the radius.

We can also define a ray (or a point in the ray) as P(t) = O + t * D, where
P(t) = a point on the ray,
O = ray origin,
t = where on the ray we are,
D = ray direction.

Since both P in the sphere formula, and P in the ray formula stands for a point in space,
we can insert the ray formula (which gives us a P), into the sphere formula.
We get the formula (O + t * D - C)^2 = r^2.
This formula, in this form, would tell us what the radius of a sphere would have to be, for a
certain point in a ray to intersect with the sphere.

But we want to find out t, which means where on the ray we intersect the sphere (if we even do so).
So we convert the formula. For simplicity we rewrite O - C to oc.
(oc + tD)^2 = r^2.

A quite famous convertion we will use as a middle-step is (a + b)^2 = a^2 + 2ab + b^2. So,
(oc + tD)^2 = oc * oc + 2(oc * tD) + t^2(D * D).

oc * oc + 2(oc * tD) + t^2(D * D) is still the formula for finding r^2. We want to find t. There's a ready-made
formula for that, after we convert ours to the standard quadratic equation form at^2+bt+c=0.
oc * oc + 2(oc * tD) + t^2(D * D) = r^2
oc * oc - r^2 + 2(oc * tD) + t^2(D * D) = 0.

We quickly reorder this to match at^2+bt+c=0 going from t^2 to t to no t.
t^2(D * D) + 2(oc * tD) + oc * oc - r^2 = 0.

We now have all the keys to fill in these values according to our sphere and ray information we got as arguments.
(Except for t, that is still what we're finding out!)

We earlier changed O - C to oc.
So oc = ray origin - sphere center.
a = D * D = dot product of the ray direction.
b = 2(oc * D) = 2 * dot product of oc and ray direction.
c = oc * oc - r2 = dot product of oc - sphere_radius * sphere_radius.

In the function we call, quadratic equation(), we will convert to the form where we find t.
To find t means to find where on the ray, the ray intersects with a sphere (if it does so).

Return:
Closest ray intersection of the sphere.
*/
static float intersect_sphere(t_sphere *sphere, t_ray ray)
{
	//have to check that a b c value is small enough to fit inside a float??? same goes for everywhere with maths
	t_xyz oc;
	float a;
	float b;
	float c;
	float sphere_radius;

	sphere_radius = sphere->diameter / 2;
	oc = vec_subtract(ray.origin, sphere->sphereCenter);
	a = vec_dot(ray.direction, ray.direction);
	b = 2.0 * vec_dot(oc, ray.direction);
	c = vec_dot(oc, oc);
	c = c - sphere_radius * sphere_radius;
	return (quadratic_equation(a, b, c));
}

void loop_intersect_spheres(t_sphere *spheres, t_ray ray, t_intersection *intersection)
{
	t_sphere *current;
	float temp;

	if (!spheres)
		return ;
	current = spheres;
	while (current != NULL)
	{
		temp = intersect_sphere(current, ray);
		if (temp < (*intersection).rayClosestIntersect && temp > -1.0)
		{
			(*intersection).rayClosestIntersect = temp;
			(*intersection).object.spheres = current;
			(*intersection).RGB = current->RGB;
			(*intersection).coorinates = vec_add(ray.origin, vec_scale(ray.direction, temp));
			(*intersection).surface_normal =  vec_normalize(vec_subtract((*intersection).coorinates, current->sphereCenter));
		}
		current = current->next;
	}
}
