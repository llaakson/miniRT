/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:18:04 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/11 21:43:47 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	is_whitespace(char c)
{
	if ((c == 32) || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int ft_strcmp(char *s1, char *s2)
{
	if (ft_strlen(s1) == ft_strlen(s2))
	{
		if (ft_strncmp(s1, s2, ft_strlen(s1)) == 0)
			return (1);
	}
	return (0);
}

float ft_atof(char *str, float *result)
{
	int i;
	float sign;
	float decimal_place;

	i = 0;
	sign = 1;
	*result = 0;
	decimal_place = 0.1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	no_extra_minus_in_str(str, i);
	while (str[i] >= '0' && str[i] <= '9')
	{
        *result = *result * 10 + (str[i] - '0');
        i++;
    }
    // Parse decimal part (if any)
    if (str[i] == '.')
	{
        i++;
        while (str[i] >= '0' && str[i] <= '9')
		{
            *result += (str[i] - '0') * decimal_place;
            decimal_place *= 0.1;
            i++;
        }
	}
	//check max and min no overflow!!
	*result = *result *sign;
	return (0);
}
