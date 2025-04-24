/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_formulas.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:27:38 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/23 16:45:37 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/miniRT.h"

/*
Arguments:
The a,b and c in the standard quadratic equation (at^2+bt+c=0).

Description:
Standard quadratic equation, in the form where we want to find out t.
t stands for where on the ray we are. If t is more than 0, the ray hits the object.
(
t = (-b - sqrt(b*b - 4 * a * c)) / (2 * a)
AND
t = (-b + sqrt(b*b - 4 * a * c)) / (2 * a)
)
We get two different t because of this.
Ideally, one where the ray enters the object, and one where the ray exits the object.
It could also be that the object and the ray only has one intersection point.
That would mean that the ray bumps into the object.

Return:
-1 if there's no intersection. (discriminant < 0).
-1 if both the intersections are behind the camera. We can't see them in the scene.
Else the smaller of the two t values, which means the hit is closer to the camera.

*/
float quadratic_equation(float a, float b, float c)
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
	if (t0 > t1)
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