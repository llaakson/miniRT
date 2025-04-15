/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:06:35 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/15 13:19:15 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

//t = point on the ray
static float quadratic_equation(float a, float b, float c)
{
	float discriminant;
	float t0;
	float t1;
	
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0.0) //no intersection
		return (-1.0);
	
	//ray often intersects an object twice, where it enters and where it leaves the object
	// the t's = ray hits
	t0 = (-b - sqrtf(discriminant)) / (2 * a);
	t1 = (-b + sqrtf(discriminant)) / (2 * a);

	if (t0 <= 0.0 || t1 <= 0.0) //ray hits are behind the camera
		return (-1.0);
	if (t0 < t1) //return closest hit to camera
		return (t0);
	return (t1);
}

//at^2+bt+c=0
static float intersect_sphere(t_sphere *sphere, t_ray ray)
{
	t_xyz sp_center_to_ray_orig;
	float a;
	float b;
	float c;
	float sphere_radius;

	sphere_radius = sphere->diameter / 2;
	sp_center_to_ray_orig = vec_subtract(ray.origin, sphere->sphereCenter);
	a = vec_dot(ray.direction, ray.direction);
	b = 2.0 * vec_dot(sp_center_to_ray_orig, ray.direction);
	c = vec_dot(sp_center_to_ray_orig, sp_center_to_ray_orig);
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
