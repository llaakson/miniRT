/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:25:34 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/25 10:43:36 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
Arguments:
Two vectors

Description:
Addition of the two vectors.

Return:
A new vector that is the result of the addition.
*/
t_xyz	vec_add(t_xyz one, t_xyz two)
{
	t_xyz	result;

	result.x = one.x + two.x;
	result.y = one.y + two.y;
	result.z = one.z + two.z;
	return (result);
}

/*
Arguments:
Two vectors

Description:
Subtraction of the two vectors.

Return:
A new vector that is the result of the subtraction.
*/
t_xyz	vec_subtract(t_xyz one, t_xyz two)
{
	t_xyz	result;

	result.x = one.x - two.x;
	result.y = one.y - two.y;
	result.z = one.z - two.z;
	return (result);
}

/*
Arguments:
A vector and a scalar.

Description:
Scale a vector according to the scalar.
The direction of the vector won't change, only the length.

Return:
A new vector with the same direction as the argument vector,
but with a different length.

*/
t_xyz	vec_scale(t_xyz vec, float scale)
{
	t_xyz	result;

	result.x = vec.x * scale;
	result.y = vec.y * scale;
	result.z = vec.z * scale;
	return (result);
}

/*
Arguments:
Two vectors.

Description:
- Calculation of dot product.
- Comparison the direction of the two vectors.
- If u need to do vector * vector and want a float answer, you can use this function.

Return:
A float number telling us how alike the directions of the vectors are.

If return value is
Positive: The directions point in similar directions,
0: The directions point 90° apart,
Negative: The directions point in opposite directions

If the two argument vectors are normalized, return values mean
1: The directions are exactly the same,
0: The directions point 90° apart,
-1: The directions are completely opposite
*/
float	vec_dot(t_xyz one, t_xyz two)
{
	return (one.x * two.x + one.y * two.y + one.z * two.z);
}

/*
Arguments:
Two vectors.

Description:
Calculation of cross product.
Calculates a new vector which points to a direction, that is at a 90° angle from both the original vectors.
The new vector's length is equal to the area of the parallellogram formed by the two argument vectors.

Return:
The new vector that is the result of vector cross product.
*/
t_xyz	vec_cross(t_xyz one, t_xyz two)
{
	t_xyz	result;

	result.x = one.y * two.z - one.z * two.y;
	result.y = one.z * two.x - one.x * two.z;
	result.z = one.x * two.y - one.y * two.x;
	return (result);
}

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
