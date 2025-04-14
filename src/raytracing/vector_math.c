/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:25:34 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/14 18:07:12 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_xyz vec_add(t_xyz one, t_xyz two)
{
	t_xyz result;

	result.x = one.x + two.x;
	result.y = one.y + two.y;
	result.z = one.z + two.z;
	return (result);
}

t_xyz vec_subtract(t_xyz one, t_xyz two)
{
	t_xyz result;

	result.x = one.x - two.x;
	result.y = one.y - two.y;
	result.z = one.z - two.z;
	return (result);
}

t_xyz vec_scale(t_xyz vec, float scale)
{
	t_xyz result;

	result.x = vec.x * scale;
	result.y = vec.y * scale;
	result.z = vec.z * scale;
	return (result);
}

float vec_dot(t_xyz one, t_xyz two)
{
	return (one.x * two.x + one.y * two.y + one.z * two.z);
}

/*
Calculates and returns a third vector which points to a direction, that is at a 90° angle from the original two vectors.
*/
t_xyz vec_cross(t_xyz one, t_xyz two)
{
	t_xyz result;

	result.x = one.y * two.z - one.z * two.y;
	result.y = one.z * two.x - one.x * two.z;
	result.z = one.x * two.y - one.y * two.x;
	return (result);
}

float vec_length(t_xyz vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_xyz vec_normalize(t_xyz vec)
{
	t_xyz result;
	float length;

	length = vec_length(vec);
	if (length == 0.0f)
		return ((t_xyz){0, 0, 0});
	result.x = vec.x / length;
	result.y = vec.y / length;
	result.z = vec.z / length;
	return (result);
}
