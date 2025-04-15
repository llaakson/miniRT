/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:06:35 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/15 18:55:14 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
Arguments:
The a,b and c in the standard quadratic equation (at^2+bt+c=0).

Description:
Standard quadratic equation, in the form where we want to find out t.
t stands for where on the ray we are. If t is more than 0, the ray hits the sphere.
(
t = (-b - sqrt(b*b - 4 * a * c)) / (2 * a)
AND
t = (-b + sqrt(b*b - 4 * a * c)) / (2 * a)
)
We get two different t because of this.
Ideally, one where the ray enters the sphere, and one where the ray exits the sphere.

Return:
-1 if there's no intersection. (discriminant < 0).
-1 if both the intersections are behind the camera. We can't see them in the scene.
Else the smaller of the two t values, which means the hit is closer to the camera.
*/
static float quadratic_equation(float a, float b, float c)
{
	float discriminant;
	float t0;
	float t1;
	float temp;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0.0)
		return (-1.0);
	t0 = (-b - sqrtf(discriminant)) / (2 * a);
	t1 = (-b + sqrtf(discriminant)) / (2 * a);
	if (t0 > t1) //set so t0 is always the smallest
	{
		temp = t0;
		t0 = t1;
		t1 = temp;
	}
	if (t0 > 0.0)
		return t0;
	if (t1 > 0.0)
		return t1;
	return (-1.0);
}

/*
Arguments:
A sphere, and a ray from the camera, going in the direction of a certain pixel of the screen.

Description:
We want to find out if the ray intersects with the sphere.
We build up the mathematical formula for that.

A sphere is defined by the fact that on which-ever point on the sphere border, the distance
to the sphere center will be the same. That distance is the same as the sphere radius.
We can define this with an equation (P - C)^2 = r^2, where
P = a point,
C = sphere center,
r = the radius.

We can also define a ray (or a point in the ray) as P(t) = O + t * D, where
P(t) = a point on the ray,
O = ray origin,
t = where on the ray we are
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

static float loop_intersect_sphere(t_sphere *spheres, t_ray ray)
{
	t_sphere *current;
	float temp;
	float closest_intersect;

	if (!spheres)
		return (-1.0);
	current = spheres;
	closest_intersect = INFINITY;
	while (current != NULL)
	{
		temp = intersect_sphere(current, ray);
		if (temp < closest_intersect && temp > -1.0)
			closest_intersect = temp;
		current = current->next;
	}
	if (closest_intersect == INFINITY)
		return (-1.0);
	return (closest_intersect);
}

//check if a ray hits an object
float intersect(t_minirt *data, t_ray ray)
{
	float closest_intersect;
	float temp;

	closest_intersect = INFINITY;
	temp = loop_intersect_sphere(data->objects->spheres, ray);
	if (temp < closest_intersect && temp > -1.0)
		closest_intersect = temp;
	if (closest_intersect == INFINITY)
		return(-1.0);
	return (closest_intersect);
}
