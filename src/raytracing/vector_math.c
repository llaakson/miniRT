/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:25:34 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/29 21:32:47 by aalbrech         ###   ########.fr       */
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
t_xyz	vec_sub(t_xyz one, t_xyz two)
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
t_xyz	vec_scale(t_xyz vec, double scale)
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
- If u need to do vector * vector and want
a double answer, you can use this function.

Return:
A double number telling us how alike the directions of the vectors are.

If return value is
Positive: The directions point in similar directions,
0: The directions point 90° apart,
Negative: The directions point in opposite directions

If the two argument vectors are normalized, return values mean
1: The directions are exactly the same,
0: The directions point 90° apart,
-1: The directions are completely opposite
*/
double	vec_dot(t_xyz one, t_xyz two)
{
	return (one.x * two.x + one.y * two.y + one.z * two.z);
}

/*
Arguments:
Two vectors.

Description:
Calculation of cross product.
Calculates a new vector which points to a direction,
that is at a 90° angle from both the original vectors.
The new vector's length is equal to the area of
the parallellogram formed by the two argument vectors.

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
