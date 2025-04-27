/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:10:01 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/27 20:10:36 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
Arguments:
A vector.

Description:
Calculates the length of the argument vector.

Return:
A float value representing the vector length.
*/
float	vec_length(t_xyz vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

/*
Arguments:
A vector.

Description:
Vector normalization (shrinking the vector length to exactly 1).
The result is a unit vector.
A unit vector has the length of exactly 1.
A unit vector is basically a vector with only a direction,
so, a unit vector represents a direction.
__________________________________________
			Vector  |  Unit vector		  |
direction:  yes   	|  yes				  |
length:     yes     |  no (always 1)	  |
__________________________________________|

Return:
A unit vector (=normalized vector), based on the argument vector.
The unit vector result and the argument vector has the same direction, but
the unit vector result has no information about the length anymore.
*/
t_xyz	vec_normalize(t_xyz vec)
{
	t_xyz	result;
	float	length;

	length = vec_length(vec);
	if (length == 0.0f)
		return ((t_xyz){0, 0, 0});
	result.x = vec.x / length;
	result.y = vec.y / length;
	result.z = vec.z / length;
	return (result);
}
